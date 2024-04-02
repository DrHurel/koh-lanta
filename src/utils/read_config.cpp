#include "entities/party.h"
#include "player.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct fail_to_open_file : public std::exception {};

Party read_config(const std::string &config_path) {

  std::ifstream file(config_path);

  if (!file.is_open()) {
    throw fail_to_open_file();
  }

  std::string line;
  auto party = Party();
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string team_name;
    iss >> team_name;
    std::string member;
    std::vector<std::shared_ptr<Player>> members;
    int id = 0;
    while (iss >> member) {
      members.emplace_back(std::make_shared<Player>(id, member));
      id++;
    }
    party.add_team(team_name, members);
  }

  std::cout << "Config file read successfully" << std::endl;
  return party;
}