#include <algorithm>
#include <cstdlib>

namespace Mayhem {

template <class T> void Deck<T>::gain_card(const T *card) { cards_.push_back(*card); }

template <class T> void Deck<T>::remove_card(const T &card) {
    int card_id = card.get_id();

    for (auto it_curr = cards_.begin(), it_end = cards_.end(); it_curr != it_end; ++it_curr) {
        if (card_id == it_curr->get_id()) {
            cards_.erase(it_curr);
            break;
        }
    }
}

template <class T> std::size_t Deck<T>::size() const { return cards_.size(); }

template <class T> void Deck<T>::shuffle() { std::shuffle(cards_.begin(), cards_.end()); }

template <class T> T Deck<T>::take_card() {
    T card = cards_.back();
    cards_.pop_back();
    return card;
};
} // namespace Mayhem
