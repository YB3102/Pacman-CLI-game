#include <string>
#ifndef _PLAYER_H_
#define _PLAYER_H_

struct Position {
	int row;
	int col;

	// already implemented for you!
	bool operator==(const Position &other) {
		return row == other.row && col == other.col;
	}

	bool operator!=(const Position &other) {
		return row != other.row && col != other.col;
	}
};

class Player {
public:
	// TODO: implement
	Player(const std::string name, const bool is_human);  // constructor

	// These are already implemented for you
	std::string get_name() const {return name_; }  // inline member function
	int get_points() const {return points_; }  // inline member function
	Position get_position() const {return pos_; }  // inline member function
	bool get_is_human() const {return is_human_; }  // inline member function
	bool get_has_treasure() const {return has_Treasure_; }  // inline member function
	int get_lives() const {return lives_;}
	bool get_is_dead() const {return is_dead_; }  // inline member function

	std::string get_prev_square() {return previous_square; }

	// TODO: implement the following functions
	// You MUST implement the following functions
	void ChangePoints(const int x);

	// set a new position for this player
	void SetPosition(Position pos);

	void SetHasTreasure();

	void SetIsDead(bool isdead);

	void SetLives(int lives);

	void SetPrevSquare (std:: string prev_square);

	// You may want to implement these functions as well
	// ToRelativePosition is a function we used to translate positions
	// into direction s relative to the player (up, down, etc)
	std::string ToRelativePosition(Position other);

	// Convert this player to a string representation of their name and points
	std::string Stringify();

	// You may add other functions as needed/wanted

private:
	std::string name_;
	int points_;
	Position pos_;
	bool is_human_;
	bool has_Treasure_;
	bool is_dead_;
	int lives_;
	std::string previous_square;

	// You may add other fields as needed

}; // class Player

#endif  // _PLAYER_H_
