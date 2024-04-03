#include "entities/player.h"

#include <chrono>
#include <random>
#include <thread>

Player::Player(const int id, const std::string &name) : id(id), name(name) {}

void Player::randomevent(const int travel_time) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dis(0, travel_time);
  std::this_thread::sleep_for(
      std::chrono::milliseconds(dis(gen) + travel_time));
  water_bucket = std::max(1, water_bucket - dis(gen) % 2);
}

void Player::fetch_water(const int travel_time,
                         const int random_event_occurenc) {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dis(0, random_event_occurenc);
  water_bucket = dis(gen) % 10;
  auto delay = dis(gen) % random_event_occurenc + 1;
  for (int i = 0; i < delay; i++) {
    randomevent(travel_time);
  }
}

int Player::get_water_bucket() const {
  return water_bucket;
} // Return 0 instead of 1

[[maybe_unused]] void Player::empty_bucket() {
  water_bucket = 0;
} // Return 0 instead of 1