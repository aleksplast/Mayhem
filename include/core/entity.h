#ifndef ENTITY_H
#define ENTITY_H

#include "graphics/drawable.hpp"
#include "graphics/graphics.hpp"
#include <string.h>

namespace Mayhem {

// Entity class
class Entity : public Drawable {
  protected:
    // Entity ID
    int id_;

  public:
    Entity(const std::string &name_main_file, const int id, const std::string &name_extra_file = "");
    virtual ~Entity(){};

    // Get ID of the entity
    int get_id() const;
}; // class Entity

} // namespace Mayhem

#endif // ENTITY_H
