#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "graphics/button.hpp"
#include "graphics/graphics_model.hpp"
#include <array>
#include <vector>

namespace Mayhem {

class Drawable;
class PlayerCard;
class Base;
template <typename T> class Deck;

class Command {
  private:
    enum class Type {
        no_type,
        base,
        deck,
        action,
        minion,
        end_turn,
        close_window,
    }; // enum class Type

    enum class Status {
        same,
        different,
        possible,
    }; // enum class Status

  private: // all possible commands
    const std::array<Type, 3> action{Type::action, Type::base, Type::minion};
    const std::array<Type, 4> move_action{Type::action, Type::base, Type::minion, Type::base};
    const std::array<Type, 2> minion_to_base{Type::minion, Type::base};
    const std::array<Type, 1> end_turn{Type::end_turn};
    const std::array<Type, 1> close_window{Type::close_window};
    const std::array<Type, 2> choose_minion{Type::minion, Type::minion};
    const std::array<Type, 2> choose_base{Type::base, Type::base};

  private:
    std::vector<std::pair<Type, Drawable *>> events;
    GraphicsModel &model;

  private:
    template <int N> Status is_this_command(const std::array<Type, N> &data) const;
    void check_commands();
    void activate_move_action();
    void activate_typical_action();

  public:
    Command() = delete;
    Command(GraphicsModel &m);
    void set_card(PlayerCard *card);
    void set_base(Base *base);
    void set_deck(Deck<PlayerCard *> *deck);
    void set_button(Button::Type type);
    void clear();
    ~Command() = default;
}; // class Command

} // namespace Mayhem

#endif // COMMAND_HPP
