#include <gtest/gtest.h>
#include "game_state_500.h"
#include "deck_500.h"

class GameState : public ::testing::Test {
protected:
   Deck_500 deck;
   GameState_500 state;
};

class GameStateDealt : public GameState {
protected:
   virtual void SetUp()
   {
      deck.srand(1);
      deck.deal(&state.hands, &state.kitty);
      state.trumps = Game_500::no_trumps;
      state.tricks.front().leader = Game_500::player_1;
   }
};

class GameStatePickedUpKitty : public GameStateDealt {
protected:
   virtual void SetUp()
   {
      GameStateDealt::SetUp();
      state.do_picking_up_kitty_move();
   }
};

class GameStateEnd : public GameStateDealt {
protected:
   virtual void SetUp()
   {
      GameStateDealt::SetUp();
      state.do_picking_up_kitty_move();

      std::mt19937_64 random_engine(1);
      unsigned random_moves = 0;
      while (random_moves++ < 43) state.do_random_move(&random_engine);
   }
};

TEST_F(GameState, Initialize)
{
   EXPECT_EQ(Game_500::player_1, state.player_to_move);
   EXPECT_EQ(1, state.team_to_move);
   EXPECT_EQ(4, state.hands.size());
   EXPECT_EQ(1, state.tricks.size());
}

TEST_F(GameStateDealt, PickUpKitty)
{
   EXPECT_EQ(3, state.kitty.size());
   EXPECT_EQ(10, state.hands.at(state.player_to_move).size());

   state.do_picking_up_kitty_move();

   EXPECT_EQ(0, state.kitty.size());
   EXPECT_EQ(13, state.hands.at(state.player_to_move).size());
}

TEST_F(GameStatePickedUpKitty, DiscardKitty)
{
   EXPECT_EQ(0, state.kitty.size());

   Card_500 * eight_hearts = deck.find(Card::eight, Card::hearts);
   state.do_discarding_kitty_move(eight_hearts);

   EXPECT_EQ(1, state.kitty.size());
   EXPECT_EQ(eight_hearts, state.kitty.pop());
}

TEST_F(GameStateDealt, PlayCardFirstInTrick)
{
   Card_500 * five_diamonds = deck.find(Card::five, Card::diamonds);

   EXPECT_EQ(Game_500::player_1, state.player_to_move);
   EXPECT_EQ(10, state.hands.at(Game_500::player_1).size());
   EXPECT_TRUE(state.hands.at(Game_500::player_1).has_card(five_diamonds));

   state.do_playing_move(five_diamonds);

   EXPECT_EQ(Game_500::player_2, state.player_to_move);
   EXPECT_EQ(9, state.hands.at(Game_500::player_1).size());
   EXPECT_FALSE(state.hands.at(Game_500::player_1).has_card(five_diamonds));
}

TEST_F(GameStateDealt, PlayCardLastInTrick)
{
   state.do_playing_move(deck.find(Card::five, Card::diamonds));
   state.do_playing_move(deck.find(Card::four, Card::diamonds));
   state.do_playing_move(deck.find(Card::ace, Card::diamonds));

   EXPECT_EQ(Game_500::player_4, state.player_to_move);
   EXPECT_EQ(0, state.tricks_won[state.team_to_move - 1]);
   EXPECT_EQ(1, state.tricks.size());

   state.do_playing_move(deck.find(Card::seven, Card::diamonds));

   // Player that won the trick leads the next trick
   EXPECT_EQ(Game_500::player_3, state.player_to_move);
   // Team that won the trick gets a trick recorded
   EXPECT_EQ(1, state.tricks_won[state.team_to_move - 1]);
   // A new trick is created
   EXPECT_EQ(2, state.tricks.size());
}

TEST_F(GameStateDealt, RandomMove)
{
   EXPECT_TRUE(state.has_moves());

   state.do_picking_up_kitty_move();

   std::mt19937_64 random_engine(1);
   unsigned random_moves = 0;
   while (random_moves++ < 43) state.do_random_move(&random_engine);

   EXPECT_FALSE(state.has_moves());
}

TEST_F(GameStateEnd, Print)
{
   setlocale(LC_ALL, "");

   std::string const game_play_1 =
      "[Caller P1]\n"
      "[Trumps NT]\n"
      "[Discarded kitty: {J♦,9♦,8♣}]\n"
      "\n"
      "     P1  P2  P3  P4  P1  P2  P3  W13  W24\n"
      " 1   8♥  6♥  5♥  K♥                    P4\n"
      " 2               7♥  Q♥  4♥  J♥   P1\n"
      " 3   9♠  6♠ 10♥  Q♠                    P4\n"
      " 4               7♦  5♦  4♦  8♦   P3\n"
      " 5           9♥  K♣  7♣  A♥            P2\n"
      " 6       Q♦  A♦ 10♦  Q♣           P3\n"
      " 7           Jo  J♠  5♠  7♠       P3\n"
      " 8           J♣  6♣ 10♣  9♣       P3\n"
      " 9           5♣  8♠  A♣  K♦       P1\n"
      "10  10♠  K♠  6♦  A♠                    P4\n"
      "                                 [6]  [4]\n";

   EXPECT_EQ(game_play_1, state.print_play());
}
