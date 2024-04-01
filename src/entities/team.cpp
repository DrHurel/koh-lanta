#include "entities/team.h"

void Team::standby_players() {
  for (auto &member : members) {
    std::jthread member_thread([&member, this]() {
      mtx.lock();
      while (!is_game_started->load()) {
        cv->wait(mtx, [this] {
          return is_game_started->load();
        }); // Add condition argument to wait
      }
      mtx.unlock();

      member.fetch_water();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      fillBucket(member.get_water_bucket());
    });
  }
}