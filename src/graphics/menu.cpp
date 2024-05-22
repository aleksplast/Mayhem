#include "graphics/menu.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace Mayhem;

PlayersMenu::PlayersMenu() : Screen({"2 players", "3 players", "4 players", "back"}){};
TypeGameMenu::TypeGameMenu() : Screen({"offline", "online", "back"}){};
MainMenu::MainMenu() : Screen({"play", "exit"}){};
ServerMenu::ServerMenu() : Screen({"2 Players", "3 players", "4 players", "back"}){};

bool MainMenu::run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes) {
    using Scope = GraphicsModel::Data::MenuAttributes;
    window.clear();
    Screen::draw(window, attributes.default_window_size);
    window.display();
    int16_t num_event = get_event(window, attributes.default_window_size);

    if (num_event != 0) {
        attributes.action = Scope::GameAction::exit;
        return false;
    }
    attributes.action = Scope::GameAction::play;
    if (!type_menu.run(window, attributes))
        return run(window, attributes);
    else
        return true;
}

bool TypeGameMenu::run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes) {
    window.clear();
    Screen::draw(window, attributes.default_window_size);
    window.display();
    int16_t num_event = get_event(window, attributes.default_window_size);

    switch (num_event) {
    case -1:
        attributes.action = GraphicsModel::Data::MenuAttributes::GameAction::exit;
        return true;
        break;
    case 0:
        attributes.type = GraphicsModel::Settings::GameType::offline;
        if (!players_menu.run(window, attributes))
            return run(window, attributes);
        else
            return true;
        break;
    case 1:
        attributes.type = GraphicsModel::Settings::GameType::online;
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool PlayersMenu::run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes) {
    window.clear();
    Screen::draw(window, attributes.default_window_size);
    window.display();
    int16_t num_event = get_event(window, attributes.default_window_size);

    switch (num_event) {
    case -1:
        attributes.action = GraphicsModel::Data::MenuAttributes::GameAction::exit;
        return true;
        break;
    case 0:
    case 1:
    case 2:
        attributes.num_players = num_event + 2u;
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool ServerMenu::run(sf::RenderWindow &window, GraphicsModel::Data::MenuAttributes &attributes) {
    window.clear();
    Screen::draw(window, attributes.default_window_size);
    window.display();
    int16_t num_event = get_event(window, attributes.default_window_size);

    switch (num_event) {
    case -1:
        attributes.action = GraphicsModel::Data::MenuAttributes::GameAction::exit;
        return true;
        break;
    case 0:
    case 1:
    case 2:
        attributes.num_players = num_event + 2;
        return true;
        break;
    default:
        return false;
        break;
    }
}
