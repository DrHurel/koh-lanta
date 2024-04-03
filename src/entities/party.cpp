#include "entities/party.h"

Party::Party(int travel_time, int random_event_occurence, int bucket_size)
    : bucket_size(bucket_size), travel_time(travel_time),
      random_event_occurence(random_event_occurence) {}