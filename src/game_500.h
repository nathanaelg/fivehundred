#ifndef _GAME_500_H_
#define _GAME_500_H_

#include <vector>
#include "card.h"

class Game_500
{
public:
   enum variant_t {two_player, two_player_dummy, three_player, three_player_dummy, four_player, five_player};
   enum suit_t {hearts, diamonds, clubs, spades, no_trumps, misere};
   static std::map <Game_500::suit_t, Card::colour_t> const colour_from_suit;
   friend bool operator== (Game_500::suit_t const s1, Card::suit_t const s2);
   static Card::suit_t suit_cast(suit_t s);
};

#endif /* _GAME_500_H_ */
