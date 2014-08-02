#include <gtest/gtest.h>
#include "hand_500.h"

class Hand : public ::testing::Test {
protected:
   Hand_500 hand;
   Card_500 joker, jack_hearts, ten_hearts, ace_diamonds, five_clubs;
   Game_500::suit_t trumps;
   Card::suit_t led;

   Hand()
      : joker(Card::joker), jack_hearts(Card::jack, Card::hearts), ten_hearts(Card::ten, Card::hearts),
        ace_diamonds(Card::ace, Card::diamonds), five_clubs(Card::five, Card::clubs), trumps(Game_500::diamonds)
   {
      hand.add_card(&joker);
      hand.add_card(&jack_hearts);
      hand.add_card(&ten_hearts);
      hand.add_card(&ace_diamonds);
      hand.add_card(&five_clubs);
   }
};

TEST_F(Hand, ValidMovesLedSuit)
{
   led = Card::diamonds;
   std::vector<Card_500 *> valid_moves = hand.valid_moves(trumps, led);

   ASSERT_EQ(3, valid_moves.size());
   EXPECT_EQ(joker, *valid_moves.at(0));
   EXPECT_EQ(jack_hearts, *valid_moves.at(1));
   EXPECT_EQ(ace_diamonds, *valid_moves.at(2));
}

TEST_F(Hand, ValidMovesNothingLed)
{
   led = Card::none;
   std::vector<Card_500 *> valid_moves = hand.valid_moves(trumps, led);

   ASSERT_EQ(5, valid_moves.size());
   EXPECT_EQ(joker, *valid_moves.at(0));
   EXPECT_EQ(jack_hearts, *valid_moves.at(1));
   EXPECT_EQ(ten_hearts, *valid_moves.at(2));
   EXPECT_EQ(ace_diamonds, *valid_moves.at(3));
   EXPECT_EQ(five_clubs, *valid_moves.at(4));
}

TEST_F(Hand, ValidMovesNoneOfLedSuit)
{
   led = Card::spades;
   std::vector<Card_500 *> valid_moves = hand.valid_moves(trumps, led);

   ASSERT_EQ(5, valid_moves.size());
   EXPECT_EQ(joker, *valid_moves.at(0));
   EXPECT_EQ(jack_hearts, *valid_moves.at(1));
   EXPECT_EQ(ten_hearts, *valid_moves.at(2));
   EXPECT_EQ(ace_diamonds, *valid_moves.at(3));
   EXPECT_EQ(five_clubs, *valid_moves.at(4));
}

TEST_F(Hand, IsValidMoveInvalid)
{
   led = Card::diamonds;
   EXPECT_FALSE(hand.is_valid_move(trumps, led, &ten_hearts));
   EXPECT_FALSE(hand.is_valid_move(trumps, led, &five_clubs));
}

TEST_F(Hand, IsValidMoveValid)
{
   led = Card::diamonds;
   EXPECT_TRUE(hand.is_valid_move(trumps, led, &joker));
   EXPECT_TRUE(hand.is_valid_move(trumps, led, &jack_hearts));
   EXPECT_TRUE(hand.is_valid_move(trumps, led, &ace_diamonds));
}

// @todo: Valid moves in no trumps/misere - joker being played, joker being led
