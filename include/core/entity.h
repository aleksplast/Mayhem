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
    //!--------------------------------
    //! @brief Constructor for Engine
    //! @param[out] name_main_file main image file
    //! @param[in] id id of the entity
    //! @param[out] name_extra_file extra_image_file
    //! @return Players leaderboard on base
    //!--------------------------------
    Entity(const std::string &name_main_file, const int id, const std::string &name_extra_file = "");

    virtual ~Entity() = default;

    //!--------------------------------
    //! @brief Get ID of the entity
    //!--------------------------------
    int get_id() const;
}; // class Entity

} // namespace Mayhem

#endif // ENTITY_H
