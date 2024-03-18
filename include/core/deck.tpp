#include <algorithm>
#include <cstdlib>

namespace Mayhem {

template <class T> void Deck<T>::clear_deck() {
    for (size_t i = 0, sz = size(); i < sz; ++i) {
        auto _ = take_card();
    }
}

template <class T> void Deck<T>::gain_card(const T &card) { cards_.push_back(card); }

template <class T> void Deck<T>::remove_card(const T &card) {
    int card_id = card->get_id();

    for (auto it_curr = cards_.begin(), it_end = cards_.end(); it_curr != it_end; ++it_curr) {
        if (card_id == (*it_curr)->get_id()) {
            cards_.erase(it_curr);
            break;
        }
    }
}

template <class T> std::size_t Deck<T>::size() const { return cards_.size(); }

// template <class T> void Deck<T>::shuffle() { std::random_shuffle(cards_.begin(), cards_.end()); }

template <class T> T Deck<T>::take_card() {
    T card = cards_.back();
    cards_.pop_back();
    return card;
}

template <class T> void Deck<T>::dump_state(std::ofstream &os) const {
    for (auto &item : cards_) {
        item->dump_state(os);
    }
}

template <class T> void Deck<T>::show_cards(Graphics::DrawingAttributes &attributes) const {
    sf::Vector2f place_settings =
        sf::Vector2f(attributes.default_window_size.x * Graphics::LocationSettings::showen_place_size_to_playground_x,
                     attributes.default_window_size.y *
                         Graphics::LocationSettings::showen_place_pos_to_playground_y); // x_scale and y_pos

    sf::Vector2f card_size =
        sf::Vector2f(attributes.default_window_size.x * Graphics::LocationSettings::showen_card_scale_to_playground_x,
                     attributes.default_window_size.y * Graphics::LocationSettings::showen_card_scale_to_playground_y);

    float num_cards = cards_.size();
    float card_index = 1.0;

    for (auto it = cards_.begin(); it != cards_.end(); ++it, card_index += 1.0) {
        (*it)->draw(attributes.window,
                    sf::FloatRect(attributes.default_window_size.x / 2 +
                                      (card_index - (num_cards + 1.0) / 2) * place_settings.x / (num_cards + 1.0) -
                                      card_size.x / 2,
                                  place_settings.y - card_size.y / 2, card_size.x, card_size.y),
                    0);
    }
}
} // namespace Mayhem
