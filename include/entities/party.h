#ifndef PARTY_H
#define PARTY_H

#include "entities/team.h"
#include <condition_variable>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
class Party {
private:
  std::map<std::string, Team> teams;
  std::shared_ptr<std::condition_variable> cv =
      std::make_shared<std::condition_variable>();
  std::shared_ptr<std::atomic<bool>> is_game_started =
      std::make_shared<std::atomic<bool>>(false);

public:
  Party();

  void add_team(const std::string &name, const std::vector<Player> &members) {

    if (auto [_, is_created] =
            teams.try_emplace(name, members, cv, is_game_started);
        !is_created) {
      std::cerr << "Team " << name << " already exists!" << std::endl;
    }
  }

  void init_game() {
    for (auto &[name, team] : teams) {
      team.standby_players();
      std::cout << "Team " << name << " is ready!" << std::endl;
    }
  }

  // notify all the players that the game has started
  void start_game() const {
    is_game_started->store(true);
    cv->notify_all();
  }
};

#endif // PARTY_H