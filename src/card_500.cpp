#include <string>
#include <map>
#include <iostream>
#include "card_500.h"

Card::Card(suit_t s, number_t n)
   : suit(s), number(n)
{
   switch (suit)
   {
      case Card::hearts:
      case Card::diamonds:
         colour = red;
         break;
      case Card::spades:
      case Card::clubs:
         colour = black;
         break;
      case Card::none:
         colour = neither;
         break;
   }
}

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

std::string Card::print() const
{
   if (number == joker) return "Jo";
   return print_short_number() + print_short_suit();
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
   return find_with_exception(print_full_number, number) + " of " + find_with_exception(print_full_suit, suit);
}

std::string Card::print_short_suit() const
{
   static std::map <Card::suit_t, std::string> const print_short_suit = {
      {Card::hearts, "♥"},
      {Card::diamonds, "♦"},
      {Card::spades, "♠"},
      {Card::clubs, "♣"}
   };
   return find_with_exception(print_short_suit, suit);
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

Card_500::Card_500(suit_t s, number_t n)
   : Card(s, n), printed_suit(s)
{
}

static Card::colour_t const trumps_colour[] = {Card::red,      // Game_500::suit_t hearts
                                               Card::red,      // Game_500::suit_t diamonds
                                               Card::black,    // Game_500::suit_t clubs
                                               Card::black,    // Game_500::suit_t spades
                                               Card::neither,  // Game_500::suit_t no_trumps
                                               Card::neither}; // Game_500::suit_t misere

void Card_500::set_trumps(Game_500::suit_t trumps)
{
   if ((number == Card::jack) && (trumps_colour[trumps] == colour)) suit = Game_500::suit_cast(trumps);
   if ((number == Card::joker) && (trumps_colour[trumps] != Card::neither)) suit = Game_500::suit_cast(trumps);
}

unsigned Card_500::win_number(Game_500::suit_t trumps, Card::suit_t led) const
{
   // Card::number_t {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, joker};
   static unsigned const base_win[] = {17, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};
   unsigned win_number = base_win[number];

   if (number == Card::jack)
   {
      if (colour == trumps_colour[trumps]) win_number = 18;
      if (trumps == printed_suit) win_number = 19;
   }
   else if (number == Card::joker)
   {
      if (trumps == Game_500::misere) win_number = 4;
      if (trumps == Game_500::no_trumps) win_number += 40;
   }

   if (led == suit) win_number += 20;
   if (trumps == suit) win_number += 40;

   //   std::cout << "Win number of " << print(false) << ": " << win_number << "\n";
   return win_number;
}
