#include <gtest/gtest.h>
#include "card_collection_500.h"

TEST(CardCollection, Initialize)
{
   CardCollection_500 cc(10);

   EXPECT_EQ(0, cc.size());
   EXPECT_EQ(10, cc.max_size());
   EXPECT_EQ(10, cc.deal_size());
}

TEST(CardCollection, InitializeWithDealSize)
{
   CardCollection_500 cc(10, 13);

   EXPECT_EQ(0, cc.size());
   EXPECT_EQ(10, cc.max_size());
   EXPECT_EQ(13, cc.deal_size());
}

TEST(CardCollection, AddCard)
{
   CardCollection_500 cc(10);
   Card_500 card(Card::queen, Card::spades);

   EXPECT_EQ(0, cc.size());
   EXPECT_FALSE(cc.has_card(&card));

   cc.add_card(&card);

   EXPECT_EQ(1, cc.size());
   EXPECT_TRUE(cc.has_card(&card));
}

TEST(CardCollection, AddCardTooMany)
{
   CardCollection_500 cc(1);
   Card_500 queen_spades(Card::queen, Card::spades), ten_spades(Card::ten, Card::spades);

   cc.add_card(&queen_spades);
   EXPECT_THROW(cc.add_card(&ten_spades), std::runtime_error);
}

TEST(CardCollection, RemoveCard)
{
   CardCollection_500 cc(10);
   Card_500 card(Card::queen, Card::spades);
   cc.add_card(&card);

   EXPECT_EQ(1, cc.size());
   EXPECT_TRUE(cc.has_card(&card));

   EXPECT_EQ(card, *cc.remove_card(&card));
   EXPECT_EQ(0, cc.size());
   EXPECT_FALSE(cc.has_card(&card));
}

TEST(CardCollection, RemoveCardNotPresent)
{
   CardCollection_500 cc(10);
   Card_500 card(Card::queen, Card::spades);
   EXPECT_THROW(cc.remove_card(&card), std::runtime_error);
}

TEST(CardCollection, Sort)
{
   CardCollection_500 cc(10);
   Card_500 ace_hearts(Card::ace, Card::hearts);
   Card_500 jack_hearts(Card::jack, Card::hearts);
   Card_500 jack_diamonds(Card::jack, Card::diamonds);
   Card_500 joker(Card::joker);
   Card_500 four_diamonds(Card::four, Card::diamonds);
   Card_500 ten_spades(Card::ten, Card::spades);

   cc.add_card(&ten_spades);
   cc.add_card(&ace_hearts);
   cc.add_card(&jack_hearts);
   cc.add_card(&four_diamonds);
   cc.add_card(&jack_diamonds);
   cc.add_card(&joker);

   // Sort currently returns cards in hearts, diamonds, clubs, spades order,
   // and within a suit in order of value, currently only used for printing

   cc.sort(Game_500::hearts);
   EXPECT_EQ("{Jo,J♥,J♦,A♥,4♦,10♠}", cc.print());

   cc.sort(Game_500::diamonds);
   EXPECT_EQ("{A♥,Jo,J♦,J♥,4♦,10♠}", cc.print());
}
