#ifndef ENTITY_H
#define ENTITY_H

#include "graphics/drawable.hpp"
#include "graphics/graphics.hpp"
#include <string.h>

namespace Mayhem {

// Entity class
class Entity : public Drawable {

    // Entity ID
    int id_;

  public:
    Entity(const std::string &name_file, const int id) : Drawable(name_file), id_(id){};
    virtual ~Entity(){};

    // Get ID of the entity
    int get_id() const { return id_; };
}; // class Entity

} // namespace Mayhem

#endif // ENTITY_H
