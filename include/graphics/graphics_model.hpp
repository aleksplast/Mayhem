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
                    static constexpr float y = 0.25;
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

            }; // struct Button

        }; // struct Rendering

    }; // struct Settings

    // The data set for graphics
    struct Data {

        // Attibutes for drawing entities
        struct Attributes {
            uint16_t draw_player; // num player who graphics draw
            sf::RenderWindow window;
            sf::Vector2u default_window_size;
            std::vector<PlayerCard *> current_player_cards;
            std::vector<Deck<PlayerCard *> *> current_decks;
            std::vector<Base *> active_bases;
            std::vector<std::pair<Button::Type, sf::FloatRect>> buttuns;
            std::pair<Base *, std::vector<PlayerCard *>> shown_place;
        }; // struct Attributes
    };     // struct Data

  public:
    Data::Attributes attributes;
    Settings::GameType type;
    Engine &engine;

  public:
    GraphicsModel() = delete;
    GraphicsModel(Engine &e);
    ~GraphicsModel() = default;

}; // class GraphicsModel

} // namespace Mayhem

#endif // GRAPHICS_MODEL_HPP
