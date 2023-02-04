#pragma once
#include <ostream>

class GameState;

class GamePiece {
 private:
  std::string owner_;
  std::string archetype_;
  GameState* game_state_;

 public:
  // Initializes Vars and Logs info
  GamePiece(const std::string&, const std::string&, GameState*);

  // Copy Constructor
  GamePiece(const GamePiece&);

  // Assignment Constructor
  GamePiece& operator=(const GamePiece&);

  // Destructor
  ~GamePiece();

  // Getters

  // Get owner of this piece
  std::string GetPlayer() const { return owner_; }
  // Get class of this piece
  std::string GetType() const { return archetype_; }
  // Get power of this piece. Returns -1 if archetype does not exist
  int GetPower() const;
  // Get speed of this piece. Returns -1 if archetype does not exist
  int GetSpeed() const;

  // friends

  // Compares two GamePieces for equal strength.
  friend bool operator==(const GamePiece&, const GamePiece&);
  friend bool operator!=(const GamePiece&, const GamePiece&);
  friend bool operator>(const GamePiece&, const GamePiece&);
  friend bool operator<(const GamePiece&, const GamePiece&);
  friend bool operator>=(const GamePiece&, const GamePiece&);
  friend bool operator<=(const GamePiece&, const GamePiece&);
  friend std::ostream& operator<<(std::ostream&, const GamePiece&);
};
