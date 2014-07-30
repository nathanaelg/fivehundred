#ifndef _CARD_500_H_
#define _CARD_500_H_

#include "card.h"
#include "game_500.h"

class Card_500 : public Card
{
public:
   Card_500(suit_t s, number_t n);
   friend bool operator== (Card_500 const &, Card_500 const &);
   Card::suit_t suit(Game_500::suit_t trumps) const;
   unsigned win_number(Game_500::suit_t trumps, Card::suit_t led) const;
};

#endif /* _CARD_500_H_ */

