#ifndef MENU_HPP
#define MENU_HPP

#include "graphics/graphics_model.hpp"
#include "graphics/screen.hpp"

namespace Mayhem {

/// A menu with a choice of the number of players
class PlayersMenu final : private Screen {
  public:
    /// @brief Constructor
    PlayersMenu();

    /// @brief Run this screan
    /// @param window Window
    /// @param attributes Attributes from menu
    /// @return State of getting menu parameters
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);

    /// @brief Destructor
    ~PlayersMenu() = default;
}; // class PlayerMenu

/// A menu with a choice of the number of player
class ServerMenu final : private Screen {
  public:
    /// @brief Constructor
    ServerMenu();

    /// @brief Run this screan
    /// @param window Window
    /// @param attributes Attributes from menu
    /// @return State of getting menu parameters
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);

    /// @brief Destructor
    ~ServerMenu() = default;
}; // class OnlineMenu

// Settings for the game type selection menu
class TypeGameMenu final : private Screen {
  private:
    /// @brief Menu with choosing number of players
    PlayersMenu players_menu = PlayersMenu();

  public:
    /// @brief Constructor
    TypeGameMenu();

    /// @brief Run this screan
    /// @param window Window
    /// @param attributes Attributes from menu
    /// @return State of getting menu parameters
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);

    /// @brief Destructor
    ~TypeGameMenu() = default;
}; // class TypegameMenu

// The main menu
class MainMenu final : private Screen {
  private:
    /// @brief Menu with game type
    TypeGameMenu type_menu = TypeGameMenu();

  public:
    /// @brief Constructor
    MainMenu();

    /// @brief Run this screan
    /// @param window Window
    /// @param attributes Attributes from menu
    /// @return State of getting menu parameters
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);

    /// @brief Destructor
    ~MainMenu() = default;
}; // class MainMenu

} // namespace Mayhem

#endif // MENU_HPP
