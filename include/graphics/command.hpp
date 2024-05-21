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

/// A class that handles game events
class Command {
  private:
    /// Type of game event
    enum class Type {
        no_type,        ///< No type
        base,           ///< The base has been selected
        deck,           ///< The deck has been selected
        action_on_base, ///< The action move to the base
        minion_on_base, ///< The minion move to the base
        action_on_hand, ///< The action move to the hand
        minion_on_hand, ///< The monion move to the hand
        end_turn,       ///< Button "end turn" has pressed
        close_window,   ///< Window has closed
    };                  // enum class Type

    /// Command status
    enum class Status {
        same,      ///< The sequence is completely the same
        different, ///< The sequence is completely the different
        possible,  ///< The sequence is possible
    };             // enum class Status

  private: // all possible commands
    /// @brief parameters of the standard action
    const std::array<Type, 3> action{Type::action_on_hand, Type::base, Type::minion_on_base};
    /// @brief parameters of the move action
    const std::array<Type, 4> move_action{Type::action_on_hand, Type::base, Type::minion_on_base, Type::base};
    /// @brief parameters of the draw action
    const std::array<Type, 2> draw_action{Type::action_on_hand, Type::deck};
    /// @brief parameters for moving the minion to the base
    const std::array<Type, 2> minion_to_base{Type::minion_on_hand, Type::base};
    /// @brief parameters for end turn
    const std::array<Type, 1> end_turn{Type::end_turn};
    /// @brief parameters for close window
    const std::array<Type, 1> close_window{Type::close_window};
    /// @brief parameters minion selection options
    const std::array<Type, 2> choose_minion{Type::minion_on_hand, Type::minion_on_hand};
    /// @brief minion selection base
    const std::array<Type, 2> choose_base{Type::base, Type::base};

  private:
    /// @brief Event buffer
    std::vector<std::pair<Type, Drawable *>> events = std::vector<std::pair<Type, Drawable *>>();
    /// @brief Graphics model
    GraphicsModel &model;

  private:
    /// @brief Determines the status of the command
    template <std::size_t N> Status is_this_command(const std::array<Type, N> &data) const;

    /// @brief Checks whether the command can be executed
    void check_commands();

    /// @brief Play move action
    void activate_move_action();

    /// @brief Play typical action
    void activate_typical_action();

    /// @brief Play draw action
    void activate_draw_action();

  public:
    /// @brief Command constructor
    Command() = delete;
    /** @brief Command constructor

        @param[out] m Link to the graphic model
    */
    Command(GraphicsModel &m);

    /**
        @brief Adds the card to the command queue
        @param[out] card Pointer to player card
    */
    void set_card(PlayerCard *card);

    /**
        @brief Adds the shown card to the command queue
        @param[out] card Pointer to player card
    */
    void set_shown_card(PlayerCard *card);

    /**
        @brief Adds the base to the command queue
        @param[out] base Pointer to base
    */
    void set_base(Base *base);

    /**
        @brief Adds the deck to the command queue
        @param[out] deck Pointer to deck
    */
    void set_deck(Deck<PlayerCard *> *deck);

    /**
        @brief Adds the button to the command queue
        @param[in] type Button type
    */
    void set_button(Button::Type type);

    /**
        @brief Clears the command queue
    */
    void clear();

    /**
        @brief Command destructor
    */
    ~Command() = default;
}; // class Command

} // namespace Mayhem

#endif // COMMAND_HPP
