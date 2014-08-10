#include <gtest/gtest.h>
#include "trick_500.h"

class Trick : public ::testing::Test {
protected:
   Trick_500 trick;
   Card_500 jack_hearts, ace_diamonds, five_clubs, jack_spades;
   Game_500::suit_t trumps;

   Trick()
      : jack_hearts(Card::jack, Card::hearts), ace_diamonds(Card::ace, Card::diamonds),
        five_clubs(Card::five, Card::clubs), jack_spades(Card::jack, Card::spades), trumps(Game_500::no_trumps)
   {
      trick.leader = Game_500::player_2;
      trick.add_card(&jack_hearts);
      trick.add_card(&ace_diamonds);
      trick.add_card(&five_clubs);
      trick.add_card(&jack_spades);
   }
};

TEST_F(Trick, LedSuit)
{
   EXPECT_EQ(Card::hearts, trick.led_suit(trumps));
}

TEST_F(Trick, WinnerNoTrumps)
{
   EXPECT_EQ(Game_500::player_2, trick.winner(trumps));
}

TEST_F(Trick, WinnerHearts)
{
   trumps = Game_500::hearts;
   EXPECT_EQ(Game_500::player_2, trick.winner(trumps));
}

TEST_F(Trick, WinnerDiamonds)
{
   trumps = Game_500::diamonds;
   EXPECT_EQ(Game_500::player_2, trick.winner(trumps));
}

TEST_F(Trick, WinnerSpades)
{
   trumps = Game_500::spades;
   EXPECT_EQ(Game_500::player_1, trick.winner(trumps));
}

TEST_F(Trick, WinnerClubs)
{
   trumps = Game_500::clubs;
   EXPECT_EQ(Game_500::player_1, trick.winner(trumps));
}
