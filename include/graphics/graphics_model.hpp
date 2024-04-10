#ifndef GRAPHICS_MODEL_HPP
#define GRAPHICS_MODEL_HPP

#include "graphics/button.hpp"

namespace Mayhem {

class Engine;
class PlayerCard;
class Base;
template <class T> class Deck;

class GraphicsModel {
  public:
    struct Settings {
        enum class GameType {
            online,
            ofline,
        }; // enum class GameType

        struct Rendering {
            struct Player {
                struct Scale {
                    static constexpr float x = 0.38;
                    static constexpr float y = 0.25;
                }; // struct Slace

                static constexpr float increase = 1.6;

                struct CardsPlace {
                    struct Scale {
                        static constexpr float x = 0.7;
                        static constexpr float y = 0.75;
                    }; // struct Scale

                    struct Position {
                        static constexpr float x = 0.5;
                        static constexpr float y = 0.5;
                    }; // struct Position

                    struct Card {
                        struct Scale {
                            static constexpr float x = 0.25;
                            static constexpr float y = 1.0;
                        }; // struct Scale
                    }; // struct Card
                }; // struct CardsPlace
            }; // struct Player

            struct ShowenPlace {
                struct Scale {
                    static constexpr float x = 0.7;
                    static constexpr float y = 0.2;
                }; // struct Scale

                struct Position {
                    static constexpr float x = 0.5;
                    static constexpr float y = 0.65;
                }; // struct Position

                struct Card {
                    struct Scale {
                        static constexpr float x = 0.11;
                        static constexpr float y = 1;
                    }; // struct Scale
                }; // struct Card

            }; // struct ShowenPlace

            struct BasesPlace {
                struct Scale {
                    static constexpr float x = 0.8;
                    static constexpr float y = 0.2;
                }; // struct Scale

                struct Position {
                    static constexpr float x = 0.5;
                    static constexpr float y = 0.25;
                }; // struct Position

                struct Base {
                    struct Scale {
                        static constexpr float x = 0.15;
                        static constexpr float y = 1.0;
                    }; // struct Scale

                }; // struct Base

            }; // strust BasesPlace

            struct Button {
                struct EndTurn {
                    struct Scale {
                        static constexpr float x = 0.1;
                        static constexpr float y = 0.08;
                    }; // struct Scale

                    struct Position {
                        static constexpr float x = 0.82;
                        static constexpr float y = 0.46;
                    }; // struct Position

                }; // struct EndTurn

            }; // struct Button

        }; // struct Rendering

    }; // struct Settings

    struct Data {
        struct Attributes {
            uint16_t draw_player; // num player who graphics draw
            sf::RenderWindow window;
            sf::Vector2u default_window_size;
            std::vector<PlayerCard *> current_player_cards;
            std::vector<Deck<PlayerCard *> *> current_decks;
            std::vector<Base *> active_bases;
            std::vector<std::pair<Button::Type, sf::FloatRect>> buttuns;
        }; // struct Attributes
    }; // struct Data

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
