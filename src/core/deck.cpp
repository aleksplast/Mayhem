#include "../../include/core/deck.h"

#include <algorithm>
#include <cstdlib>

namespace Mayhem {

int cmp_func() {
    return std::rand() - RAND_MAX / 2;
}

template<class T>
void Deck<T>::gain_card(const T* card) {
    cards_.push_back(*card);
}

template<class T>
void Deck<T>::remove_card(const T& card) {
    int card_id = card.get_id();

    for (auto it_curr = cards_.begin(), it_end = cards_.end(); it_curr != it_end; ++it_curr) {
        if (card_id == *it_curr.get_id()) {
            cards_.erase(*it_curr);
        }
    }
}

template<class T>
void Deck<T>::shuffle() {
    cards_.sort(cards_.begin(), cards_.end(), cmp_func());
}

} // namespace Mayhem
