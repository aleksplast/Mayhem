#ifndef GRAPHICS_MODEL_HPP
#define GRAPHICS_MODEL_HPP

#include "graphics/button.hpp"

namespace Mayhem {

class Engine;
class PlayerCard;
class Base;
template <class T> class Deck;

/// The graphics class responsible for data storage
class GraphicsModel {
  public:
    /// Graphics settings
    struct Settings {

        /// Game types
        enum class GameType {
            online,  ///< Online game
            offline, ///< Offline game
        };           // enum class GameType

        /// The structure describing the location of entities on the window
        struct Rendering {

            /// Drawing player
            struct Player {

                /// Relative scale to the playground
                struct Scale {
                    static constexpr float x = 0.38f; ///< Scale on the x axis
                    static constexpr float y = 0.25f; ///< Scale on the y axis
                };                                    // struct Slace

                /// Increasing the size of the main player
                static constexpr float increase = 1.6f;

                /// Drawing Cards' place
                struct CardsPlace {

                    /// Relative scale to the player
                    struct Scale {
                        static constexpr float x = 0.7f;  ///< Scale on the x axis
                        static constexpr float y = 0.75f; ///< Scale on the y axis
                    };                                    // struct Scale

                    /// Relative position to the player
                    struct Position {
                        static constexpr float x = 0.5f; ///< Position on the x axis
                        static constexpr float y = 0.5f; ///< Position on the y axis
                    };                                   // struct Position

                    // Drawing card
                    struct Card {

                        /// Relative scale to the cards place
                        struct Scale {
                            static constexpr float x = 0.25f; ///< Scale on the x axis
                            static constexpr float y = 1.0f;  ///< Scale on the y axis
                        };                                    // struct Scale
                    };                                        // struct Card
                };                                            // struct CardsPlace
            };                                                // struct Player

            /// Displaying a place with the main cards
            struct ShowenPlace {

                /// Relative scale to the playground
                struct Scale {
                    static constexpr float x = 0.8f;  ///< Scale on the x axis
                    static constexpr float y = 0.25f; ///< Scale on the y axis
                };                                    // struct Scale

                /// Relative position to the playground
                struct Position {
                    static constexpr float x = 0.5f;  ///< Position on the x axis
                    static constexpr float y = 0.65f; ///< Position on the y axis
                };                                    // struct Position

                /// Drawing card
                struct Card {

                    /// Relative scale to the showen palce
                    struct Scale {
                        static constexpr float x = 0.12f; ///< Scale on the x axis
                        static constexpr float y = 1.0f;  ///< Scale on the y axis
                    };                                    // struct Scale
                };                                        // struct Card

            }; // struct ShowenPlace

            /// Drawing the place where the bases are located
            struct BasesPlace {

                /// Relative scale to the playgorund
                struct Scale {
                    static constexpr float x = 0.8f; ///< Scale on the x axis
                    static constexpr float y = 0.2f; ///< Scale on the y axis
                };                                   // struct Scale

                /// Relative position to the playground
                struct Position {
                    static constexpr float x = 0.5f; ///< Position on the x axis
                    static constexpr float y = 0.3f; ///< Position on the y axis
                };                                   // struct Position

                /// Drawing Bases
                struct Base {

                    /// Relative scale to the Base place
                    struct Scale {
                        static constexpr float x = 0.15f; ///< Scale on the x axis
                        static constexpr float y = 1.0f;  ///< Scale on the y axis
                    };                                    // struct Scale

                }; // struct Base

            }; // strust BasesPlace

            /// Drawing Buttons
            struct Button {

                /// Drawing Button end_turn
                struct EndTurn {

                    /// Relative scale to the playground
                    struct Scale {
                        static constexpr float x = 0.1f;  ///< Scale on the x axis
                        static constexpr float y = 0.08f; ///< Scale on the y axis
                    };                                    // struct Scale

                    // Relative position to the playground
                    struct Position {
                        static constexpr float x = 0.82f; ///< Position on the x axis
                        static constexpr float y = 0.46f; ///< Position on the y axis
                    };                                    // struct Position

                }; // struct EndTurn

                /// Drawing power icon
                struct Power {

                    /// Relative scale to the playground
                    struct Scale {
                        static constexpr float x = 0.18f; ///< Scale on the x axis
                        static constexpr float y = 0.1f;  ///< Scale on the y axis
                    };                                    // struct Scale
                };                                        // struct Power

                /// Player points
                struct Points {

                    /// Relative scale to the playground
                    struct Scale {
                        static constexpr float x = 0.15f; ///< Scale on the x axis
                        static constexpr float y = 0.15f; ///< Scale on the y axis
                    };                                    // struct Scale
                };                                        // struct Points

                /// Drawing summary units power on base
                struct UnitsPower {

                    /// Relative scale to the player
                    struct Scale {
                        static constexpr float x = 0.7f; ///< Scale on the x axis
                        static constexpr float y = 0.2f; ///< Scale on the y axis
                    };                                   // struct Scale

                    /// Relative position to the player
                    struct Position {
                        static constexpr float x = 0.5f;  ///< Position on the x axis
                        static constexpr float y = -0.1f; ///< Position on the y axis
                    };                                    // struct Position
                };                                        // struct UnitsPower

                /// Drawing buttons on Screen
                struct ScreenButtons {

                    /// Relative offset to the screen
                    struct Offset {
                        static constexpr float x = 0.5f;     ///< Offset on the x axis
                        static constexpr float y = 0.15f;    ///< offset on the y axis
                        static constexpr float start = 0.2f; ///< initial y axis offset
                    };                                       // struct Offset

                    /// Relative scale to the screen
                    struct Scale {
                        static constexpr float x = 0.28f; ///< Scale on the x axis
                        static constexpr float y = 0.12f; ///< Scale on the y axis
                    };                                    // struct Scale

                    static constexpr unsigned int char_size = 36u; ///< Char size
                };                                                 // struct ScreenButtons
            };                                                     // struct Button

            /// Drawing poppong up card
            struct PopUpCard {

                /// Relative scale to the playground
                struct Scale {
                    static constexpr float x = 0.13f; ///< Scale on the x axis
                    static constexpr float y = 0.35f; ///< Scale on the y axis
                };                                    // struct Scale

                /// Relative position to  the playground
                struct Position {
                    static constexpr float x = 0.13f; ///< Position on the x axis
                    static constexpr float y = 0.5f;  ///< Position on the y axis
                };                                    // struct Position
            };                                        // struct PopUpCard
        };                                            // struct Rendering

    }; // struct Settings

    /// The data set for graphics
    struct Data {

        /// Attibutes for drawing entities
        struct Attributes {
            /// @brief Num player who graphics draw
            uint16_t draw_player = 0;

            /// @brief Reference to the window
            sf::RenderWindow &window;

            /// @brief Default window size
            sf::Vector2u default_window_size = sf::Vector2u();

            /// @brief The cards of the player being drawn
            std::vector<PlayerCard *> current_player_cards = std::vector<PlayerCard *>();

            /// @brief The decks of the player being drawn
            std::vector<Deck<PlayerCard *> *> current_decks = std::vector<Deck<PlayerCard *> *>();

            /// @brief The bases being drawn
            std::vector<Base *> active_bases = std::vector<Base *>();

            /// @brief The buttons being drawn
            std::vector<std::pair<Button::Type, sf::FloatRect>> buttuns =
                std::vector<std::pair<Button::Type, sf::FloatRect>>();
            std::pair<Base *, std::vector<PlayerCard *>> shown_place = std::pair<Base *, std::vector<PlayerCard *>>();

            /// @brief A map with a description
            PlayerCard *popping_up_card = nullptr;

          public:
            Attributes() = delete;
            Attributes(const Attributes &) = delete;
            Attributes(Attributes &&) = delete;
            Attributes &operator=(const Attributes &) = delete;
            Attributes &operator=(Attributes &&) = delete;

            /// @brief Constructor
            /// @param[out] Window Window
            Attributes(sf::RenderWindow &Window) : window(Window){};

            /// @brief Destructor
            ~Attributes() = default;
        }; // struct Attributes

        /// Attributes for menu
        struct MenuAttributes {
            /// Actions of game
            enum class GameAction {
                play,
                exit,
            }; // enum class GameAction

            /// @brief Default window size
            sf::Vector2u default_window_size = sf::Vector2u();

            /// @brief Type of game
            Settings::GameType type = Settings::GameType::offline;

            /// @brief Action of game
            GameAction action = GameAction::exit;
            /// @brief Number of players
            uint16_t num_players = 4;
            uint16_t number_of_player;
        }; // struct MenuAttributes
    };     // struct Data

  public:
    /// @brief Attributes of the game
    Data::Attributes attributes;
    /// @brief Type of game
    Settings::GameType type = Settings::GameType::offline;
    /// @brief Reference to the engine
    Engine &engine;

  public:
    GraphicsModel() = delete;
    /// @brief Constructor
    /// @param[out] e Reference to the engine
    /// @param[out] window Window
    /// @param[in] menu_attributes Game parameters
    GraphicsModel(Engine &e, sf::RenderWindow &window, const Data::MenuAttributes &menu_attributes);
    /// @brief Destructor
    ~GraphicsModel() = default;

}; // class GraphicsModel

} // namespace Mayhem

#endif // GRAPHICS_MODEL_HPP
