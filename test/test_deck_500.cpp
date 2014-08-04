#include <gtest/gtest.h>
#include "deck_500.h"

TEST(Deck, Deal)
{
   Deck_500 deck;
   Kitty_500 kitty;
   std::vector<Hand_500> hands;
   for (unsigned i = 0; i < 4; i++) hands.emplace_back();

   deck.srand(1);
   deck.deal(&hands, &kitty);

   std::string const deal_1[] = {
      "{8♥,J♦,9♦,5♦,Q♣,10♣,8♣,10♠,9♠,5♠}",
      "{A♥,6♥,4♥,K♦,Q♦,4♦,9♣,K♠,7♠,6♠}",
      "{Jo,J♥,10♥,9♥,5♥,A♦,8♦,6♦,5♣,J♣}",
      "{K♥,7♥,10♦,7♦,K♣,6♣,A♠,Q♠,J♠,8♠}",
      "{Q♥,A♣,7♣}"
   };

   for (unsigned i = 0; i < 4; i++) EXPECT_EQ(deal_1[i], hands.at(i).print());
   EXPECT_EQ(deal_1[4], kitty.print());
}
