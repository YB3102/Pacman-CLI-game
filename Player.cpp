#include <iostream>
#include "Player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param name string
 * @param is_human boolean
 */

Player::Player(const std :: string name, const bool is_human){
    this->name_ = name;
    this->is_human_ = is_human;
    this->pos_ = {-1, -1};
    this->points_ = 0;
    this->has_Treasure_ = false;
    this->is_dead_ = false;
    this->lives_ = 3;
    this->previous_square = "[O]";
}

/**
 * @brief This function changes the points of the object by x value.
 * 
 * @param x int
 */

void Player::ChangePoints(const int x){
    this->points_ = this->points_ + x;
}

/**
 * @brief This function sets the Position of the object.
 * 
 * @param pos Position
 */

void Player::SetPosition(Position pos){
    this->pos_ = pos;
}

/**
 * @brief This function sets the inverse of player's current treasure held status.
 * 
 */
void Player::SetHasTreasure(){
    this->has_Treasure_ = !(this->has_Treasure_);
}

/**
 * @brief This function sets the player's death status.
 * 
 * @param isdead boolean
 */

void Player::SetIsDead(bool isdead){
    this->is_dead_ = isdead;
}

/**
 * @brief This function sets the number for lives for the player.
 * 
 * @param lives 
 */
void Player::SetLives(int lives){
    this->lives_ = lives;
}

/**
 * @brief This function sets the previous square the player was on as a string. Used for ghosts.
 * 
 * @param prev_square string
 */

void Player::SetPrevSquare(std::string prev_square){
    this->previous_square = prev_square;
}

/**
 * @brief This function converts the passed Position other param into a relative direction to the Player object on the board.
 *        Returns the direction as a string.
 * 
 * @param other Position
 * @return std::string 
 */

std::string Player::ToRelativePosition(Position other){

    int thisCol = this->pos_.col;
    int thisRow = this->pos_.row;
    int thatCol = other.col;
    int thatRow = other.row;

    if((thisRow - 1 == thatRow) && (thisCol == thatCol)){
        return "up";
    }
    else if ((thisRow + 1 == thatRow) && (thisCol == thatCol)){
        return "down";
    }
    else if ((thisRow == thatRow) && (thisCol + 1 == thatCol)){
        return "right";
    }
    else if ((thisRow == thatRow) && (thisCol - 1 == thatCol)){
        return "left";
    }
    else{
        return "Not a relative position.";
    }
    
}

/**
 * @brief Gives a brief line of the player's notable attributes as a string.
 * 
 * @return std::string 
 */
std::string Player::Stringify(){
    std :: string x;

    x = "The human player " + (this->name_) + " has " + std::to_string(this->points_) + " points.";

    return x;
}