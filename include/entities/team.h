#ifndef TEAM_H
#define TEAM_H

#include "entities/player.h"
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
class Team {
private:
  // mutex
  std::unique_lock<std::mutex> mtx = std::unique_lock<std::mutex>();
  const std::shared_ptr<std::condition_variable> cv;
  std::atomic<int> bucket = 0;
  std::vector<Player> members;
  const std::shared_ptr<std::atomic<bool>> is_game_started;
  /// Fill the bucket with the given amount of water and return the
  /// amount of water that was actually added
  int fillBucket(int amount) { return bucket += amount; }

public:
  Team() = delete;
  Team(const std::vector<Player> &members,
       std::shared_ptr<std::condition_variable> cv,
       std::shared_ptr<std::atomic<bool>> is_game_started)
      : cv(cv), members(members), is_game_started(is_game_started){};

  void standby_players();
};

#endif // TEAM_H