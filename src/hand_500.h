#ifndef _HAND_500_H_
#define _HAND_500_H_

#include "card_collection_500.h"

class Hand_500 : public CardCollection_500
{
public:
   Hand_500();

   std::vector<Card_500 *> valid_moves(Game_500::suit_t trumps, Card::suit_t led) const;
   bool is_valid_move(Game_500::suit_t trumps, Card::suit_t led, Card_500 * card) const;

   std::string print_name(unsigned number) const;
};

#endif /* _HAND_500_H_ */
