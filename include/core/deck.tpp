#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <random>
#include <vector>

namespace Mayhem {

template <class T> void Deck<T>::clear_deck() {
    for (size_t i = 0, sz = size(); i < sz; ++i) {
        take_card();
    }
}

template <class T> void Deck<T>::gain_card(const T &card) { cards_.push_back(card); }

template <class T> void Deck<T>::remove_card(const T &card) {
    int card_id = card->get_id();

    auto erase_card = std::find_if(cards_.begin(), cards_.end(),
                                   [&card_id](const T &find_card) { return find_card->get_id() == card_id; });

    if (erase_card != cards_.end()) {
        cards_.erase(erase_card);
    }
}

template <class T> size_t Deck<T>::size() const { return cards_.size(); }

template <class T> void Deck<T>::shuffle() {
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

    std::vector<T> vec(cards_.begin(), cards_.end());
    cards_.clear();
    std::shuffle(vec.begin(), vec.end(), gen);
    std::copy(vec.begin(), vec.end(), std::back_inserter(cards_));
}

template <class T> T Deck<T>::take_card() {
    T card = cards_.back();
    cards_.pop_back();
    return card;
}

template <class T> void Deck<T>::dump_state(std::ostream &os) const {
    for (auto &item : cards_) {
        item->dump_state(os);
    }
}

template <class T> void Deck<T>::show_cards(GraphicsModel::Data::Attributes &attributes) const {
    using Scope = GraphicsModel::Settings::Rendering::ShowenPlace;
    sf::Vector2f place_size = sf::Vector2f(attributes.default_window_size.x * Scope::Scale::x,
                                           attributes.default_window_size.y * Scope::Scale::y);

    sf::Vector2f place_pos = sf::Vector2f(attributes.default_window_size.x * Scope::Position::x,
                                          attributes.default_window_size.y * Scope::Position::y);

    sf::Vector2f card_size = sf::Vector2f(place_size.x * Scope::Card::Scale::x, place_size.y * Scope::Card::Scale::y);

    float num_cards = cards_.size();
    float card_index = 1.0;

    for (auto it = cards_.begin(); it != cards_.end(); ++it, card_index += 1.0) {
        (*it)->set_main_texture();
        (*it)->draw(attributes.window,
                    sf::FloatRect(place_pos.x +
                                      (card_index - (num_cards + 1.0) / 2) * place_size.x / (num_cards + 1.0) -
                                      card_size.x / 2,
                                  place_pos.y - card_size.y / 2, card_size.x, card_size.y),
                    0);
        attributes.shown_place.second.push_back(*it);
    }
}

} // namespace Mayhem
