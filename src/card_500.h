#ifndef _CARD_500_H_
#define _CARD_500_H_

#include "card.h"
#include "game_500.h"

class Card_500 : public Card
{
public:
   Card_500(number_t number, suit_t suit = none);

   suit_t suit(Game_500::suit_t trumps) const;
   unsigned win_number(Game_500::suit_t trumps, Card::suit_t led) const;

protected:
   bool card_and_game_suit_equal(Card::suit_t card_suit, Game_500::suit_t game_suit) const;
};

#endif /* _CARD_500_H_ */
