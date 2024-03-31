#ifndef TEAM_H
#define TEAM_H

#include "entities/player.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>
class Team {
private:
  // mutex
  std::unique_lock<std::mutex> mtx = std::unique_lock<std::mutex>();
  std::condition_variable cv = std::condition_variable();
  std::atomic<int> bucket = 0;
  std::vector<Player> members;
  std::atomic<bool> is_game_started = false;
  /// Fill the bucket with the given amount of water and return the
  /// amount of water that was actually added
  int fillBucket(int amount) { return bucket += amount; }

public:
  Team();
  ~Team();

  void standby_players() {
    for (auto &member : members) {
      std::jthread member_thread([&member, this]() {
        mtx.lock();
        while (!is_game_started.load()) {
          cv.wait(mtx, [this] {
            return is_game_started.load();
          }); // Add condition argument to wait
        }
        mtx.unlock();

        member.fetch_water();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        fillBucket(member.get_water_bucket());
      });
    }
  }

  void go() {
    is_game_started.store(true);
    cv.notify_all();
  }
};

#endif // TEAM_H