#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    int id_;

public:
    Entity(int id) : id_(id) {};
    virtual ~Entity() {};
    int get_id() const { return id_; };
}; // class Entity

#endif // ENTITY_H
