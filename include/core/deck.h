#ifndef DECK_H
#define DECK_H

#include <cstdint>
#include <list>

namespace Mayhem {

template <class T>
class Deck {
private:
    std::list<T> cards_;

public:
    void gain_card(const T* card);
    void remove_card(const T& card);
    void shuffle();
}; // class Deck

} // namespace Mayhem

#endif // DECK_H
