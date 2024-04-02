#include "entities/player.h"

#include <chrono>
#include <cstdlib>
#include <random>
#include <thread>

Player::Player(const int id, const std::string &name) : id(id), name(name) {}

void Player::randomevent() {
  std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 100));
  water_bucket = std::max(1, water_bucket - std::rand() % 2);
}

void Player::fetch_water() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dis(0, 9);
  water_bucket = dis(gen);
  auto delay = dis(gen) % 10 + 1;
  for (int i = 0; i < delay; i++) {
    randomevent();
  }
}

int Player::get_water_bucket() const {
  return water_bucket;
} // Return 0 instead of 1

[[maybe_unused]] void Player::empty_bucket() {
  water_bucket = 0;
} // Return 0 instead of 1