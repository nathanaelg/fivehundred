#include <gtest/gtest.h>
#include "card_500.h"

TEST(Card, Initialize)
{
   Card card(Card::hearts, Card::ace);

   EXPECT_EQ(Card::hearts, card.suit());
   EXPECT_EQ(Card::ace, card.number());
}

TEST(Card, Equality)
{
   Card card(Card::clubs, Card::seven);
   Card card_copy(Card::clubs, Card::seven);

   EXPECT_EQ(card_copy, card);
}

TEST(Card, Inequality)
{
   Card card(Card::clubs, Card::seven);
   Card different_suit(Card::spades, Card::seven);
   Card different_number(Card::clubs, Card::eight);

   EXPECT_NE(different_suit, card);
   EXPECT_NE(different_number, card);
}

TEST(Card, Colour)
{
   Card red_card(Card::hearts, Card::ace);
   Card black_card(Card::clubs, Card::ace);
   Card neither_card(Card::none, Card::joker);

   EXPECT_EQ(Card::red, red_card.colour());
   EXPECT_EQ(Card::black, black_card.colour());
   EXPECT_EQ(Card::neither, neither_card.colour());
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

   EXPECT_EQ(Card::hearts, card.suit(Game_500::no_trumps));
   EXPECT_EQ(Card::ace, card.number());
   EXPECT_EQ(Card::red, card.colour());
}

TEST(Card_500, CompareNoTrumps)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 jack_hearts(Card::hearts, Card::jack);

   EXPECT_GT(ace_hearts.win_number(Game_500::no_trumps, Card::hearts),
             jack_hearts.win_number(Game_500::no_trumps, Card::hearts));
}

TEST(Card_500, CompareBowersAndJoker)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 jack_hearts(Card::hearts, Card::jack);
   Card_500 jack_diamonds(Card::diamonds, Card::jack);
   Card_500 joker(Card::none, Card::joker);

   EXPECT_GT(joker.win_number(Game_500::hearts, Card::hearts),
             jack_hearts.win_number(Game_500::hearts, Card::hearts));
   EXPECT_GT(jack_hearts.win_number(Game_500::hearts, Card::hearts),
             jack_diamonds.win_number(Game_500::hearts, Card::hearts));
   EXPECT_GT(jack_diamonds.win_number(Game_500::hearts, Card::hearts),
             ace_hearts.win_number(Game_500::hearts, Card::hearts));
}

TEST(Card_500, CompareJokerInNoTrumps)
{
   Card_500 joker(Card::none, Card::joker);
   Card_500 ace_hearts(Card::hearts, Card::ace);

   EXPECT_GT(joker.win_number(Game_500::no_trumps, Card::hearts),
             ace_hearts.win_number(Game_500::no_trumps, Card::hearts));
}

TEST(Card_500, CompareJokerInMisere)
{
   Card_500 joker(Card::none, Card::joker);
   Card_500 five_spades(Card::spades, Card::five);

   EXPECT_LT(joker.win_number(Game_500::misere, Card::spades),
             five_spades.win_number(Game_500::misere, Card::spades));
}

TEST(Card_500, CompareTrumpsAndNonTrumps)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 five_clubs(Card::clubs, Card::five);

   EXPECT_GT(five_clubs.win_number(Game_500::clubs, Card::clubs),
             ace_hearts.win_number(Game_500::clubs, Card::clubs));
}

TEST(Card_500, CompareNonLedSuit)
{
   Card_500 ace_hearts(Card::hearts, Card::ace);
   Card_500 five_clubs(Card::clubs, Card::five);

   EXPECT_GT(five_clubs.win_number(Game_500::no_trumps, Card::clubs),
             ace_hearts.win_number(Game_500::no_trumps, Card::clubs));
   EXPECT_LT(five_clubs.win_number(Game_500::no_trumps, Card::hearts),
             ace_hearts.win_number(Game_500::no_trumps, Card::hearts));
}
