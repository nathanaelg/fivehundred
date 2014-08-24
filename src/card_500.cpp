#include <string>
#include <map>
#include <iostream>
#include "card_500.h"

static Card::colour_t const suit_colour[] = {
   [Card::none] = Card::neither,
   [Card::hearts] = Card::red,
   [Card::diamonds] = Card::red,
   [Card::clubs] = Card::black,
   [Card::spades] = Card::black
};

Card::Card(number_t number, suit_t suit)
   : _suit(suit), _number(number), _colour(suit_colour[suit])
{
}

bool operator== (Card const &c1, Card const &c2)
{
   if (c1.suit() != c2.suit()) return false;
   if (c1.number() != c2.number()) return false;
   return true;
}

bool operator!= (Card const &c1, Card const &c2)
{
   return !(c1 == c2);
}

Card::suit_t Card::suit() const
{
   return _suit;
}

Card::number_t Card::number() const
{
   return _number;
}

Card::colour_t Card::colour() const
{
   return _colour;
}

std::string Card::print() const
{
   if (_number == joker) return "Jo";
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

   if (_number == joker) return "The Joker";
   return find_with_exception(print_full_number, _number) + " of " + find_with_exception(print_full_suit, _suit);
}

std::string Card::print_short_suit() const
{
   static std::map <Card::suit_t, std::string> const print_short_suit = {
      {Card::hearts, "♥"},
      {Card::diamonds, "♦"},
      {Card::spades, "♠"},
      {Card::clubs, "♣"}
   };
   return find_with_exception(print_short_suit, _suit);
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
   return find_with_exception(print_short_number, _number);
}

Card_500::Card_500(number_t number, suit_t suit)
   : Card(number, suit)
{
}

static Card::colour_t const trumps_colour[] = {
   [Game_500::none] = Card::neither,
   [Game_500::hearts] = Card::red,
   [Game_500::diamonds] = Card::red,
   [Game_500::clubs] = Card::black,
   [Game_500::spades] = Card::black,
   [Game_500::no_trumps] = Card::neither,
   [Game_500::misere] = Card::neither
};

static Card::suit_t const card_from_game_suit[] = {
   [Game_500::none] = Card::none,
   [Game_500::hearts] = Card::hearts,
   [Game_500::diamonds] = Card::diamonds,
   [Game_500::clubs] = Card::clubs,
   [Game_500::spades] = Card::spades
};

Card::suit_t Card_500::suit(Game_500::suit_t trumps) const
{
   if ((_number == Card::jack) &&
       (_colour == trumps_colour[trumps])) return card_from_game_suit[trumps];

   if ((_number == Card::joker) &&
       (trumps_colour[trumps] != Card::neither)) return card_from_game_suit[trumps];

   return _suit;
}

bool Card_500::card_and_game_suit_equal(Card::suit_t card_suit, Game_500::suit_t game_suit) const
{
   if (card_suit == Card::none) return false;
   if (card_from_game_suit[game_suit] == card_suit) return true;
   return false;
}

unsigned Card_500::win_number(Game_500::suit_t trumps, Card::suit_t led) const
{
   // Card::number_t {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, joker};
   static unsigned const base_win[] = {17, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};
   unsigned win_number = base_win[_number];

   if (_number == Card::jack)
   {
      if (_colour == trumps_colour[trumps]) win_number = 18;
      if (card_and_game_suit_equal(_suit, trumps)) win_number = 19;
   }
   else if (_number == Card::joker)
   {
      if (trumps == Game_500::misere) win_number = 4;
      if (trumps == Game_500::no_trumps) win_number += 40;
   }

   if (led == suit(trumps)) win_number += 20;
   if (card_and_game_suit_equal(suit(trumps), trumps)) win_number += 40;

   return win_number;
}
