#include "entities/team.h"

#include <iostream>

void Team::standby_players() {

  std::cout << "standby..." << members.size() << std::endl;
  for (const auto &member : members) {
    std::cout << *member << " is standing by" << std::endl;

    threads.emplace_back([&member, this]() {
      std::unique_lock lock(mtx);
      while (!is_game_started->load()) {

        cv->wait(lock, [this]() { return is_game_started->load(); });
      }
      lock.unlock();

      if (member->get_id() != 0) {
        std::cout << *this << *member << " is sleeping" << std::endl;
        member->put_to_sleep();
      }

      while (bucket < 50 && is_game_started->load()) {
        std::cout << *this << *member << " is playing" << std::endl;

        member->fetch_water();
        fillBucket(member->get_water_bucket());

        members.at((member->get_id() + 1) % members.size())->wake_up();
        member->put_to_sleep();
      }

      lock.lock();
      if (!is_game_started->load()) {
        return;
      }
      std::cout << *this << *member << " is done" << std::endl;
      std::cout << *this << " has Won" << std::endl;
      std::cout << std::endl;
      std ::cout << "Game Over" << std::endl;
      is_game_started->store(false);
      lock.unlock();
      return;
    });
  }
}