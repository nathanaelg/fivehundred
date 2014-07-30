#include <gtest/gtest.h>
#include "card_500.h"

TEST(Card, Initialize)
{
   Card card(Card::hearts, Card::ace);

   EXPECT_EQ(Card::hearts, card.suit);
   EXPECT_EQ(Card::ace, card.number);
}

TEST(Card, Colour)
{
   Card red_card(Card::hearts, Card::ace);
   Card black_card(Card::clubs, Card::ace);
   Card neither_card(Card::none, Card::joker);

   EXPECT_EQ(Card::red, red_card.colour);
   EXPECT_EQ(Card::black, black_card.colour);
   EXPECT_EQ(Card::neither, neither_card.colour);
}

TEST(Card, PrintFull)
{
   Card queen_of_spades(Card::spades, Card::queen);
   Card the_joker(Card::none, Card::joker);

   EXPECT_EQ("Queen of Spades", queen_of_spades.print_full());
   EXPECT_EQ("The Joker", the_joker.print_full());
}

TEST(Card, Print)
{
   Card queen_of_spades(Card::spades, Card::queen);
   Card the_joker(Card::none, Card::joker);

   EXPECT_EQ("Q♠", queen_of_spades.print());
   EXPECT_EQ("Jo", the_joker.print());
}

TEST(Card_500, Initialize)
{
   Card_500 card(Card::hearts, Card::ace);
   card.set_trumps(Game_500::no_trumps);

   EXPECT_EQ(Card::hearts, card.suit);
   EXPECT_EQ(Card::ace, card.number);
   EXPECT_EQ(Card::red, card.colour);
}

TEST(Card_500, CompareNoTrumps)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 jack_hearts(Card::hearts, Card::jack);
   ace_hearts.set_trumps(Game_500::no_trumps);
   jack_hearts.set_trumps(Game_500::no_trumps);

   EXPECT_GT(ace_hearts.win_number(Game_500::no_trumps, Card::none), 
             jack_hearts.win_number(Game_500::no_trumps, Card::none));
}

TEST(Card_500, CompareBowersAndJoker)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 jack_hearts(Card::hearts, Card::jack);
   Card_500 jack_diamonds(Card::diamonds, Card::jack);
   Card_500 joker(Card::none, Card::joker);
   ace_hearts.set_trumps(Game_500::hearts);
   jack_hearts.set_trumps(Game_500::hearts);
   jack_diamonds.set_trumps(Game_500::hearts);
   joker.set_trumps(Game_500::hearts);

   EXPECT_GT(joker.win_number(Game_500::hearts, Card::none), 
             jack_hearts.win_number(Game_500::hearts, Card::none));
   EXPECT_GT(jack_hearts.win_number(Game_500::hearts, Card::none), 
             jack_diamonds.win_number(Game_500::hearts, Card::none));
   EXPECT_GT(jack_diamonds.win_number(Game_500::hearts, Card::none), 
             ace_hearts.win_number(Game_500::hearts, Card::none));
}

TEST(Card_500, CompareJokerInNoTrumps)
{
   Card_500 joker(Card::none, Card::joker);
   Card_500 ace_hearts(Card::hearts, Card::ace);
   joker.set_trumps(Game_500::no_trumps);
   ace_hearts.set_trumps(Game_500::no_trumps);

   EXPECT_GT(joker.win_number(Game_500::no_trumps, Card::hearts), 
             ace_hearts.win_number(Game_500::no_trumps, Card::hearts));
}

TEST(Card_500, CompareJokerInMisere)
{
   Card_500 joker(Card::none, Card::joker);
   Card_500 five_spades(Card::spades, Card::five);
   joker.set_trumps(Game_500::misere);
   five_spades.set_trumps(Game_500::misere);

   EXPECT_LT(joker.win_number(Game_500::misere, Card::spades), 
             five_spades.win_number(Game_500::misere, Card::spades));
}

TEST(Card_500, CompareTrumpsAndNonTrumps)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 five_clubs(Card::clubs, Card::five);
   ace_hearts.set_trumps(Game_500::clubs);
   five_clubs.set_trumps(Game_500::clubs);

   EXPECT_GT(five_clubs.win_number(Game_500::clubs, Card::none), 
             ace_hearts.win_number(Game_500::clubs, Card::none));
}

TEST(Card_500, CompareNonLedSuit)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 five_clubs(Card::clubs, Card::five);
   ace_hearts.set_trumps(Game_500::no_trumps);
   five_clubs.set_trumps(Game_500::no_trumps);

   EXPECT_GT(five_clubs.win_number(Game_500::no_trumps, Card::clubs), 
             ace_hearts.win_number(Game_500::no_trumps, Card::clubs));
   EXPECT_LT(five_clubs.win_number(Game_500::no_trumps, Card::hearts), 
             ace_hearts.win_number(Game_500::no_trumps, Card::hearts));
}