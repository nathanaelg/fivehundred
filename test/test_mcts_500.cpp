#include <gtest/gtest.h>
#include <iostream>
#include "game_state_500.h"
#include "deck_500.h"
#include "mcts.h"

class MonteCarloTreeSearch : public ::testing::Test {
protected:
   MCTS::ComputeOptions mcts_options;

   MonteCarloTreeSearch()
   {
      setlocale(LC_ALL, "");

      mcts_options.max_iterations = 3000;
      mcts_options.max_time = 10.0;
      mcts_options.verbose = false;
      mcts_options.number_of_threads = 1;

      srand(time(NULL));
   }
};

static void play_hand(unsigned hand_number,
                      Game_500::suit_t trumps,
                      Game_500::player_t bid_winner,
                      MCTS::ComputeOptions mcts_options)
{
   Deck_500 deck;
   GameState_500 state;

   deck.srand(hand_number);
   deck.deal(&state.hands, &state.kitty);

   state.trumps = trumps;

   state.player_to_move = state.tricks.front().leader = bid_winner;
   state.team_to_move = (state.player_to_move % 2) + 1;

   state.do_picking_up_kitty_move();

   while (state.has_moves())
   {
      state.tricks_won[0] = state.tricks_won[1] = 0;
      state.discarding_kitty = (state.kitty.size() < state.kitty.max_size());

      state.do_move(MCTS::compute_move(state, mcts_options));
   }

   std::cout << "[Seed " << hand_number << "]" << std::endl;
   std::cout << deck.print() << std::endl;
   std::cout << state.print_play() << std::endl;
}

TEST_F(MonteCarloTreeSearch, PlayHand)
{
   play_hand(rand() % 1000, Game_500::hearts, Game_500::player_1, mcts_options);
}

TEST_F(MonteCarloTreeSearch, PlayHandVerbose)
{
   mcts_options.verbose = true;

   play_hand(rand() % 1000, Game_500::spades, Game_500::player_2, mcts_options);
}
