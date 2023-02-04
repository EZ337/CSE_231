#include "GameState.hpp"
#include "GamePiece.hpp"
#include <sstream>

GamePiece::GamePiece(const std::string& player, const std::string& archetype,
                     GameState* game_state) {
  owner_ = player;
  archetype_ = archetype;
  game_state_ = game_state;
  game_state->LogGamePiece(player, archetype, true);
}

/*I shouldn't have to write this all over. But Destructor is called
if I don't. Possible reasoning being that by using *this, I create a new
instance that goes out of scope. But how to fix that?
*/
GamePiece::GamePiece(const GamePiece& og) {
  owner_ = og.owner_;
  archetype_ = og.archetype_;
  game_state_ = og.game_state_;
  game_state_->LogGamePiece(owner_, archetype_, true);
  //*this = GamePiece(og.owner_, og.archetype_, og.game_state_);
}

GamePiece& GamePiece::operator=(const GamePiece& rhs) {
  this->~GamePiece();
  // this(rhs);
  // Duplicate code. If I get marked down for this, can you please tell me how I
  // should've done this. I thought  long and hard on this and drew blanks
  owner_ = rhs.owner_;
  archetype_ = rhs.archetype_;
  game_state_ = rhs.game_state_;
  game_state_->LogGamePiece(owner_, archetype_, true);
  return *this;
}

GamePiece::~GamePiece() {
  game_state_->LogGamePiece(owner_, archetype_, false);
}

std::pair<int, int> CalculateWizardStats(const std::string& owner,
                                         GameState* game_state) {
  int wiz_power = game_state->player_info[owner]["Wizard"], wiz_speed,
      wiz_count = 0;
  // For each player in player_info...
  for (auto& player : (game_state->player_info)) {
    if (player.first == owner)
      continue;  // Don't count my team
    else         // Only count enemy team
      wiz_count += player.second["Wizard"];
  }

  wiz_speed = (12 - wiz_count);
  if (wiz_speed <= 0) wiz_speed = 1;
  return std::make_pair(wiz_power, wiz_speed);
}

int GamePiece::GetPower() const {
  if (archetype_ == "Warrior")
    return 5;
  else if (archetype_ == "Scout")
    return 1;
  else if (archetype_ == "Wizard")
    return (CalculateWizardStats(owner_, game_state_)).first;
  return -1;
}

int GamePiece::GetSpeed() const {
  if (archetype_ == "Warrior")
    return 2;
  else if (archetype_ == "Scout")
    return 8;
  else if (archetype_ == "Wizard")
    return (CalculateWizardStats(owner_, game_state_)).second;
  return -1;
}

bool operator==(const GamePiece& p1, const GamePiece& p2) {
  if ((p1.GetPower() == p2.GetPower()) && (p1.GetSpeed() == p2.GetSpeed()))
    return true;
  return false;
}

bool operator!=(const GamePiece& p1, const GamePiece& p2) {
  return !(p1 == p2);
}

bool operator>(const GamePiece& p1, const GamePiece& p2) {
  int power1 = p1.GetPower(), power2 = p2.GetPower();
  if (power1 > power2)  // || (p1.GetSpeed() > p2.GetSpeed()))
    return true;
  else if (power1 == power2) {
    if (p1.GetSpeed() > p2.GetSpeed()) return true;
  }
  return false;
}

bool operator<(const GamePiece& p1, const GamePiece& p2) {
  int power1 = p1.GetPower(), power2 = p2.GetPower();
  if (power1 < power2)  // || (p1.GetSpeed() > p2.GetSpeed()))
    return true;
  else if (power1 == power2) {
    if (p1.GetSpeed() < p2.GetSpeed()) return true;
  }
  return false;
}

bool operator>=(const GamePiece& p1, const GamePiece& p2) {
  if ((p1 == p2) || (p1 > p2)) return true;
  return false;
}

bool operator<=(const GamePiece& p1, const GamePiece& p2) {
  if ((p1 == p2) || (p1 < p2)) return true;
  return false;
}

std::ostream& operator<<(std::ostream& out, const GamePiece& piece) {
  out << '(' << piece.owner_ << ',' << piece.archetype_ << ','
      << piece.GetPower() << ',' << piece.GetSpeed() << ')';
  return out;
}
