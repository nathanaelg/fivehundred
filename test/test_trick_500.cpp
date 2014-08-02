#include <gtest/gtest.h>
#include "trick_500.h"

class Trick : public ::testing::Test {
protected:
   Trick_500 trick;
   Card_500 jack_hearts, ace_diamonds, five_clubs, jack_spades;
   Game_500::suit_t trumps;

   Trick()
      : jack_hearts(Card::jack, Card::hearts), ace_diamonds(Card::ace, Card::diamonds),
        five_clubs(Card::five, Card::clubs), jack_spades(Card::jack, Card::spades), trumps(Game_500::clubs)
   {
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

TEST_F(Trick, Winner)
{
   trick.leader = Game_500::player_2;
   EXPECT_EQ(Game_500::player_1, trick.winner(trumps));
}
