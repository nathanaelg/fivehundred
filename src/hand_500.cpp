#include "hand_500.h"

Hand_500::Hand_500()
   : CardCollection_500(13, 10)
{
}

std::vector<Card_500 *> Hand_500::valid_moves(Game_500::suit_t trumps, Card::suit_t led) const
{
   if (led == Card::none) return cards;
   std::vector<Card_500 *> cards_in_led_suit = cards_in_suit(led, trumps);
   return cards_in_led_suit.empty() ? cards : cards_in_led_suit;
}

bool Hand_500::is_valid_move(Game_500::suit_t trumps, Card::suit_t led, Card_500 * card) const
{
   if (led == Card::none) return true;
   if (card->suit(trumps) == led) return true;
   if (cards_in_suit(led, trumps).empty()) return true;
   return false;
}

std::string Hand_500::print_name(unsigned number) const
{
   return "P" + std::to_string(number);
}
