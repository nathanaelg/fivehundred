#include <string>
#include <map>
#include <iostream>
#include "card_500.h"

Card::Card(suit_t s, number_t n)
   : printed_suit(s), number(n)
{
}

Card::colour_t Card::colour() const
{
   static std::map <Card::suit_t, Card::colour_t> const colour_from_suit = {
      {Card::hearts, Card::red},
      {Card::diamonds, Card::red},
      {Card::spades, Card::black},
      {Card::clubs, Card::black},
      {Card::none, Card::neither}
   };
   return find_with_exception(colour_from_suit, printed_suit);
}

Card::suit_t Card::suit() const
{
   return printed_suit;
}

std::map <Game_500::suit_t, Card::colour_t> const Game_500::colour_from_suit = {
   {Game_500::hearts, Card::red},
   {Game_500::diamonds, Card::red},
   {Game_500::spades, Card::black},
   {Game_500::clubs, Card::black},
   {Game_500::no_trumps, Card::neither},
   {Game_500::misere, Card::neither}
};

bool operator== (Game_500::suit_t const s1, Card::suit_t const s2)
{
   if ((s1 == Game_500::hearts) && (s2 == Card::hearts)) return true;
   if ((s1 == Game_500::diamonds) && (s2 == Card::diamonds)) return true;
   if ((s1 == Game_500::clubs) && (s2 == Card::clubs)) return true;
   if ((s1 == Game_500::spades) && (s2 == Card::spades)) return true;
   return false;
}

Card::suit_t Game_500::suit_cast(Game_500::suit_t s)
{
   if (s == Game_500::hearts) return Card::hearts;
   if (s == Game_500::diamonds) return Card::diamonds;
   if (s == Game_500::clubs) return Card::clubs;
   if (s == Game_500::spades) return Card::spades;
   return Card::none;
}

std::string Card::print_full() const
{
   static std::map <Card::suit_t, std::string> const print_full_suit = {
      {Card::hearts, "Hearts"},
      {Card::diamonds, "Diamonds"},
      {Card::spades, "Spades"},
      {Card::clubs, "Clubs"}
   };
   static std::map <Card::number_t, std::string> const print_full_number = {
      {Card::ace, "Ace"}, 
      {Card::two, "2"}, 
      {Card::three, "3"}, 
      {Card::four, "4"}, 
      {Card::five, "5"}, 
      {Card::six, "6"}, 
      {Card::seven, "7"}, 
      {Card::eight, "8"}, 
      {Card::nine, "9"}, 
      {Card::ten, "10"}, 
      {Card::jack, "Jack"}, 
      {Card::queen, "Queen"}, 
      {Card::king, "King"}
   };

   if (number == joker) return "The Joker";
   return find_with_exception(print_full_number, number) + " of " + find_with_exception(print_full_suit, printed_suit);
}

std::string Card::print_short_suit() const
{
   static std::map <Card::suit_t, std::string> const print_short_suit = {
      {Card::hearts, "♥"},
      {Card::diamonds, "♦"},
      {Card::spades, "♠"},
      {Card::clubs, "♣"}
   };
   return find_with_exception(print_short_suit, printed_suit);
}

std::string Card::print_short_number() const
{
   static std::map <Card::number_t, std::string> const print_short_number = {
      {Card::ace, "A"}, 
      {Card::two, "2"}, 
      {Card::three, "3"}, 
      {Card::four, "4"}, 
      {Card::five, "5"}, 
      {Card::six, "6"}, 
      {Card::seven, "7"}, 
      {Card::eight, "8"}, 
      {Card::nine, "9"}, 
      {Card::ten, "10"}, 
      {Card::jack, "J"}, 
      {Card::queen, "Q"}, 
      {Card::king, "K"}
   };
   return find_with_exception(print_short_number, number);
}

std::string Card::print() const
{
   if (number == joker) return "Jo";
   return print_short_number() + print_short_suit();
}

Card_500::Card_500(suit_t s, number_t n)
   : Card(s, n)
{
}

Card::suit_t Card_500::suit(Game_500::suit_t trumps) const
{
   if ((number == Card::jack) && (find_with_exception(Game_500::colour_from_suit, trumps) == colour())) return Game_500::suit_cast(trumps);
   if ((number == Card::joker) && (find_with_exception(Game_500::colour_from_suit, trumps) != Card::neither)) return Game_500::suit_cast(trumps);

   return Card::suit();
}

unsigned Card_500::win_number(Game_500::suit_t trumps, Card::suit_t led) const
{
   static std::map <Card::number_t, unsigned> const card_order = {
      /* Joker is 20 for everything apart from misere */
      /* Jack is 19 or 18 for trumps */
      {Card::ace, 17}, 
      {Card::king, 16},
      {Card::queen, 15}, 
      /* Jack is 14 for no trumps */
      {Card::ten, 13}, 
      {Card::nine, 12}, 
      {Card::eight, 11}, 
      {Card::seven, 10}, 
      {Card::six, 9}, 
      {Card::five, 8}, 
      {Card::four, 7}, 
      {Card::three, 6}, 
      {Card::two, 5} 
      /* Joker is 4 for misere */
   };
   unsigned win_number;

   if (number == Card::jack)
   {
      win_number = (find_with_exception(Game_500::colour_from_suit, trumps) == colour()) ? 18 : 14;
      if (trumps == printed_suit) win_number = 19;
   }
   else if (number == Card::joker)
   {
      win_number = (trumps == Game_500::misere) ? 4 : 20;
      if (trumps == Game_500::no_trumps) win_number += 40;
   }
   else
   {
      win_number = find_with_exception(card_order, number);
   }

   if (led == suit(trumps)) win_number += 20;
   if (trumps == suit(trumps)) win_number += 40;

   //   std::cout << "Win number of " << print(false) << ": " << win_number << "\n";
   return win_number;
}

bool operator== (Card_500 const & c1, Card_500 const & c2)
{
  if (c1.printed_suit != c2.printed_suit) return false;
  if (c1.number != c2.number) return false;
  return true;
}
