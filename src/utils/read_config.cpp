#include "entities/party.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct fail_to_open_file : public std::exception {};

Party read_config(const std::string &config_path) {
  std::ifstream file(config_path);
  if (!file.is_open()) {
    throw fail_to_open_file{};
  }
  std::string line;
  std::string party_name;
  std::vector<std::pair<std::string, std::vector<std::string>>> teams;

  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    if (line[0] == '[') {
      party_name = line.substr(1, line.size() - 2);
    } else {
      std::istringstream iss(line);
      std::string team_name;
      std::vector<std::string> members;
      iss >> team_name;
      std::string member;
      while (iss >> member) {
        members.push_back(member);
      }
      teams.emplace_back(team_name, members);
    }
  }
  auto party = Party();
  for (const auto &[team_name, members] : teams) {
    std::vector<Player> players;
    for (const auto &member : members) {
      players.emplace_back(member);
    }
    party.add_team(team_name, players);
  }
  return party;
}