#ifndef PARTY_H
#define PARTY_H

#include "entities/team.h"
#include <condition_variable>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
class Party {
private:
  std::map<std::string, Team, std::less<>> teams;
  std::shared_ptr<std::condition_variable> cv =
      std::make_shared<std::condition_variable>();
  std::shared_ptr<std::atomic<bool>> is_game_started =
      std::make_shared<std::atomic<bool>>(false);
  int bucket_size;
  /// time it takes to travel from the start to the end in seconds
  int travel_time;
  /// number of seconds between each random event
  int random_event_occurence = 1;

public:
  /// Constructor for the Party class
  /// @param travel_time : time it takes to travel from the start to the end in
  /// seconds
  /// @param random_event_occurence : number of seconds between each random
  /// event
  Party(int travel_time, int random_event_occurence, int bucket_size);

  void add_team(const std::string &name,
                const std::vector<std::shared_ptr<Player>> &members) {

    if (auto [_, is_created] =
            teams.try_emplace(name, members, cv, is_game_started, name);
        !is_created) {
      std::cerr << "Team " << name << " already exists!" << std::endl;
    }
  }

  void init_game() {
    for (auto &[name, team] : teams) {
      team.standby_players(travel_time, random_event_occurence, bucket_size);
      std::cout << "Team " << name << " is ready!" << std::endl;
    }
  }

  // notify all the players that the game has started
  void start_game() {
    is_game_started->store(true);
    std::cout << "Game started!" << std::endl;
    cv->notify_all();
    for (auto &[_, team] : teams) {
      team.join();
    }
  }
};

#endif // PARTY_H