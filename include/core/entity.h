#ifndef ENTITY_H
#define ENTITY_H

#include "../graphics/graphics.hpp"

namespace Mayhem {

class Entity : public Drawable {
    int id_;

public:
    Entity(const std::string &name_file) : Drawable(name_file) {};
    virtual ~Entity() {};
    int get_id() { return id_; };
}; // class Entity

} //namespace Mayhem

#endif // ENTITY_H
