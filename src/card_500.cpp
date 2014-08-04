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
   [Game_500::hearts] = Card::red,
   [Game_500::diamonds] = Card::red,
   [Game_500::clubs] = Card::black,
   [Game_500::spades] = Card::black,
   [Game_500::no_trumps] = Card::neither,
   [Game_500::misere] = Card::neither
};

static Card::suit_t const play_suit[6][5][14] = {
   [Game_500::hearts] = {
      [Card::none] = {
         [Card::ace] = Card::none,
         [Card::two] = Card::none,
         [Card::three] = Card::none,
         [Card::four] = Card::none,
         [Card::five] = Card::none,
         [Card::six] = Card::none,
         [Card::seven] = Card::none,
         [Card::eight] = Card::none,
         [Card::nine] = Card::none,
         [Card::ten] = Card::none,
         [Card::jack] = Card::none,
         [Card::queen] = Card::none,
         [Card::king] = Card::none,
         [Card::joker] = Card::hearts
      },
      [Card::hearts] = {
         [Card::ace] = Card::hearts,
         [Card::two] = Card::hearts,
         [Card::three] = Card::hearts,
         [Card::four] = Card::hearts,
         [Card::five] = Card::hearts,
         [Card::six] = Card::hearts,
         [Card::seven] = Card::hearts,
         [Card::eight] = Card::hearts,
         [Card::nine] = Card::hearts,
         [Card::ten] = Card::hearts,
         [Card::jack] = Card::hearts,
         [Card::queen] = Card::hearts,
         [Card::king] = Card::hearts,
         [Card::joker] = Card::hearts
      },
      [Card::diamonds] = {
         [Card::ace] = Card::diamonds,
         [Card::two] = Card::diamonds,
         [Card::three] = Card::diamonds,
         [Card::four] = Card::diamonds,
         [Card::five] = Card::diamonds,
         [Card::six] = Card::diamonds,
         [Card::seven] = Card::diamonds,
         [Card::eight] = Card::diamonds,
         [Card::nine] = Card::diamonds,
         [Card::ten] = Card::diamonds,
         [Card::jack] = Card::hearts,
         [Card::queen] = Card::diamonds,
         [Card::king] = Card::diamonds,
         [Card::joker] = Card::hearts
      },
      [Card::clubs] = {
         [Card::ace] = Card::clubs,
         [Card::two] = Card::clubs,
         [Card::three] = Card::clubs,
         [Card::four] = Card::clubs,
         [Card::five] = Card::clubs,
         [Card::six] = Card::clubs,
         [Card::seven] = Card::clubs,
         [Card::eight] = Card::clubs,
         [Card::nine] = Card::clubs,
         [Card::ten] = Card::clubs,
         [Card::jack] = Card::clubs,
         [Card::queen] = Card::clubs,
         [Card::king] = Card::clubs,
         [Card::joker] = Card::hearts
      },
      [Card::spades] = {
         [Card::ace] = Card::spades,
         [Card::two] = Card::spades,
         [Card::three] = Card::spades,
         [Card::four] = Card::spades,
         [Card::five] = Card::spades,
         [Card::six] = Card::spades,
         [Card::seven] = Card::spades,
         [Card::eight] = Card::spades,
         [Card::nine] = Card::spades,
         [Card::ten] = Card::spades,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::spades,
         [Card::king] = Card::spades,
         [Card::joker] = Card::hearts
      }
   },
   [Game_500::diamonds] = {
      [Card::none] = {
         [Card::ace] = Card::none,
         [Card::two] = Card::none,
         [Card::three] = Card::none,
         [Card::four] = Card::none,
         [Card::five] = Card::none,
         [Card::six] = Card::none,
         [Card::seven] = Card::none,
         [Card::eight] = Card::none,
         [Card::nine] = Card::none,
         [Card::ten] = Card::none,
         [Card::jack] = Card::none,
         [Card::queen] = Card::none,
         [Card::king] = Card::none,
         [Card::joker] = Card::diamonds
      },
      [Card::hearts] = {
         [Card::ace] = Card::hearts,
         [Card::two] = Card::hearts,
         [Card::three] = Card::hearts,
         [Card::four] = Card::hearts,
         [Card::five] = Card::hearts,
         [Card::six] = Card::hearts,
         [Card::seven] = Card::hearts,
         [Card::eight] = Card::hearts,
         [Card::nine] = Card::hearts,
         [Card::ten] = Card::hearts,
         [Card::jack] = Card::diamonds,
         [Card::queen] = Card::hearts,
         [Card::king] = Card::hearts,
         [Card::joker] = Card::diamonds
      },
      [Card::diamonds] = {
         [Card::ace] = Card::diamonds,
         [Card::two] = Card::diamonds,
         [Card::three] = Card::diamonds,
         [Card::four] = Card::diamonds,
         [Card::five] = Card::diamonds,
         [Card::six] = Card::diamonds,
         [Card::seven] = Card::diamonds,
         [Card::eight] = Card::diamonds,
         [Card::nine] = Card::diamonds,
         [Card::ten] = Card::diamonds,
         [Card::jack] = Card::diamonds,
         [Card::queen] = Card::diamonds,
         [Card::king] = Card::diamonds,
         [Card::joker] = Card::diamonds
      },
      [Card::clubs] = {
         [Card::ace] = Card::clubs,
         [Card::two] = Card::clubs,
         [Card::three] = Card::clubs,
         [Card::four] = Card::clubs,
         [Card::five] = Card::clubs,
         [Card::six] = Card::clubs,
         [Card::seven] = Card::clubs,
         [Card::eight] = Card::clubs,
         [Card::nine] = Card::clubs,
         [Card::ten] = Card::clubs,
         [Card::jack] = Card::clubs,
         [Card::queen] = Card::clubs,
         [Card::king] = Card::clubs,
         [Card::joker] = Card::diamonds
      },
      [Card::spades] = {
         [Card::ace] = Card::spades,
         [Card::two] = Card::spades,
         [Card::three] = Card::spades,
         [Card::four] = Card::spades,
         [Card::five] = Card::spades,
         [Card::six] = Card::spades,
         [Card::seven] = Card::spades,
         [Card::eight] = Card::spades,
         [Card::nine] = Card::spades,
         [Card::ten] = Card::spades,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::spades,
         [Card::king] = Card::spades,
         [Card::joker] = Card::diamonds
      }
   },
   [Game_500::clubs] = {
      [Card::none] = {
         [Card::ace] = Card::none,
         [Card::two] = Card::none,
         [Card::three] = Card::none,
         [Card::four] = Card::none,
         [Card::five] = Card::none,
         [Card::six] = Card::none,
         [Card::seven] = Card::none,
         [Card::eight] = Card::none,
         [Card::nine] = Card::none,
         [Card::ten] = Card::none,
         [Card::jack] = Card::none,
         [Card::queen] = Card::none,
         [Card::king] = Card::none,
         [Card::joker] = Card::clubs
      },
      [Card::hearts] = {
         [Card::ace] = Card::hearts,
         [Card::two] = Card::hearts,
         [Card::three] = Card::hearts,
         [Card::four] = Card::hearts,
         [Card::five] = Card::hearts,
         [Card::six] = Card::hearts,
         [Card::seven] = Card::hearts,
         [Card::eight] = Card::hearts,
         [Card::nine] = Card::hearts,
         [Card::ten] = Card::hearts,
         [Card::jack] = Card::hearts,
         [Card::queen] = Card::hearts,
         [Card::king] = Card::hearts,
         [Card::joker] = Card::clubs
      },
      [Card::diamonds] = {
         [Card::ace] = Card::diamonds,
         [Card::two] = Card::diamonds,
         [Card::three] = Card::diamonds,
         [Card::four] = Card::diamonds,
         [Card::five] = Card::diamonds,
         [Card::six] = Card::diamonds,
         [Card::seven] = Card::diamonds,
         [Card::eight] = Card::diamonds,
         [Card::nine] = Card::diamonds,
         [Card::ten] = Card::diamonds,
         [Card::jack] = Card::diamonds,
         [Card::queen] = Card::diamonds,
         [Card::king] = Card::diamonds,
         [Card::joker] = Card::clubs
      },
      [Card::clubs] = {
         [Card::ace] = Card::clubs,
         [Card::two] = Card::clubs,
         [Card::three] = Card::clubs,
         [Card::four] = Card::clubs,
         [Card::five] = Card::clubs,
         [Card::six] = Card::clubs,
         [Card::seven] = Card::clubs,
         [Card::eight] = Card::clubs,
         [Card::nine] = Card::clubs,
         [Card::ten] = Card::clubs,
         [Card::jack] = Card::clubs,
         [Card::queen] = Card::clubs,
         [Card::king] = Card::clubs,
         [Card::joker] = Card::clubs
      },
      [Card::spades] = {
         [Card::ace] = Card::spades,
         [Card::two] = Card::spades,
         [Card::three] = Card::spades,
         [Card::four] = Card::spades,
         [Card::five] = Card::spades,
         [Card::six] = Card::spades,
         [Card::seven] = Card::spades,
         [Card::eight] = Card::spades,
         [Card::nine] = Card::spades,
         [Card::ten] = Card::spades,
         [Card::jack] = Card::clubs,
         [Card::queen] = Card::spades,
         [Card::king] = Card::spades,
         [Card::joker] = Card::clubs
      }
   },
   [Game_500::spades] = {
      [Card::none] = {
         [Card::ace] = Card::none,
         [Card::two] = Card::none,
         [Card::three] = Card::none,
         [Card::four] = Card::none,
         [Card::five] = Card::none,
         [Card::six] = Card::none,
         [Card::seven] = Card::none,
         [Card::eight] = Card::none,
         [Card::nine] = Card::none,
         [Card::ten] = Card::none,
         [Card::jack] = Card::none,
         [Card::queen] = Card::none,
         [Card::king] = Card::none,
         [Card::joker] = Card::spades
      },
      [Card::hearts] = {
         [Card::ace] = Card::hearts,
         [Card::two] = Card::hearts,
         [Card::three] = Card::hearts,
         [Card::four] = Card::hearts,
         [Card::five] = Card::hearts,
         [Card::six] = Card::hearts,
         [Card::seven] = Card::hearts,
         [Card::eight] = Card::hearts,
         [Card::nine] = Card::hearts,
         [Card::ten] = Card::hearts,
         [Card::jack] = Card::hearts,
         [Card::queen] = Card::hearts,
         [Card::king] = Card::hearts,
         [Card::joker] = Card::spades
      },
      [Card::diamonds] = {
         [Card::ace] = Card::diamonds,
         [Card::two] = Card::diamonds,
         [Card::three] = Card::diamonds,
         [Card::four] = Card::diamonds,
         [Card::five] = Card::diamonds,
         [Card::six] = Card::diamonds,
         [Card::seven] = Card::diamonds,
         [Card::eight] = Card::diamonds,
         [Card::nine] = Card::diamonds,
         [Card::ten] = Card::diamonds,
         [Card::jack] = Card::diamonds,
         [Card::queen] = Card::diamonds,
         [Card::king] = Card::diamonds,
         [Card::joker] = Card::spades
      },
      [Card::clubs] = {
         [Card::ace] = Card::clubs,
         [Card::two] = Card::clubs,
         [Card::three] = Card::clubs,
         [Card::four] = Card::clubs,
         [Card::five] = Card::clubs,
         [Card::six] = Card::clubs,
         [Card::seven] = Card::clubs,
         [Card::eight] = Card::clubs,
         [Card::nine] = Card::clubs,
         [Card::ten] = Card::clubs,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::clubs,
         [Card::king] = Card::clubs,
         [Card::joker] = Card::spades
      },
      [Card::spades] = {
         [Card::ace] = Card::spades,
         [Card::two] = Card::spades,
         [Card::three] = Card::spades,
         [Card::four] = Card::spades,
         [Card::five] = Card::spades,
         [Card::six] = Card::spades,
         [Card::seven] = Card::spades,
         [Card::eight] = Card::spades,
         [Card::nine] = Card::spades,
         [Card::ten] = Card::spades,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::spades,
         [Card::king] = Card::spades,
         [Card::joker] = Card::spades
      }
   },
   [Game_500::no_trumps] = {
      [Card::none] = {
         [Card::ace] = Card::none,
         [Card::two] = Card::none,
         [Card::three] = Card::none,
         [Card::four] = Card::none,
         [Card::five] = Card::none,
         [Card::six] = Card::none,
         [Card::seven] = Card::none,
         [Card::eight] = Card::none,
         [Card::nine] = Card::none,
         [Card::ten] = Card::none,
         [Card::jack] = Card::none,
         [Card::queen] = Card::none,
         [Card::king] = Card::none,
         [Card::joker] = Card::none
      },
      [Card::hearts] = {
         [Card::ace] = Card::hearts,
         [Card::two] = Card::hearts,
         [Card::three] = Card::hearts,
         [Card::four] = Card::hearts,
         [Card::five] = Card::hearts,
         [Card::six] = Card::hearts,
         [Card::seven] = Card::hearts,
         [Card::eight] = Card::hearts,
         [Card::nine] = Card::hearts,
         [Card::ten] = Card::hearts,
         [Card::jack] = Card::hearts,
         [Card::queen] = Card::hearts,
         [Card::king] = Card::hearts,
         [Card::joker] = Card::hearts
      },
      [Card::diamonds] = {
         [Card::ace] = Card::diamonds,
         [Card::two] = Card::diamonds,
         [Card::three] = Card::diamonds,
         [Card::four] = Card::diamonds,
         [Card::five] = Card::diamonds,
         [Card::six] = Card::diamonds,
         [Card::seven] = Card::diamonds,
         [Card::eight] = Card::diamonds,
         [Card::nine] = Card::diamonds,
         [Card::ten] = Card::diamonds,
         [Card::jack] = Card::diamonds,
         [Card::queen] = Card::diamonds,
         [Card::king] = Card::diamonds,
         [Card::joker] = Card::diamonds
      },
      [Card::clubs] = {
         [Card::ace] = Card::clubs,
         [Card::two] = Card::clubs,
         [Card::three] = Card::clubs,
         [Card::four] = Card::clubs,
         [Card::five] = Card::clubs,
         [Card::six] = Card::clubs,
         [Card::seven] = Card::clubs,
         [Card::eight] = Card::clubs,
         [Card::nine] = Card::clubs,
         [Card::ten] = Card::clubs,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::clubs,
         [Card::king] = Card::clubs,
         [Card::joker] = Card::clubs
      },
      [Card::spades] = {
         [Card::ace] = Card::spades,
         [Card::two] = Card::spades,
         [Card::three] = Card::spades,
         [Card::four] = Card::spades,
         [Card::five] = Card::spades,
         [Card::six] = Card::spades,
         [Card::seven] = Card::spades,
         [Card::eight] = Card::spades,
         [Card::nine] = Card::spades,
         [Card::ten] = Card::spades,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::spades,
         [Card::king] = Card::spades,
         [Card::joker] = Card::spades
      }
   },
   [Game_500::misere] = {
      [Card::none] = {
         [Card::ace] = Card::none,
         [Card::two] = Card::none,
         [Card::three] = Card::none,
         [Card::four] = Card::none,
         [Card::five] = Card::none,
         [Card::six] = Card::none,
         [Card::seven] = Card::none,
         [Card::eight] = Card::none,
         [Card::nine] = Card::none,
         [Card::ten] = Card::none,
         [Card::jack] = Card::none,
         [Card::queen] = Card::none,
         [Card::king] = Card::none,
         [Card::joker] = Card::none
      },
      [Card::hearts] = {
         [Card::ace] = Card::hearts,
         [Card::two] = Card::hearts,
         [Card::three] = Card::hearts,
         [Card::four] = Card::hearts,
         [Card::five] = Card::hearts,
         [Card::six] = Card::hearts,
         [Card::seven] = Card::hearts,
         [Card::eight] = Card::hearts,
         [Card::nine] = Card::hearts,
         [Card::ten] = Card::hearts,
         [Card::jack] = Card::hearts,
         [Card::queen] = Card::hearts,
         [Card::king] = Card::hearts,
         [Card::joker] = Card::hearts
      },
      [Card::diamonds] = {
         [Card::ace] = Card::diamonds,
         [Card::two] = Card::diamonds,
         [Card::three] = Card::diamonds,
         [Card::four] = Card::diamonds,
         [Card::five] = Card::diamonds,
         [Card::six] = Card::diamonds,
         [Card::seven] = Card::diamonds,
         [Card::eight] = Card::diamonds,
         [Card::nine] = Card::diamonds,
         [Card::ten] = Card::diamonds,
         [Card::jack] = Card::diamonds,
         [Card::queen] = Card::diamonds,
         [Card::king] = Card::diamonds,
         [Card::joker] = Card::diamonds
      },
      [Card::clubs] = {
         [Card::ace] = Card::clubs,
         [Card::two] = Card::clubs,
         [Card::three] = Card::clubs,
         [Card::four] = Card::clubs,
         [Card::five] = Card::clubs,
         [Card::six] = Card::clubs,
         [Card::seven] = Card::clubs,
         [Card::eight] = Card::clubs,
         [Card::nine] = Card::clubs,
         [Card::ten] = Card::clubs,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::clubs,
         [Card::king] = Card::clubs,
         [Card::joker] = Card::clubs
      },
      [Card::spades] = {
         [Card::ace] = Card::spades,
         [Card::two] = Card::spades,
         [Card::three] = Card::spades,
         [Card::four] = Card::spades,
         [Card::five] = Card::spades,
         [Card::six] = Card::spades,
         [Card::seven] = Card::spades,
         [Card::eight] = Card::spades,
         [Card::nine] = Card::spades,
         [Card::ten] = Card::spades,
         [Card::jack] = Card::spades,
         [Card::queen] = Card::spades,
         [Card::king] = Card::spades,
         [Card::joker] = Card::spades
      }
   }
};

Card::suit_t Card_500::suit(Game_500::suit_t trumps) const
{
   return play_suit[trumps][_suit][_number];
}

bool Card_500::card_and_game_suit_equal(Card::suit_t card_suit, Game_500::suit_t game_suit) const
{
   if ((card_suit == Card::hearts) && (game_suit == Game_500::hearts)) return true;
   if ((card_suit == Card::diamonds) && (game_suit == Game_500::diamonds)) return true;
   if ((card_suit == Card::clubs) && (game_suit == Game_500::clubs)) return true;
   if ((card_suit == Card::spades) && (game_suit == Game_500::spades)) return true;
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
