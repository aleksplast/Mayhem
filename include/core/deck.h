#ifndef DECK_H
#define DECK_H

#include "graphics/drawable.hpp"
#include "graphics/graphics.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <list>

namespace Mayhem {

template <class T> class Deck : public Drawable {
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
    Deck() = default;
    Deck(const std::string &deck_file) : Drawable(deck_file){};

    // Destroy all cards in deck
    void clear_deck();

    // Add card to the deck
    void gain_card(const T &card);

    // Remove card from deck
    void remove_card(const T &card);

    // Dump state of the deck
    void dump_state(std::ofstream &os) const;

    // Number of cards in the deck
    size_t size() const;

    // Shuffle cards in the deck
    void shuffle();

    // Get top card from the deck and remove it from deck
    T take_card();

  public: // graphics functions
    // Show cards in deck
    void show_cards(Graphics::DrawingAttributes &attributes) const;

}; // class Deck

} // namespace Mayhem

#include "deck.tpp"

#endif // DECK_H
