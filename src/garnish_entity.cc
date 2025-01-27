#include "garnish_entity.h"
#include <algorithm>
#include <cassert>
#include <cstddef>

namespace garnish {
  GarnishEntityManager::GarnishEntityManager() {
    for (GarnishEntity i=0; i<MAX_ENTITIES; i++) {
      AvailableEntities.push_back(i);
    }
  }

  GarnishEntity GarnishEntityManager::NewEntity() {
    assert(!AvailableEntities.empty() && "Error: Exceeded maximum entity count");
    GarnishEntity e = AvailableEntities.front();
    AvailableEntities.pop_front();
    return e;
  }
  void GarnishEntityManager::SetSignature(GarnishEntity e, GarnishSignature s) {
    GARNISH_VALID_ENTITY();
    Signatures[e]=s;
  }

  GarnishSignature GarnishEntityManager::GetSignature(GarnishEntity e) {
    GARNISH_VALID_ENTITY();
    assert(std::find(AvailableEntities.begin(), AvailableEntities.end(), e) != AvailableEntities.end() && "Error: Entity Not registered");
    return Signatures[e];
  }

  void GarnishEntityManager::RemoveEntity(GarnishEntity e) {
    GARNISH_VALID_ENTITY();
    // Check if the entity id is valid and not available, this is why we use a deque instead of a queue
    assert(std::find(AvailableEntities.begin(), AvailableEntities.end(), e) == AvailableEntities.end() && "Error: Entity already available");
    Signatures[e]=0;
    AvailableEntities.push_back(e);
  }
}
