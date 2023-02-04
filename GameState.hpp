#pragma once
#include <map>
#include <string>
#include <utility>
#include <iostream>

class GameState {
 private:
  std::map<std::string, std::map<std::string, int> > player_info;
  int game_pieces = 0;

 public:
  // Logs Creation/Destruction of GamePieces
  // Last param: true = create piece. false = destroy piece
  void LogGamePiece(const std::string& owner, const std::string& archetype,
                    const bool create);

  // Calculates Wizard Power and Speed Across the board
  friend std::pair<int, int> CalculateWizardStats(const std::string&,
                                                  GameState*);

  int NumPieces() const { return game_pieces; }
  int NumPieces(const std::string&);
  int NumPieces(const std::string&, const std::string&);
};

// Helper Functions

// Calculates <power, speed> of wizard piece.
// std::pair<int,int> CalculateWizardStats(const std::string&, GameState*);
