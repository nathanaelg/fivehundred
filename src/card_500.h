#ifndef _CARD_500_H_
#define _CARD_500_H_

#include "card.h"
#include "game_500.h"

class Card_500 : public Card
{
public:
   Card_500(suit_t s, number_t n);
   void set_trumps(Game_500::suit_t trumps);
   friend bool operator== (Card_500 const &, Card_500 const &);
   unsigned win_number(Game_500::suit_t trumps, Card::suit_t led) const;

private:
   suit_t printed_suit;
};

#endif /* _CARD_500_H_ */

