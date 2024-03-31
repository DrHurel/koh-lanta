#ifndef PLAYER_H
#define PLAYER_H

// Include any necessary headers here
#include <string>
// Define the Player class

class Player {
public:
  // Constructor
  explicit Player(const std::string &name);

  void fetch_water();
  int get_water_bucket() const;
  [[maybe_unused]] void empty_bucket();

private:
  int id;
  std::string name;
  int water_bucket = 0;

  /// event that can happen to the player when he goes to fill the bamboo
  /// bucket, will decrease the amount of water in the bucket
  void randomevent();
};

#endif // PLAYER_H