#include "GameState.hpp"

void GameState::LogGamePiece(const std::string& owner,
                             const std::string& archetype, const bool create) {
  // Create Game Piece
  if (create) {
    player_info[owner][archetype] += 1;
    ++game_pieces;
    // player_info[owner]["Power"] += power;
  }
  // Destroy Game Piece
  else if (!create) {
    player_info[owner][archetype] -= 1;
    --game_pieces;
    // player_info[owner]["Power"] -= power;
  }
}

int GameState::NumPieces(const std::string& player) {
  int r_pieces = 0;
  for (const auto & [ key, val ] : player_info[player]) {
    r_pieces += val;
  }
  return r_pieces;
}

int GameState::NumPieces(const std::string& player, const std::string& type) {
  return player_info[player][type];
}
