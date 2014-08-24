#include <algorithm>
#include "deck_500.h"
#include "console.h"

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

   std::vector<CardCollection_500 *> hands_and_kitty = {
      &hands->at(0), &hands->at(1), &hands->at(2), &hands->at(3), kitty
   };

   deal(hands_and_kitty);
}

Card_500 * Deck_500::find(Card::number_t number, Card::suit_t suit)
{
   Card_500 card = Card_500(number, suit);
   std::vector<Card_500>::iterator c = std::find(cards.begin(), cards.end(), card);
   return (c == cards.end()) ? 0 : &(*c);
}

void Deck_500::deal(std::vector<CardCollection_500 *> hands_and_kitty)
{
   Card_500 * c = &cards.front();
   for (CardCollection_500 * h : hands_and_kitty)
   {
      for (unsigned i = 0; i < h->deal_size(); i++) h->add_card(c++);
      h->sort(Game_500::no_trumps);
   }
}

std::string Deck_500::print()
{
   std::vector<Hand_500> hands(4);
   Kitty_500 kitty;
   std::vector<CardCollection_500 *> hands_and_kitty = {
      &hands.at(0), &hands.at(1), &hands.at(2), &hands.at(3), &kitty
   };

   std::array<Card::suit_t, 5> suits = {{Card::none, Card::hearts, Card::diamonds, Card::clubs, Card::spades}};
   std::array<unsigned, 5> max_in_suit = {{0, 0, 0, 0, 0}};
   std::array<std::string, 5> titles = {{"", "Hearts", "Diamonds", "Clubs", "Spades"}};

   deal(hands_and_kitty);

   // Calculate column widths
   std::string output = "    ";
   for (unsigned i = 0; i < suits.size(); i++)
   {
      auto hand_iterator = std::max_element(hands_and_kitty.begin(),
                                            hands_and_kitty.end(),
                                            number_in_suit_compare(suits[i]));
      max_in_suit[suits[i]] = (*hand_iterator)->cards_in_suit(suits[i]).size();
      output += fixed_width_string(titles[i], max_in_suit[i] * 4 + 1, left_side);
   }

   // Print each hand/kitty as a row
   unsigned player_n = 1;
   for (CardCollection_500 * h : hands_and_kitty)
   {
      output += "\n" + h->print_name(player_n++);

      for (unsigned i = 0; i < suits.size(); i++)
      {
         std::string cards_in_one_suit = "";
         for (Card_500 * c : h->cards_in_suit(suits[i]))
         {
            cards_in_one_suit += fixed_width_string(c->print(), 4, right_side);
         }

         output += fixed_width_string(cards_in_one_suit, max_in_suit[i] * 4 + 1, left_side);
      }
   }

   return output + "\n";
}
