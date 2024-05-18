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
                    static constexpr float x = 0.38f;
                    static constexpr float y = 0.25f;
                }; // struct Slace

                // increasing the size of the main player
                static constexpr float increase = 1.6f;

                // Drawing Cards' place
                struct CardsPlace {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.7f;
                        static constexpr float y = 0.75f;
                    }; // struct Scale

                    // Position
                    struct Position {
                        static constexpr float x = 0.5f;
                        static constexpr float y = 0.5f;
                    }; // struct Position

                    // Drawing card
                    struct Card {

                        // Scale
                        struct Scale {
                            static constexpr float x = 0.25f;
                            static constexpr float y = 1.0f;
                        }; // struct Scale
                    };     // struct Card
                };         // struct CardsPlace
            };             // struct Player

            // Displaying a place with the main cards
            struct ShowenPlace {

                // Scale
                struct Scale {
                    static constexpr float x = 0.8f;
                    static constexpr float y = 0.25f;
                }; // struct Scale

                // Position
                struct Position {
                    static constexpr float x = 0.5f;
                    static constexpr float y = 0.65f;
                }; // struct Position

                // Drawing card
                struct Card {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.12f;
                        static constexpr float y = 1.0f;
                    }; // struct Scale
                };     // struct Card

            }; // struct ShowenPlace

            // Drawing the place where the bases are located
            struct BasesPlace {

                // Scale
                struct Scale {
                    static constexpr float x = 0.8f;
                    static constexpr float y = 0.2f;
                }; // struct Scale

                // Position
                struct Position {
                    static constexpr float x = 0.5f;
                    static constexpr float y = 0.3f;
                }; // struct Position

                // Drawing Bases
                struct Base {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.15f;
                        static constexpr float y = 1.0f;
                    }; // struct Scale

                }; // struct Base

            }; // strust BasesPlace

            // Drawing Buttons
            struct Button {

                // Drawing Button end_turn
                struct EndTurn {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.1f;
                        static constexpr float y = 0.08f;
                    }; // struct Scale

                    // Position
                    struct Position {
                        static constexpr float x = 0.82f;
                        static constexpr float y = 0.46f;
                    }; // struct Position

                }; // struct EndTurn

                // Drawing power icon
                struct Power {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.18f;
                        static constexpr float y = 0.1f;
                    }; // struct Scale
                };     // struct Power

                // Player points
                struct Points {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.15f;
                        static constexpr float y = 0.15f;
                    }; // struct Scale
                };     // struct Points

                // Drawing summary units power on base
                struct UnitsPower {

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.7f;
                        static constexpr float y = 0.2f;
                    }; // struct Scale

                    // Position
                    struct Position {
                        static constexpr float x = 0.5f;
                        static constexpr float y = -0.1f;
                    }; // struct Position
                };     // struct UnitsPower

                // Drawing buttons on Screen
                struct ScreenButtons {

                    // Offset
                    struct Offset {
                        static constexpr float x = 0.5f;
                        static constexpr float y = 0.15f;
                        static constexpr float start = 0.2f; // initial y-axis offset
                    };                                       // struct Offset

                    // Scale
                    struct Scale {
                        static constexpr float x = 0.28f;
                        static constexpr float y = 0.12f;
                    }; // struct Scale

                    static constexpr unsigned int char_size = 36u;
                }; // struct ScreenButtons
            };     // struct Button

            // Drawing poppong up card
            struct PopUpCard {

                // Scale
                struct Scale {
                    static constexpr float x = 0.13f;
                    static constexpr float y = 0.35f;
                }; // struct Scale

                // Position
                struct Position {
                    static constexpr float x = 0.13f;
                    static constexpr float y = 0.5f;
                }; // struct Position
            };     // struct PopUpCard
        };         // struct Rendering

    }; // struct Settings

    // The data set for graphics
    struct Data {

        // Attibutes for drawing entities
        struct Attributes {
            uint16_t draw_player = 0; // num player who graphics draw
            sf::RenderWindow &window;
            sf::Vector2u default_window_size = sf::Vector2u();
            std::vector<PlayerCard *> current_player_cards = std::vector<PlayerCard *>();
            std::vector<Deck<PlayerCard *> *> current_decks = std::vector<Deck<PlayerCard *> *>();
            std::vector<Base *> active_bases = std::vector<Base *>();
            std::vector<std::pair<Button::Type, sf::FloatRect>> buttuns =
                std::vector<std::pair<Button::Type, sf::FloatRect>>();
            std::pair<Base *, std::vector<PlayerCard *>> shown_place = std::pair<Base *, std::vector<PlayerCard *>>();
            PlayerCard *popping_up_card = nullptr;

          public:
            Attributes() = delete;
            Attributes(const Attributes &) = delete;
            Attributes(Attributes &&) = delete;
            Attributes &operator=(const Attributes &) = delete;
            Attributes &operator=(Attributes &&) = delete;
            Attributes(sf::RenderWindow &Window) : window(Window){};
            ~Attributes() = default;
        }; // struct Attributes

        // Attributes for menu
        struct MenuAttributes {
            // Game actions
            enum class GameAction {
                play,
                exit,
            }; // enum class GameAction

            sf::Vector2u default_window_size = sf::Vector2u();
            Settings::GameType type = Settings::GameType::offline;
            GameAction action = GameAction::exit;
            uint16_t num_players = 4;
            uint16_t number_of_player;
        }; // struct MenuAttributes
    };     // struct Data

  public:
    Data::Attributes attributes;
    Settings::GameType type = Settings::GameType::offline;
    Engine &engine;

  public:
    GraphicsModel() = delete;
    GraphicsModel(Engine &e, sf::RenderWindow &window, const Data::MenuAttributes &menu_attributes);
    ~GraphicsModel() = default;

}; // class GraphicsModel

} // namespace Mayhem

#endif // GRAPHICS_MODEL_HPP
