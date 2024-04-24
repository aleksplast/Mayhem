#include "core/entity.h"

namespace Mayhem {

Entity::Entity(const std::string &name_main_file, const int id, const std::string &name_extra_file)
    : Drawable(name_main_file, name_extra_file), id_(id){};

int Entity::get_id() const { return id_; };

} // namespace Mayhem
