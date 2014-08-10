#include <algorithm>
#include "deck_500.h"

Deck_500::Deck_500()
{
   Card::suit_t suits[] = {Card::hearts, Card::diamonds, Card::clubs, Card::spades};
   Card::number_t numbers[] = {Card::ace, Card::five, Card::six, Card::seven, Card::eight,
                               Card::nine, Card::ten, Card::jack, Card::queen, Card::king};

   for (Card::suit_t suit : suits)
   {
      for (Card::number_t number : numbers) cards.emplace_back(number, suit);
   }

   cards.emplace_back(Card::four, Card::hearts);
   cards.emplace_back(Card::four, Card::diamonds);
   cards.emplace_back(Card::joker);
}

void Deck_500::shuffle()
{
   std::srand(random_seed);
   std::random_shuffle(cards.begin(), cards.end());
}

void Deck_500::srand(unsigned seed)
{
  random_seed = seed;
}

void Deck_500::deal(std::vector<Hand_500> * hands, Kitty_500 * kitty)
{
   if (hands->size() != 4) throw std::runtime_error("Invalid number of hands passed in for deal.");

   shuffle();

   std::vector<Card_500>::iterator c = cards.begin();
   for (Hand_500 & h : *hands)
   {
      for (unsigned i = 0; i < h.deal_size(); i++) h.add_card(&(*c++));
   }
   for (Hand_500 & h : *hands) h.sort(Game_500::no_trumps);

   for (unsigned i = 0; i < kitty->deal_size(); i++) kitty->add_card(&(*c++));
   kitty->sort(Game_500::no_trumps);
}

Card_500 * Deck_500::find(Card::number_t number, Card::suit_t suit)
{
   Card_500 card = Card_500(number, suit);
   std::vector<Card_500>::iterator c = std::find(cards.begin(), cards.end(), card);
   return (c == cards.end()) ? 0 : &(*c);
}
