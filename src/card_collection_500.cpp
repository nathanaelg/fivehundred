#include <algorithm>
#include "card_collection_500.h"

CardCollection_500::CardCollection_500(unsigned max_size)
   : max_size_(max_size), deal_size_(max_size)
{
}

CardCollection_500::CardCollection_500(unsigned max_size, unsigned deal_size)
   : max_size_(max_size), deal_size_(deal_size)
{
}

unsigned CardCollection_500::size() const
{
   return cards.size();
}

unsigned CardCollection_500::max_size() const
{
   return max_size_;
}

unsigned CardCollection_500::deal_size() const
{
   return deal_size_;
}

void CardCollection_500::add_card(Card_500 * card)
{
   if (cards.size() == max_size_) throw std::runtime_error("CardCollection can only contain "
                                                           + std::to_string(max_size_)
                                                           + " cards, cannot add another.");
   cards.push_back(card);
}

void CardCollection_500::remove_card(Card_500 * card)
{
   auto card_iterator = std::find_if(cards.begin(),
                                     cards.end(),
                                     [card](Card_500 const * c) { return (*c == *card); });

   if (card_iterator == cards.end()) throw std::runtime_error("Could not find card in hand.");

   cards.erase(card_iterator);
}

void CardCollection_500::remove_card(Card::number_t number, Card::suit_t suit)
{
   Card_500 card = Card_500(number, suit);
   remove_card(&card);
}

bool CardCollection_500::has_card(Card_500 * card) const
{
   auto card_iterator = std::find_if(cards.begin(),
                                     cards.end(),
                                     [card](Card_500 const * c) { return (*c == *card); });

   return (card_iterator != cards.end());
}

bool CardCollection_500::has_card(Card::number_t number, Card::suit_t suit) const
{
   Card_500 card = Card_500(number, suit);
   return has_card(&card);
}

void CardCollection_500::sort(Game_500::suit_t trumps, Card::suit_t led)
{
   std::sort(cards.begin(), cards.end(), win_number_compare(trumps, led));
   std::reverse(cards.begin(), cards.end());
   std::sort(cards.begin(),
             cards.end(),
             [trumps] (Card_500 * l, Card_500 * r) { return l->suit(trumps) < r->suit(trumps); });
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

std::vector<Card_500 *> CardCollection_500::all_cards() const
{
   return cards;
}
