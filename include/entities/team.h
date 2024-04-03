#ifndef TEAM_H
#define TEAM_H

#include "entities/player.h"
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Team {
private:
  // mutex
  std::vector<std::jthread> threads;
  std::mutex mtx = std::mutex();
  std::shared_ptr<std::condition_variable> cv;
  std::atomic<int> bucket = 0;
  std::atomic<int> next = 0;
  std::vector<std::shared_ptr<Player>> members;
  const std::string name;
  const std::shared_ptr<std::atomic<bool>> is_game_started;
  /// Fill the bucket with the given amount of water and return the
  /// amount of water that was actually added
  int fillBucket(int amount) { return bucket += amount; }

  void routine(int bucket_size, int travel_time, int random_event_occurence,
               std::shared_ptr<Player> member);

public:
  Team(const std::vector<std::shared_ptr<Player>> &members,
       std::shared_ptr<std::condition_variable> cv,
       std::shared_ptr<std::atomic<bool>> is_game_started,
       const std::string &name)
      : cv(cv), members(members), name(name),
        is_game_started(is_game_started){};

  void standby_players(int travel_time, int random_event_occurence,
                       int bucket_size);
  void join() {
    for (auto &thread : threads) {
      thread.join();
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Team &t) {
    os << "Team " << t.name;
    return os;
  }
};

#endif // TEAM_H