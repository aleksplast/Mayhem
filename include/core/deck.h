#ifndef DECK_H
#define DECK_H

#include <algorithm>
#include <cstdint>
#include <cstdlib>
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
    Deck() {};
    void gain_card(const T& card);
    void remove_card(const T &card);
    std::size_t size() const;
    void shuffle();
    T take_card();

}; // class Deck

} // namespace Mayhem

#include "deck.tpp"

#endif // DECK_H
