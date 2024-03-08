#ifndef GRAFICS_H
#define GRAFICS_H

#include <SFML/Graphics.hpp>
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

  private:
    class GameEvent {
      public:
        enum class EventType {
            place_card_to_base,
            place_card_to_deck,
            show_deck,
            show_base,
            end_turn,
            close_window,
            wait_event,
            no_event,
        };

      public:
        EventType type;
        const PlayerCard *card;
        const Base *base;
        const Deck<PlayerCard *> *deck;

      public:
        GameEvent(EventType type_ = EventType::no_event, const PlayerCard *card_ptr = nullptr,
                  const Base *base_ptr = nullptr, const Deck<PlayerCard *> *deck_ptr = nullptr)
            : type(type_), card(card_ptr), base(base_ptr), deck(deck_ptr) {}
        ~GameEvent() = default;
    };

  public:
    constexpr static const float player_scale_to_playground = 0.38;
    constexpr static const float player_increase = 1.8;
    constexpr static const float base_shift_to_playground = 0.1;
    constexpr static const float card_scale_to_player = 0.2;
    constexpr static const float bases_place_to_playground = 0.8;
    constexpr static const float cards_place_to_player = 0.6;
    constexpr static const float bases_pos_to_playground = 0.25;

  private:
    const GameType type_;
    uint16_t draw_player_; // num player who graphic draw
    GameEvent game_event_;

  public:
    sf::RenderWindow window;
    std::vector<PlayerCard *> current_player_cards;
    std::vector<Deck<PlayerCard *> *> current_decks;
    std::vector<Base *> active_bases;

  private:
    PlayerCard *pressed_card(float x, float y) const;
    Base *pressed_base(float x, float y) const;
    Deck<PlayerCard *> *pressed_deck(float x, float y) const;
    void parse_events(GameEvent &game_event);

  public:
    Graphics() = delete;
    Graphics(GameType type, uint16_t draw_player = 0);
    void process_events(Engine &engine);
    uint16_t get_draw_player() const;
    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif
