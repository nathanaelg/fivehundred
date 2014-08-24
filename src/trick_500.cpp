#include <algorithm>
#include "trick_500.h"
#include "console.h"

Trick_500::Trick_500()
   : CardCollection_500(4)
{
}

Game_500::player_t Trick_500::winner(Game_500::suit_t trumps) const
{
   if (cards.size() != max_size()) throw std::runtime_error("Cannot calculate winner of unfinished trick.");

   auto winning_card_iterator = std::max_element(cards.begin(),
                                                 cards.end(),
                                                 win_number_compare(trumps, led_suit(trumps)));

   return (Game_500::player_t)((leader + winning_card_iterator - cards.begin()) % 4);
}

Card::suit_t Trick_500::led_suit(Game_500::suit_t trumps) const
{
   if (cards.size() == 0) return Card::none;
   return cards.front()->suit(trumps);
}

std::string Trick_500::print() const
{
   std::string output = fixed_width_string(cards.at(0)->print(), 4 * (leader + 1), right_side);
   for (unsigned i = 1; i < 4; i++) output += fixed_width_string(cards.at(i)->print(), 4, right_side);
   return output;
}
