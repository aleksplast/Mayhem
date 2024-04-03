#include "core/entity.h"

namespace Mayhem {

Entity::Entity(const std::string &name_file, const int id) : Drawable(name_file), id_(id){};

int Entity::get_id() const { return id_; };

} // namespace Mayhem
