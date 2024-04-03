#ifndef PLAYER_H
#define PLAYER_H

// Include any necessary headers here

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <ostream>
#include <string>

// Define the Player class

class Player {
public:
  // Constructor
  explicit Player(const int id, const std::string &name);

  void fetch_water(const int travel_time, const int random_event_occurenc);
  int get_water_bucket() const;
  [[maybe_unused]] void empty_bucket();

  template <typename T>
  friend std::basic_ostream<T> &operator<<(std::basic_ostream<T> &os,
                                           const Player &p) {
    return os << p.id << ":Player " << p.name << " has " << p.water_bucket
              << " water";
  }

  void put_to_sleep() {
    std::unique_lock lock(mtx);
    player_cv.wait(lock, []() { return true; });
  }

  void wake_up() {
    std::unique_lock lock(mtx);
    water_bucket = 0;
    player_cv.notify_one();
  }
  int get_id() const { return id; }

private:
  int id;
  std::mutex mtx;
  std::string name;
  int water_bucket = 0;
  std::condition_variable player_cv;

  /// event that can happen to the player when he goes to fill the bamboo
  /// bucket, will decrease the amount of water in the bucket
  void randomevent(const int travel_time);
};

#endif // PLAYER_H