#ifndef PARTY_H
#define PARTY_H

#include "entities/team.h"
#include <vector>
class Party {
private:
  std::vector<Team> teams;

public:
  Party();
  ~Party();
};

#endif // PARTY_H