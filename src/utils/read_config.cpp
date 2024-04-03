#include "entities/party.h"
#include "player.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct fail_to_open_file : public std::exception {};

Party read_config(const std::string &config_path) {

  std::cout << "Reading config file" << std::endl;
  std::ifstream file(config_path);

  if (!file.is_open()) {
    throw fail_to_open_file();
  }

  std::string line;

  std::getline(file, line);
  // configuration des paramettre du jeu

  std::istringstream config_line(line);
  int travel_time;
  int random_event_occurence;
  int bucket_size;
  config_line >> travel_time >> random_event_occurence >> bucket_size;
  auto party = Party(travel_time, random_event_occurence, bucket_size);

  while (std::getline(file, line)) {
    std::istringstream team_line(line);
    std::string team_name;
    team_line >> team_name;
    std::string member;
    std::vector<std::shared_ptr<Player>> members;
    int id = 0;
    while (team_line >> member) {
      members.emplace_back(std::make_shared<Player>(id, member));
      id++;
    }
    party.add_team(team_name, members);
  }

  std::cout << "Config file read successfully" << std::endl;
  return party;
}