#include <algorithm>
#include "trick_500.h"

Trick_500::Trick_500()
   : CardCollection_500(4)
{
}

Game_500::player_t Trick_500::winner(Game_500::suit_t trumps) const
{
   return (Game_500::player_t)((leader + std::max_element(cards.begin(), cards.end()) - cards.begin()) % 4);
}

Card::suit_t Trick_500::led_suit(Game_500::suit_t trumps) const
{
   return cards.front()->suit(trumps);
}
