#ifndef _DECK_500_H_
#define _DECK_500_H_

#include "hand_500.h"
#include "kitty_500.h"

class Deck_500
{
public:
   Deck_500();
   void shuffle();
   void srand(unsigned seed);
   void deal(std::vector<Hand_500> * hands, Kitty_500 * kitty);
   Card_500 * find(Card::number_t number, Card::suit_t suit);

protected:
   unsigned random_seed;
   std::vector<Card_500> cards;
};

#endif /* _DECK_500_H_ */
