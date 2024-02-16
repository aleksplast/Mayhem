#ifndef ENTITY_H
#define ENTITY_H

#include "../graphics/graphics.hpp"

namespace Mayhem {

class Entity : public Drawable {
    int id_;

public:
    Entity(int id) : id_(id) {};
    virtual ~Entity() {};
    int get_id() const { return id_; };
}; // class Entity

} //namespace Mayhem

#endif // ENTITY_H
