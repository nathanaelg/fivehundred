#include <algorithm>
#include "card_collection_500.h"

CardCollection_500::CardCollection_500(unsigned max_size)
   : _max_size(max_size), _deal_size(max_size)
{
}

CardCollection_500::CardCollection_500(unsigned max_size, unsigned deal_size)
   : _max_size(max_size), _deal_size(deal_size)
{
}

unsigned CardCollection_500::size() const
{
   return cards.size();
}

unsigned CardCollection_500::max_size() const
{
   return _max_size;
}

unsigned CardCollection_500::deal_size() const
{
   return _deal_size;
}

void CardCollection_500::add_card(Card_500 * card)
{
   if (cards.size() == _max_size) throw std::runtime_error("CardCollection can only contain " + std::to_string(_max_size) + " cards, cannot add another.");
   cards.push_back(card);
}

Card_500 * CardCollection_500::remove_card(Card_500 * card)
{
   for (std::vector<Card_500 *>::iterator i = cards.begin();
        i != cards.end();
        i++)
   {
      if (*(*i) != *card) continue;
      cards.erase(i);
      return card;
   }
   throw std::runtime_error("Could not find card in hand.");
}

bool CardCollection_500::has_card(Card_500 * card) const
{
   if (std::find(cards.begin(), cards.end(), card) == cards.end()) return false;
   return true;
}

void CardCollection_500::sort(Game_500::suit_t trumps, Card::suit_t led)
{
   std::sort(cards.begin(), cards.end(), number_compare(trumps, led));
   std::sort(cards.begin(), cards.end(), suit_compare(trumps));
}

std::string CardCollection_500::print() const
{
   std::string output = "{";
   for (Card_500 * c : cards) output += c->print() + ",";
   return output.replace(output.end()-1, output.end(), "}");
}

std::string CardCollection_500::print_name(unsigned number) const
{
   throw std::runtime_error("CardCollection_500 class should not call print_name.");
}

std::vector<Card_500 *> CardCollection_500::cards_in_suit(Card::suit_t suit, Game_500::suit_t trumps) const
{
   std::vector<Card_500 *> cards_in_suit;
   for (Card_500 * c : cards) if (c->suit(trumps) == suit) cards_in_suit.push_back(c);
   return cards_in_suit;
}
