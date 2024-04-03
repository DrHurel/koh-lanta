#include "entities/team.h"

#include <iostream>
#include <mutex>

void Team::standby_players(int travel_time, int random_event_occurence,
                           int bucket_size) {

  std::cout << "standby..." << members.size() << std::endl;
  for (const auto &member : members) {
    std::cout << *member << " is standing by" << std::endl;

    threads.emplace_back(
        [&member, this, travel_time, random_event_occurence, bucket_size]() {
          std::unique_lock lock(mtx);
          while (!is_game_started->load()) {
            cv->wait(lock, [this]() { return is_game_started->load(); });
          }
          lock.unlock();

          routine(bucket_size, travel_time, random_event_occurence, member);

          lock.lock();
          if (!is_game_started->load()) {
            return;
          }

          std::cout << *this << *member << " is done" << std::endl;
          std::cout << *this << " has Won" << std::endl;
          std::cout << std::endl;
          std ::cout << "Game Over" << std::endl;

          is_game_started->store(false);
          return;
        });
  }
}

void Team::routine(int bucket_size, int travel_time, int random_event_occurence,
                   std::shared_ptr<Player> member) {
  if (member->get_id() != 0) {
    std::cout << *this << *member << " is sleeping" << std::endl;
    member->put_to_sleep();
  }

  while (bucket.load() < bucket_size && is_game_started->load()) {
    member->fetch_water(travel_time, random_event_occurence);
    fillBucket(member->get_water_bucket());
    members.at((member->get_id() + 1) % members.size())->wake_up();

    member->put_to_sleep();

    if (is_game_started->load()) {
      std::cout << *this << " bucket is : " << bucket << std::endl;
    } else {
      return;
    }
  }
}