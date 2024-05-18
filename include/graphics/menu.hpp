#ifndef MENU_HPP
#define MENU_HPP

#include "graphics/graphics_model.hpp"
#include "graphics/screen.hpp"

namespace Mayhem {

// A menu with a choice of the number of players
class PlayersMenu final : private Screen {
  public:
    PlayersMenu();
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);
    ~PlayersMenu() = default;
}; // class PlayerMenu

// A menu with a choice of the number of player
class OnlineMenu final : private Screen {
  public:
    OnlineMenu();
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);
    ~OnlineMenu() = default;
}; // class OnlineMenu

// Settings for the game type selection menu
class TypeGameMenu final : private Screen {
  private:
    PlayersMenu players_menu = PlayersMenu();
    OnlineMenu online_menu = OnlineMenu();

  public:
    TypeGameMenu();
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);
    ~TypeGameMenu() = default;
}; // class TypegameMenu

// The main menu
class MainMenu final : private Screen {
  private:
    TypeGameMenu type_menu = TypeGameMenu();

  public:
    MainMenu();
    bool run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes);
    ~MainMenu() = default;
}; // class MainMenu

} // namespace Mayhem

#endif // MENU_HPP
