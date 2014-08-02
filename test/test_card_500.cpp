#include <gtest/gtest.h>
#include "card_500.h"

TEST(Card, Initialize)
{
   Card card(Card::ace, Card::hearts);

   EXPECT_EQ(Card::hearts, card.suit());
   EXPECT_EQ(Card::ace, card.number());
}

TEST(Card, Equality)
{
   Card card(Card::seven, Card::clubs);
   Card card_copy(Card::seven, Card::clubs);

   EXPECT_EQ(card_copy, card);
}

TEST(Card, Inequality)
{
   Card card(Card::seven, Card::clubs);
   Card different_suit(Card::seven, Card::spades);
   Card different_number(Card::eight, Card::clubs);

   EXPECT_NE(different_suit, card);
   EXPECT_NE(different_number, card);
}

TEST(Card, Colour)
{
   Card red_card(Card::ace, Card::hearts);
   Card black_card(Card::ace, Card::clubs);
   Card neither_card(Card::joker);

   EXPECT_EQ(Card::red, red_card.colour());
   EXPECT_EQ(Card::black, black_card.colour());
   EXPECT_EQ(Card::neither, neither_card.colour());
}

TEST(Card, PrintFull)
{
   Card queen_of_spades(Card::queen, Card::spades);
   Card the_joker(Card::joker);

   EXPECT_EQ("Queen of Spades", queen_of_spades.print_full());
   EXPECT_EQ("The Joker", the_joker.print_full());
}

TEST(Card, Print)
{
   Card queen_of_spades(Card::queen, Card::spades);
   Card the_joker(Card::joker);

   EXPECT_EQ("Q♠", queen_of_spades.print());
   EXPECT_EQ("Jo", the_joker.print());
}

TEST(Card_500, Initialize)
{
   Card_500 card(Card::ace, Card::hearts);

   EXPECT_EQ(Card::hearts, card.suit(Game_500::no_trumps));
   EXPECT_EQ(Card::ace, card.number());
   EXPECT_EQ(Card::red, card.colour());
}

TEST(Card_500, CompareNoTrumps)
{
   Card_500 ace_hearts(Card::ace, Card::hearts);
   Card_500 jack_hearts(Card::jack, Card::hearts);

   EXPECT_GT(ace_hearts.win_number(Game_500::no_trumps, Card::hearts),
             jack_hearts.win_number(Game_500::no_trumps, Card::hearts));
}

TEST(Card_500, CompareBowersAndJoker)
{
   Card_500 ace_hearts(Card::ace, Card::hearts);
   Card_500 jack_hearts(Card::jack, Card::hearts);
   Card_500 jack_diamonds(Card::jack, Card::diamonds);
   Card_500 joker(Card::joker);

   EXPECT_GT(joker.win_number(Game_500::hearts, Card::hearts),
             jack_hearts.win_number(Game_500::hearts, Card::hearts));
   EXPECT_GT(jack_hearts.win_number(Game_500::hearts, Card::hearts),
             jack_diamonds.win_number(Game_500::hearts, Card::hearts));
   EXPECT_GT(jack_diamonds.win_number(Game_500::hearts, Card::hearts),
             ace_hearts.win_number(Game_500::hearts, Card::hearts));
}

TEST(Card_500, CompareJokerInNoTrumps)
{
   Card_500 joker(Card::joker);
   Card_500 ace_hearts(Card::ace, Card::hearts);

   EXPECT_GT(joker.win_number(Game_500::no_trumps, Card::hearts),
             ace_hearts.win_number(Game_500::no_trumps, Card::hearts));
}

TEST(Card_500, CompareJokerInMisere)
{
   Card_500 joker(Card::joker);
   Card_500 five_spades(Card::five, Card::spades);

   EXPECT_LT(joker.win_number(Game_500::misere, Card::spades),
             five_spades.win_number(Game_500::misere, Card::spades));
}

TEST(Card_500, CompareTrumpsAndNonTrumps)
{
   Card_500 ace_hearts(Card::ace, Card::hearts);
   Card_500 five_clubs(Card::five, Card::clubs);

   EXPECT_GT(five_clubs.win_number(Game_500::clubs, Card::clubs),
             ace_hearts.win_number(Game_500::clubs, Card::clubs));
}

TEST(Card_500, CompareNonLedSuit)
{
   Card_500 ace_hearts(Card::ace, Card::hearts);
   Card_500 five_clubs(Card::five, Card::clubs);

   EXPECT_GT(five_clubs.win_number(Game_500::no_trumps, Card::clubs),
             ace_hearts.win_number(Game_500::no_trumps, Card::clubs));
   EXPECT_LT(five_clubs.win_number(Game_500::no_trumps, Card::hearts),
             ace_hearts.win_number(Game_500::no_trumps, Card::hearts));
}
