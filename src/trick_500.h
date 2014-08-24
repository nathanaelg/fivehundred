#ifndef _TRICK_500_H_
#define _TRICK_500_H_

#include "card_collection_500.h"

class Trick_500 : public CardCollection_500
{
public:
   Trick_500();

   Game_500::player_t leader;
   Game_500::player_t winner(Game_500::suit_t trumps) const;
   Card::suit_t led_suit(Game_500::suit_t trumps) const;
   std::string print() const;
};

#endif /* _TRICK_500_H_ */
