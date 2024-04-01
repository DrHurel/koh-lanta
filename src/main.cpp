#include "entities/party.h"
#include "utils.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <config_path>" << std::endl;
    return 1;
  }

  auto party = read_config(argv[1]);

  party.init_game();

  party.start_game();

  return 0;
}
