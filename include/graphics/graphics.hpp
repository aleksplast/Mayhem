#ifndef GRAFICS_H
#define GRAFICS_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace Mayhem {

class PlayerCard;
class Base;
template <typename T> class Deck;
class Engine;

class Graphics {
  public:
    enum class GameType { ONLINE, OFLINE };

  public:
    class GameEvent {
      public:
        enum class EventType {
            no_event,
            place_card_to_base,
            place_card_to_deck,
            show_deck,
            show_base,
            end_turn,
            close_window,
            wait_event,
        };

      public:
        EventType type = EventType::no_event;
        const PlayerCard *card = nullptr;
        const Base *displayed_base = nullptr;
        const Deck<PlayerCard *> *displayed_deck = nullptr;
        const Base *base = nullptr;
        const Deck<PlayerCard *> *deck = nullptr;

      public:
        explicit GameEvent() = default;
        explicit GameEvent(EventType Type, const PlayerCard *Card = nullptr,
                           const Base *Displayed_base = nullptr, const Deck<PlayerCard *> *Displaed_deck = nullptr,
                           const Base *Base = nullptr, const Deck<PlayerCard *> *Deck = nullptr)
            : type(Type), card(Card), displayed_base(Displayed_base), displayed_deck(Displaed_deck), base(Base),
              deck(Deck) {}
        explicit GameEvent(const GameEvent &) = delete;
        explicit GameEvent(GameEvent &&) = delete;
        const GameEvent& operator=(const GameEvent &rhs);
        const GameEvent& operator=(GameEvent &&rhs);
        ~GameEvent() = default;
    };

    class LocationSettings {
      public:
        constexpr static const float player_scale_to_playground_x = 0.38;
        constexpr static const float player_scale_to_playground_y = 0.25;
        constexpr static const float player_increase = 1.6;

        constexpr static const float bases_place_to_playground_x = 0.8;
        constexpr static const float bases_plase_to_playground_y = 0.2;
        constexpr static const float bases_scale_to_place_x = 0.15;
        constexpr static const float bases_scale_to_place_y = 1;
        constexpr static const float bases_pos_to_playground = 0.2;

        constexpr static const float showen_place_size_to_playground_x = 0.7;
        constexpr static const float showen_place_pos_to_playground_y = 0.6;
        constexpr static const float showen_card_scale_to_playground_x = 0.1;
        constexpr static const float showen_card_scale_to_playground_y = 0.2;

        constexpr static const float cards_place_to_player_x = 0.6;
        constexpr static const float cards_place_to_player_y = 0.8;
        constexpr static const float card_scale_to_player_x = 0.2;
        constexpr static const float card_scale_to_player_y = 0.8;
    };

    class DrawingAttributes {
      public:
        uint16_t draw_player; // num player who graphic draw
        sf::RenderWindow window;
        sf::Vector2u default_window_size;
        std::vector<PlayerCard *> current_player_cards;
        std::vector<Deck<PlayerCard *> *> current_decks;
        std::vector<Base *> active_bases;
    };

  private:
    GameType type_;

  public:
    DrawingAttributes attributes;

  private:
    PlayerCard *pressed_card(const sf::Vector2f &pos) const;
    Base *pressed_base(const sf::Vector2f &pos) const;
    Deck<PlayerCard *> *pressed_deck(const sf::Vector2f &pos) const;
    void parse_events(GameEvent &game_event);
    void get_event_parameters(const sf::Event &event, GameEvent &game_event) const;

  public:
    Graphics();
    void process_events(Engine &engine);
    void launch_game(Engine &engine);
    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif
