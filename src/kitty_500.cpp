#include "kitty_500.h"

Kitty_500::Kitty_500()
   : CardCollection_500(3)
{
}

Card_500 * Kitty_500::pop()
{
   Card_500 * card = cards.back();
   cards.pop_back();
   return card;
}

std::string Kitty_500::print_name(unsigned number) const
{
   return "Ki";
}
