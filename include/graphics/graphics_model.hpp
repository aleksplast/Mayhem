#ifndef GRAPHICS_MODEL_HPP
#define GRAPHICS_MODEL_HPP

#include "graphics/button.hpp"

namespace Mayhem {

class Engine;
class PlayerCard;
class Base;
template <class T> class Deck;

// The graphics class responsible for data storage
class GraphicsModel {
  public:
    // Graphics settings
    struct Settings {

        // Game types
        enum class GameType {
            online,
            offline,
        }; // enum class GameType

        // The structure describing the location of entities on the window
        struct Rendering {

            // Drawing Player
            struct Player {

                // Scale
                struct Scale {
                    static constexpr float x = 0.38;
                    static constexpr float y = 0.25;
                }; // struct Slace

                // increas��� the size of the main player
                static constexpr float increase = 1.6;

                // Drawing Cards' place
                struct CardsPlace {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.7;
                        static constexpr float y = 0.75;
                    }; // struct Scale

                    // Position
                    struct Position {
                        static constexpr float x = 0.5;
                        static constexpr float y = 0.5;
                    }; // struct Position

                    // Drawing card
                    struct Card {

                        // Scale
                        struct Scale {
                            static constexpr float x = 0.25;
                            static constexpr float y = 1.0;
                        }; // struct Scale
                    };     // struct Card
                };         // struct CardsPlace
            };             // struct Player

            // Displaying a place with the main cards
            struct ShowenPlace {

                // Scale
                struct Scale {
                    static constexpr float x = 0.8;
                    static constexpr float y = 0.25;
                }; // struct Scale

                // Position
                struct Position {
                    static constexpr float x = 0.5;
                    static constexpr float y = 0.65;
                }; // struct Position

                // Drawing card
                struct Card {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.12;
                        static constexpr float y = 1;
                    }; // struct Scale
                };     // struct Card

            }; // struct ShowenPlace

            // Drawing the place where the bases are located
            struct BasesPlace {

                // Scale
                struct Scale {
                    static constexpr float x = 0.8;
                    static constexpr float y = 0.2;
                }; // struct Scale

                // Position
                struct Position {
                    static constexpr float x = 0.5;
                    static constexpr float y = 0.3;
                }; // struct Position

                // Drawing Bases
                struct Base {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.15;
                        static constexpr float y = 1.0;
                    }; // struct Scale

                }; // struct Base

            }; // strust BasesPlace

            // Drawing Buttons
            struct Button {

                // Drawing Button end_turn
                struct EndTurn {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.1;
                        static constexpr float y = 0.08;
                    }; // struct Scale

                    // Position
                    struct Position {
                        static constexpr float x = 0.82;
                        static constexpr float y = 0.46;
                    }; // struct Position

                }; // struct EndTurn

                // Drawing power icon
                struct Power {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.18;
                        static constexpr float y = 0.1;
                    }; // struct Scale
                };     // struct Power

                // Player points
                struct Points {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.15;
                        static constexpr float y = 0.15;
                    }; // struct Scale
                };     // struct Points

                // Drawing summary units power on base
                struct UnitsPower {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.7;
                        static constexpr float y = 0.2;
                    }; // struct Scale

                    // Position
                    struct Position {
                        static constexpr float x = 0.5;
                        static constexpr float y = -0.1;
                    }; // struct Position
                };     // struct UnitsPower

                // Drawing buttons on Screen
                struct ScreenButtons {

                    // Offset
                    struct Offset {
                        static constexpr float x = 0.5;
                        static constexpr float y = 0.15;
                        static constexpr float start = 0.2; // initial y-axis offset
                    };                                      // struct Offset

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.28;
                        static constexpr float y = 0.12;
                    }; // struct Scale

                    static constexpr unsigned int char_size = 36;
                }; // struct ScreenButtons
            };     // struct Button

            // Drawing poppong up card
            struct PopUpCard {

                // Scale
                struct Scale {
                    static constexpr float x = 0.13;
                    static constexpr float y = 0.35;
                }; // struct Scale

                // Position
                struct Position {
                    static constexpr float x = 0.13;
                    static constexpr float y = 0.5;
                }; // struct Position
            };     // struct PopUpCard
        };         // struct Rendering

    }; // struct Settings

    // The data set for graphics
    struct Data {

        // Attibutes for drawing entities
        struct Attributes {
            uint16_t draw_player; // num player who graphics draw
            sf::RenderWindow &window;
            sf::Vector2u default_window_size;
            std::vector<PlayerCard *> current_player_cards;
            std::vector<Deck<PlayerCard *> *> current_decks;
            std::vector<Base *> active_bases;
            std::vector<std::pair<Button::Type, sf::FloatRect>> buttuns;
            std::pair<Base *, std::vector<PlayerCard *>> shown_place;
            PlayerCard *popping_up_card = nullptr;

          public:
            Attributes(sf::RenderWindow &window) : window(window){};
        }; // struct Attributes

        // Attributes for menu
        struct MenuAttributes {
            // Game actions
            enum class GameAction {
                play,
                exit,
            }; // enum class GameAction

            sf::Vector2u default_window_size;
            Settings::GameType type;
            GameAction action;
            uint16_t num_players = 3;
            uint16_t number_of_player;
        }; // struct MenuAttributes
    };     // struct Data

  public:
    Data::Attributes attributes;
    Settings::GameType type;
    Engine &engine;

  public:
    GraphicsModel() = delete;
    GraphicsModel(Engine &e, sf::RenderWindow &window, const Data::MenuAttributes &menu_attributes);
    ~GraphicsModel() = default;

}; // class GraphicsModel

} // namespace Mayhem

#endif // GRAPHICS_MODEL_HPP
