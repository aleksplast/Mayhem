#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "entity.h"
#include <cstdint>
#include <list>
#include <iostream>

namespace Mayhem {

template <class T> class Deck {
private:
    std::list<T> cards_;

public: // Iterator functions
    using container = std::list<T>;
    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;

    iterator begin() { return cards_.begin(); };
    iterator end() { return cards_.end(); };
    const_iterator begin() const { return cards_.begin(); };
    const_iterator end() const { return cards_.end(); };

public: // Interface functions
    void gain_card(const T* card) {
        cards_.push_back(*card);
    }
    void remove_card(const T& card) {
        int card_id = card.get_id();

        for (auto it_curr = cards_.begin(), it_end = cards_.end(); it_curr != it_end; ++it_curr) {
            if (card_id == it_curr->get_id()) {
                cards_.erase(it_curr);
                break;
            }
        }
    }
    std::size_t size() const {
        return cards_.size();
    }
    void shuffle() {
        cards_.sort(cards_.begin(), cards_.end(), cmp_func());
    }

int cmp_func() {
    return std::rand() - RAND_MAX / 2;
}
}; // class Deck

} // namespace Mayhem

#endif // DECK_H
