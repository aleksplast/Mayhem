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

// A class that handles game events
class Command {
  private:
    // enum class type of game event
    enum class Type {
        no_type,
        base,
        deck,
        action_on_base,
        minion_on_base,
        action_on_hand,
        minion_on_hand,
        end_turn,
        close_window,
    }; // enum class Type

    // Command status
    enum class Status {
        same,
        different,
        possible,
    }; // enum class Status

  private: // all possible commands
    const std::array<Type, 3> action{Type::action_on_hand, Type::base, Type::minion_on_base};
    const std::array<Type, 4> move_action{Type::action_on_hand, Type::base, Type::minion_on_base, Type::base};
    const std::array<Type, 2> draw_action{Type::action_on_hand, Type::deck};
    const std::array<Type, 2> minion_to_base{Type::minion_on_hand, Type::base};
    const std::array<Type, 1> end_turn{Type::end_turn};
    const std::array<Type, 1> close_window{Type::close_window};
    const std::array<Type, 2> choose_minion{Type::minion_on_hand, Type::minion_on_hand};
    const std::array<Type, 2> choose_base{Type::base, Type::base};

  private:
    std::vector<std::pair<Type, Drawable *>> events = std::vector<std::pair<Type, Drawable *>>();
    GraphicsModel &model;

  private:
    // determines the status of the command
    template <std::size_t N> Status is_this_command(const std::array<Type, N> &data) const;

    // checks whether the command can be executed
    void check_commands();

    // Play move action
    void activate_move_action();

    // Play typical action
    void activate_typical_action();

    // Play draw action
    void activate_draw_action();

  public:
    Command() = delete;
    Command(GraphicsModel &m);

    // Adds the card to the command queue
    void set_card(PlayerCard *card);

    // Adds the shown card to the command queue
    void set_shown_card(PlayerCard *card);

    // Adds the base to the command queue
    void set_base(Base *base);

    // Adds the deck to the command queue
    void set_deck(Deck<PlayerCard *> *deck);

    // Adds the button to the command queue
    void set_button(Button::Type type);

    // Clears the command queue
    void clear();

    ~Command() = default;
}; // class Command

} // namespace Mayhem

#endif // COMMAND_HPP
