#include "entities/player.h"

#include <thread> // Include the <thread> header

#include <random> // Include the <random> header

Player::Player(const int id, const std::string &name) : id(id), name(name) {}

void Player::randomevent() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  water_bucket--;
}

void Player::fetch_water() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dis(0, 9);
  water_bucket = dis(gen);
}

int Player::get_water_bucket() const {
  return water_bucket;
} // Return 0 instead of 1

[[maybe_unused]] void Player::empty_bucket() {
  water_bucket = 0;
} // Return 0 instead of 1