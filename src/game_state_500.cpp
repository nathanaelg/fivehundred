#include <iostream>
#include "game_state_500.h"
#include "console.h"

static const Game_500::player_t next_player[] = {
   [Game_500::player_1] = Game_500::player_2,
   [Game_500::player_2] = Game_500::player_3,
   [Game_500::player_3] = Game_500::player_4,
   [Game_500::player_4] = Game_500::player_1
};

void GameState_500::do_move(Move move)
{
   if (!hands.at(player_to_move).is_valid_move(trumps, led, move))
   {
      std::cout << "Trumps: " << trumps << " Led: " << led << " Move: " << move->print() << std::endl;
      throw std::runtime_error("Move is not valid.");
   }

   switch (stage)
   {
   case Game_500::discarding_kitty:
      do_discarding_kitty_move(move);
      break;
   case Game_500::playing:
      do_playing_move(move);
      break;
   }
}

void GameState_500::do_picking_up_kitty_move()
{
   for (unsigned i = 0; i < kitty.max_size(); i++) hands.at(player_to_move).add_card(kitty.pop());
   tricks.front().leader = player_to_move;
   stage = Game_500::discarding_kitty;
}

void GameState_500::do_discarding_kitty_move(Move move)
{
   kitty.add_card(move);
   hands.at(player_to_move).remove_card(move);
   if (kitty.size() == kitty.max_size()) stage = Game_500::playing;
}

void GameState_500::do_playing_move(Move move)
{
   tricks.back().add_card(move);
   hands.at(player_to_move).remove_card(move);

   if (tricks.back().size() == tricks.back().max_size())
   {
      player_to_move = tricks.back().winner(trumps);
      team_to_move = (player_to_move % 2) + 1;
      tricks_won[team_to_move - 1]++;

      if (tricks.size() == 10) return;

      tricks.emplace_back();
      tricks.back().leader = player_to_move;
   }
   else
   {
      player_to_move = next_player[player_to_move];
      team_to_move = (player_to_move % 2) + 1;
   }

   led = tricks.back().led_suit(trumps);
}

bool GameState_500::has_moves() const
{
   if (tricks.size() < 10) return true;
   if (tricks.back().size() < tricks.back().max_size()) return true;
   return false;
}

std::vector<GameState_500::Move> GameState_500::get_moves() const
{
   return hands.at(player_to_move).valid_moves(trumps, led);
}

double GameState_500::get_result(int current_team_to_move) const
{
   if (has_moves()) throw std::runtime_error("Cannot give hand result as it is still in progress.");

   double tricks_played = tricks_won[0] + tricks_won[1];

   if (discarding_kitty) return tricks_won[current_team_to_move - 1] / tricks_played;
   return tricks_won[current_team_to_move % 2] / tricks_played;
}

GameState_500::GameState_500()
   : team_to_move(1), stage(Game_500::discarding_kitty), led(Card::none), player_to_move(Game_500::player_1)
{
   for (unsigned i = 0; i < 4; i++) hands.emplace_back();
   tricks.emplace_back();
   tricks_won[0] = tricks_won[1] = 0;
}

void GameState_500::count_tricks()
{
   tricks_won[0] = tricks_won[1] = 0;
   for (auto i = tricks.begin(); i != tricks.end(); i++)
   {
      tricks_won[i->winner(trumps) % 2]++;
   }
}

std::string GameState_500::print_play() const
{
   static std::map <Game_500::suit_t, std::string> const print_trumps_suit = {
      {Game_500::hearts, "♥"},
      {Game_500::diamonds, "♦"},
      {Game_500::spades, "♠"},
      {Game_500::clubs, "♣"},
      {Game_500::no_trumps, "NT"},
      {Game_500::misere, "M"}
   };

   std::string output = "[Caller P" + std::to_string(tricks.at(0).leader + 1) + "]\n";
   output += "[Trumps " + find_with_exception(print_trumps_suit, trumps) + "]\n";
   output += "[Discarded kitty: " + kitty.print() + "]\n\n";
   output += "     P1  P2  P3  P4  P1  P2  P3  W13  W24\n";

   unsigned tricks_won[2] = {0, 0};
   for (std::vector<Trick_500>::const_iterator i = tricks.begin();
        i != tricks.end();
        i++)
   {
      std::string trick_str = fixed_width_string(std::to_string(i - tricks.begin() + 1), 2, right_side) + " ";
      trick_str += i->print();
      trick_str = fixed_width_string(trick_str, (i->winner(trumps) % 2 == 0) ? 34 : 39, left_side);
      trick_str += "P" + std::to_string(i->winner(trumps) + 1) + "\n";
      output += trick_str;
      tricks_won[i->winner(trumps) % 2]++;
   }

   output += fixed_width_string("[" + std::to_string(tricks_won[0]) + "]  " \
                                "[" + std::to_string(tricks_won[1]) + "]", 41, right_side) + "\n";

   return output;
}
