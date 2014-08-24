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
   std::string print();

protected:
   unsigned random_seed;
   std::vector<Card_500> cards;

   struct number_in_suit_compare
   {
      Card::suit_t suit;
      number_in_suit_compare(Card::suit_t s) { suit = s; }
      bool operator() (CardCollection_500 * l, CardCollection_500 * r)
      {
         return l->cards_in_suit(suit).size() < r->cards_in_suit(suit).size();
      }
   };

private:
   void deal(std::vector<CardCollection_500 *> hands_and_kitty);
};

#endif /* _DECK_500_H_ */
