#ifndef ENTITY_H
#define ENTITY_H

#include "graphics/drawable.hpp"
#include "graphics/graphics.hpp"
#include <string.h>

namespace Mayhem {

class Entity : public Drawable {
    int id_;

  public:
    Entity(const std::string &name_file, const int id) : Drawable(name_file), id_(id){};
    virtual ~Entity(){};
    int get_id() { return id_; };
    virtual ~Entity() = 0;
}; // class Entity

} // namespace Mayhem

#endif // ENTITY_H
