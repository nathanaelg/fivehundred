#ifndef _GAME_500_H_
#define _GAME_500_H_

#include <vector>
#include "card.h"

class Game_500
{
public:
   enum variant_t {two_player, two_player_dummy, three_player, three_player_dummy, four_player, five_player};
   enum suit_t {hearts, diamonds, clubs, spades, no_trumps, misere};
};

#endif /* _GAME_500_H_ */
