#ifndef _GAME_STATE_500_H_
#define _GAME_STATE_500_H_

#include <random>
#include "hand_500.h"
#include "kitty_500.h"
#include "trick_500.h"

class GameState_500
{
public:
   typedef Card_500 * Move;
   static constexpr Move no_move = 0;

   void do_move(Move move);
   template<typename RandomEngine>
      void do_random_move(RandomEngine* engine)
   {
      std::vector<GameState_500::Move> moves = get_moves();
      std::uniform_int_distribution<unsigned> index(0, moves.size() - 1);
      do_move(moves.at(index(*engine)));
   }

   bool has_moves() const;
   std::vector<Move> get_moves() const;

   double get_result(int current_team_to_move) const;

   int team_to_move;

   GameState_500();
   std::string print_play() const;

   Game_500::stage_t stage;
   bool discarding_kitty;
   Game_500::suit_t trumps;
   Card::suit_t led;
   std::vector<Hand_500> hands;
   Kitty_500 kitty;
   std::vector<Trick_500> tricks;

   Game_500::player_t player_to_move;
   unsigned tricks_won[2];

   void do_bidding_move(Move move);
   void do_picking_up_kitty_move();
   void do_discarding_kitty_move(Move move);
   void do_playing_move(Move move);
   void count_tricks();
};

#endif /* _GAME_STATE_500_H_ */
