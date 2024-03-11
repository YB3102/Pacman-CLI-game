#include <iostream>
#include <fstream>
#include <algorithm>
#include "Game.h"

/**
 * @brief This function converts a SquareType into corresponding string and returns it.
 * 
 * @param SquareType sq 
 * @return std::string 
 */

std::string SquareTypeStringify(SquareType sq){

    switch(sq){
        case (SquareType :: Wall):
            return "[X]";
            break;
        case (SquareType :: Dots):
            return "[O]";
            break;
        case (SquareType :: Pacman):
            return "(O_O)";
            break;
        case (SquareType :: Treasure):
            return "[T]";
            break;
        case (SquareType :: Enemies):
            return "(X+X)";
            break;
        case (SquareType :: Empty):
            return "[]";
            break;
        case (SquareType :: PowerfulPacman):
            return "|0_O|";
            break;
        case (SquareType :: Trap):
            return "[!]";
            break;
        case (SquareType :: EnemySpecialTreasure):
            return "[S]";
            break;
        default:
            return "";
            break;
    }
    
}

/**
 * @brief This function converts a SquareType square into corresponding square.
 * 
 * @param sqst 
 * @return SquareType 
 */
SquareType StringSquareTypify(std::string sqst){

    if (sqst == "[X]"){
        return SquareType :: Wall;
    }
    else if (sqst == "[O]"){
        return SquareType :: Dots;
    }
    else if (sqst == "(O_O)"){
        return SquareType :: Pacman;
    }
    else if (sqst == "[T]"){
        return SquareType :: Treasure;
    }
    else if (sqst == "(X+X)"){
        return SquareType :: Enemies;
    }
    else if (sqst == "|0_O|"){
        return SquareType :: PowerfulPacman;
    }
    else if (sqst == "[!]"){
        return SquareType :: Trap;
    }
    else if (sqst == "[S]"){
        return SquareType :: EnemySpecialTreasure;
    }
    else{
        return SquareType :: Empty;
    }
}

/**
 * @brief Construct a new Board:: Board object
 *        Constructs the board for the game.
 *        Takes a txt file containing the board as input and converts
 *        stores the tiles into the SquareType arr_.
 * 
 */

Board::Board(){

    std::ifstream inputFile("board.txt");

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file. Board not initialized" << std::endl;
    }

    else{
        std::string board[10][10];

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                std::string element;
                inputFile >> std::noskipws >> element >> std::ws;
                board[i][j] = element;
            }
        }

        // Close the file
        inputFile.close();

        // Print the array to verify the data has been read
        /*for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                std::cout << board[i][j] << "\t";
            }
            std::cout << std::endl;
        } */

        for (int i = 0; i < 10; ++i){
            for (int j = 0; j < 10; ++j){
                this->arr_[i][j] = StringSquareTypify(board[i][j]);
            }
        }
    }
}

/**
 * @brief Returns the SquareType value of a given square/tile.
 * 
 * @param pos Position of the tile on the board
 * @return SquareType 
 */

SquareType Board::get_square_value(Position pos) const{
    return this->arr_[pos.row][pos.col];
}

/**
 * @brief Sets the SquareType value of a passed position on the board.
 * 
 * @param pos Position of the square on the board
 * @param value The value to be assigned to the square
 */
void Board::SetSquareValue(Position pos, SquareType value){
    this->arr_[pos.row][pos.col] = value;
}

/**
 * @brief Returns the valid moves that the human player can take at a position on the board as a vector.
 *        Checks each direction as well as bound conditions.
 * 
 * @param p Pointer to the Player p object.
 * @return std::vector<Position> The Positions that the player can move to
 */
std::vector<Position> Board::GetMoves(Player *p){
    
    Position player_pos = p->get_position();
    std::vector <Position> valid;
    int player_r = player_pos.row;
    int player_c = player_pos.col;

    //std :: cout << player_r << player_c << std::endl;

    SquareType other_tile;

    if ((0 <= player_r + 1 && player_r + 1 <= 9) && (0 <= player_c && player_c <= 9 )){
        
        Position other = {player_r+1, player_c};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall)){
            valid.push_back(other);
        }

    }

    if ((0 <= player_r - 1 && player_r - 1 <= 9) && (0 <= player_c && player_c <= 9 )){
        
        Position other = {player_r-1, player_c};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall)){
            valid.push_back(other);
        }

    }

    if ((0 <= player_r && player_r <= 9) && (0 <= player_c+1 && player_c+1 <= 9 )){
        
        Position other = {player_r, player_c+1};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall)){
            valid.push_back(other);
        }

    }

    if ((0 <= player_r && player_r <= 9) && (0 <= player_c-1 && player_c-1 <= 9 )){
        
        Position other = {player_r, player_c-1};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall)){
            valid.push_back(other);
        }

    }

    return valid;
}

/**
 * @brief Checks all the valid positions that a ghost can move to. Returns a Position vector of valid positions.
 *        Similar to GetMoves in function.
 * 
 * @param p Pointer to the enemy ghost object p.
 * @return std::vector<Position> Vector of valid positions for the ghost to move to.
 */

std::vector<Position> Board::GetEnemyMoves(Player *p){

    Position enemy_pos = p->get_position();
    std::vector <Position> valid;
    int enemy_r = enemy_pos.row;
    int enemy_c = enemy_pos.col;

    SquareType other_tile;

    if ((0 <= enemy_r + 1 && enemy_r + 1 <= 9) && (0 <= enemy_c && enemy_c <= 9 )){
        
        Position other = {enemy_r+1, enemy_c};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall) && (other_tile!= SquareType::Enemies) && (other_tile!= SquareType::Treasure)){
            valid.push_back(other);
        }

    }

    if ((0 <= enemy_r - 1 && enemy_r - 1 <= 9) && (0 <= enemy_c && enemy_c <= 9 )){
        
        Position other = {enemy_r-1, enemy_c};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall)&& (other_tile!= SquareType::Enemies) && (other_tile!= SquareType::Treasure)){
            valid.push_back(other);
        }

    }

    if ((0 <= enemy_r && enemy_r <= 9) && (0 <= enemy_c+1 && enemy_c+1 <= 9 )){
        
        Position other = {enemy_r, enemy_c+1};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall)&& (other_tile!= SquareType::Enemies) && (other_tile!= SquareType::Treasure)){
            valid.push_back(other);
        }

    }

    if ((0 <= enemy_r && enemy_r <= 9) && (0 <= enemy_c-1 && enemy_c-1 <= 9 )){
        
        Position other = {enemy_r, enemy_c-1};

        other_tile = this->get_square_value(other);

        if ((other_tile != SquareType::Wall) && (other_tile!= SquareType::Enemies) && (other_tile!= SquareType::Treasure)){
            valid.push_back(other);
        }

    }

    return valid;

}

/**
 * @brief This function moves the player to the Position pos provided it is valid.
 *        It also performs computation depending on the SquareType of the Position pos square tile.
 *        Returns a bool indicating success or failure.
 * 
 * @param p Pointer to human player object p.
 * @param pos The Position the player wishes to move to.
 * @param enemylist Passed list of enemies on board to help with computation.
 * @return true Booleans indicating return status.
 * @return false 
 */

bool Board :: MovePlayer(Player *p, Position pos, std::vector<Player *> enemylist){

    std::vector <Position> valid_player_positions = this->GetMoves(p); //getting valid moves


    std::vector <Position> current_enemy_positions;

    for (Player * enemy : enemylist){
        current_enemy_positions.push_back(enemy -> get_position()); //all corresponding pos of enemies
    } 

    //checking if the passed pos is valid

    bool valid_pos = false;

    for (Position valid : valid_player_positions){
        if (valid == pos){
            valid_pos = true; 
        }
    }

    if (valid_pos == false){
        return false; //pos not found in valid
    }
    
    else{
        if(this->get_square_value(pos) == SquareType::Wall){
            return false;
        }
        
        else if (this->get_square_value(pos) == SquareType::Dots){
            p->ChangePoints(1);
        }
        else if (this->get_square_value(pos) == SquareType::Treasure){
            p->ChangePoints(100);
            if (p->get_has_treasure() == false){
                p->SetHasTreasure();
            }
        }
        else if (this->get_square_value(pos) == SquareType::Enemies){

            if(p->get_has_treasure() == true){ //Power Pac

                int enemy_index = -1;

                for (int i = 0; i < (int)current_enemy_positions.size(); i++){
                    if (pos == current_enemy_positions[i]){
                        enemy_index = i;
                        break;
                    }
                }

                if(enemy_index == -1){
                    return false;   //confirming corresponding index exists.
                }

                enemylist[enemy_index] -> SetIsDead(true); //killing ghost
                enemylist.erase(std::remove(enemylist.begin(), enemylist.end(), enemylist[enemy_index]), enemylist.end()); //erasing existence
                p->SetHasTreasure(); //deactivating power
            }

            else{
                p->SetLives((p->get_lives()-1)); //otherwise lose 1 life
                //this->SetSquareValue(p->get_position(), SquareType::Empty);
                //p->SetPosition({0,0});
                //this->SetSquareValue({0,0}, SquareType::Pacman);
                if(p->get_lives() == 0){ //pac death
                    p->SetIsDead(true);
                }
                return true;
            }

        }

        //setting universal rule conditions:

        this->SetSquareValue(p->get_position(), SquareType::Empty); //moving pac to new pos

        p->SetPosition(pos);

        if(p->get_has_treasure() == false){
            this->SetSquareValue(pos, SquareType::Pacman);
        }
        else{
            this->SetSquareValue(pos, SquareType::PowerfulPacman);
        }

        return true;

    }
}

/**
 * @brief This function is similar to MovePlayer but for the ghosts.
 *        Checks if passed Position pos is valid.
 *        Moves ghost to new position if all checks out. 
 *        Little computation because human player is not passed in params.
 * 
 * @param p Pointer to the ghost player object p.
 * @param pos The position the ghost wishes to move to.
 * @return true Boolean indicating return status.
 * @return false 
 */

bool Board :: MoveEnemy(Player *p, Position pos){

    
    std::vector <Position> valid_player_positions = this->GetEnemyMoves(p); //get moves for enemy

    //checking if the passed pos is valid

    bool valid_pos = false;

    for (Position valid : valid_player_positions){
        if (valid == pos){
            valid_pos = true;
        }
    }

    if (valid_pos == false){
        return false; //valid move not found;

    }  
    
    else{
        if(this->get_square_value(pos) == SquareType::Wall){
            return false;
        }

        else if(this->get_square_value(pos) == SquareType::Enemies){
            return false;
        }

        else if(this->get_square_value(pos) == SquareType::Treasure){
            return false;
        }

        else if (this->get_square_value(pos) == SquareType::Pacman){
            return false;
        }

        //setting universal rule conditions:

        if (p->get_prev_square() == SquareTypeStringify(SquareType::Pacman)){
            this->SetSquareValue(p->get_position(), SquareType::Empty);

            p -> SetPrevSquare("[]"); //storing previous tile info as empty if pacman (redundant code)
        }

        else{

        this->SetSquareValue(p->get_position(), StringSquareTypify(p->get_prev_square())); //storing prev tile info

        p -> SetPrevSquare(SquareTypeStringify(this->get_square_value(pos))); //resetting the tile ghost was on
        }

        if(this -> get_square_value(pos) == SquareType::PowerfulPacman){
            p->SetIsDead(true); //dying if going against power pac
            this->SetSquareValue(pos, SquareType::Pacman); //power pac on tile now
            return true;
        }

        p->SetPosition(pos); //else change pos

        this->SetSquareValue(pos, SquareType::Enemies);

        return true;
    
    }
}
/**
 * @brief Overload operator for printing the game board.
 * 
 * @param os Overloaded output stream
 * @param b Passed by reference game board b.
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &os, const Board &b){
    os << "Printing the board now: " << std::endl;
    
    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 10; ++j){
            os << SquareTypeStringify(b.arr_[i][j]) << "\t";
        }
        os << std::endl;
    }
    return os;
}

//--------   Game   Class   --------

/**
 * @brief Construct a new Game:: Game object
 * Added an additional enemies_ param vector to keep track of enemies on board
 * whenever needed by computation.
 */

Game::Game(){
    this->board_ = new Board();
    std::vector<Player *> players_;
    this->turn_count_ = 0;
    this->dots_count_ = 0;
    this->moves_ = 0;
    this->game_over_ = false;
    std::vector<Player *> enemies_;
}

/**
 * @brief Destroy the Game:: board_ object
 * 
 */
Game::~Game(){
    delete this->board_;

    for (Player * p : this->players_){
        delete p;
    }

    for (Player * p : this->enemies_){
        delete p;
    }
}

/**
 * @brief Generates a ghost on the death of a ghost. Takes the dying ghost as a param for deletion.
 *        Creates a new ghost inside of the function to be stored. 
 *        Also chooses a random position.
 * 
 * @param p Pointer to the dying ghost enemy Player p.
 * @return Player* The new ghost to respawn on the board.
 */
Player * Game :: GenGhost(Player * p){

    int ghost_gen_flag = -1;

    int enemylist_size = (int)this->enemies_.size();

    Player * new_ghost = new Player ("Ghost "+std::to_string(enemylist_size), false); //creating the ghost

    new_ghost->SetPrevSquare("[]");

    while(ghost_gen_flag = -1){ //flag for loop

        srand(time(0));
        int random_row = rand()%10;
        int random_col = rand()%10;
        Position temp_gen = {random_row, random_col};
        SquareType temp_gen_square = this->board_->get_square_value(temp_gen); //random tile

        if((temp_gen_square != SquareType::Wall) && (temp_gen_square != SquareType::Pacman) //making sure that none of these
            && (temp_gen_square != SquareType::Treasure) && (temp_gen_square != SquareType::Enemies)){
                this->board_->SetSquareValue(temp_gen, SquareType::Enemies);
                new_ghost -> SetPosition(temp_gen);

                this->board_->SetSquareValue(new_ghost->get_position(), SquareType::Enemies);

                this->enemies_.push_back(new_ghost);

                this->players_.push_back(new_ghost); //pushing ghost to the vectors

                this->enemies_.erase(std::remove(this->enemies_.begin(), this->enemies_.end(), p), this->enemies_.end()); //killing old ghost

                this->players_.erase(std::remove(this->players_.begin(), this->players_.end(), p), this->players_.end()); //confirming death

                return new_ghost;

                ghost_gen_flag = 0; //redundant
            }
    }

    return NULL; //incase not initialized
    
}

/**
 * @brief This function initializes the game. Creates a human player and allocates ghosts according to int enemies.
 *        Also generate "random" positions for the ghosts, minus the upper quadrant to give the player some
 *        breathing room at start.
 * 
 * @param human The human player
 * @param enemylist Vector of enemies to be initialized on the board
 * @param enemies int number of enemies to be initialized
 */
void Game::NewGame(Player *human, std::vector<Player *> enemylist, const int enemies){
    this->board_->SetSquareValue({0,0}, SquareType::Pacman);
    human->SetPosition({0,0});
    players_.push_back(human);

    this->dots_count_ = (100 - 36 - 1);

    for (int i = 0; i < enemies; i++){
        
        Player * test_enemy = new Player ("Ghost "+std::to_string(i), false);

        enemylist.push_back(test_enemy);
    }

    //getting random pos for the square for ghosts first

    srand(time(0));
    int ghost_gen_flag = 0;

    while(ghost_gen_flag != enemies){
        int random_row = rand()%10;
        int random_col = rand()%10;
        Position temp_gen = {random_row, random_col};
        SquareType temp_gen_square = this->board_->get_square_value(temp_gen);
        Position pac_spawn = {0,0};

        if((temp_gen != pac_spawn)&&(temp_gen_square != SquareType::Wall) && (temp_gen_square != SquareType::Pacman) 
            && (temp_gen_square != SquareType::Treasure) && (temp_gen_square != SquareType::Enemies)
            &&(temp_gen.col >= 4) && (temp_gen.row >=4)){
                this->board_->SetSquareValue(temp_gen, SquareType::Enemies);
                enemylist[ghost_gen_flag] -> SetPosition(temp_gen);
                ghost_gen_flag = ghost_gen_flag + 1;
            }
    }
     for(int i = 0; i < enemies; i++){
        this->board_->SetSquareValue(enemylist[i]->get_position(), SquareType::Enemies);
        this->players_.push_back(enemylist[i]);
        this->enemies_.push_back(enemylist[i]);
    }
}

/**
 * @brief Returns a vector of the valid moves that the human player can make as strings.
 * 
 * @param p Pointer to The human player p
 * @param positions Vector of valid position
 * @return std::vector<std::string> 
 */

std::vector<std::string> Game::GetMoveNames(Player *p, const std::vector<Position> &positions){
    std::vector<Position> valid_positions = this->board_->GetMoves(p); //redundant but kept in

    std::vector<std::string> store_move_names;

    for (Position pos : valid_positions){
        std :: string curr_string = p->ToRelativePosition(pos);
        store_move_names.push_back(curr_string);
    }

    return store_move_names;
}

/**
 * @brief Takes a string choice and verifies if the string is in names and valid positions.
 *        Also converts it to output from ToRelativeInput() for easier usability.
 * 
 * @param choice The string to be verified
 * @param names The valid positions vector but as string
 * @param positions The valid position vector but as Positions
 * @return Returns the position corresponding to the choice if verified properly. {-1, -1} otherwise.
 */
Position Game::GetPositionFromChoice(const std::string choice, const std::vector<std::string> names, const std::vector<Position> positions){
    //Player * human = this->players_[0];

    //passed param positions is same thing as GetMoves called on player p;
    //passed param string names is same thing as Game's GetMoveNames;

    std::string empty_choice = "";

    for (int i = 0; i < (int)choice.size(); i++){
        char append = tolower(choice[i]);
        empty_choice = empty_choice + append;
    }

    if (empty_choice == "w"){
        empty_choice = "up";
    }
    else if (empty_choice == "s"){
        empty_choice = "down";
    }
    else if (empty_choice == "d"){
        empty_choice = "right";
    }
    else if (empty_choice == "a"){
        empty_choice = "left";
    }

    //need to check whether or not choice in names;
    for (int i = 0; i < (int)names.size(); i++){
        if (empty_choice == names[i]){
            return positions[i];
            break;
        }
    }

    return {-1,-1};
}

/**
 * @brief Handles interactions between occupant SquareType and the Player *p.
 * 
 * @param p The Player object who wishes to occupy the square of the current occupant.
 * @param occupant The SquareType of the square to which the player object wishes to move to.
 * @return true Boolean indicating return status.
 * @return false 
 */
bool Game::HandleOccupant(Player *p, SquareType occupant){

    //Position p_curr_pos = p->get_position();
    
    if (occupant == SquareType::Wall){
        return false;
    }

    if (p->get_is_human() == false){
        if (occupant == SquareType::Enemies){
            return false;
        }
        else{
            return true;
        }
    }

    return true;
}

/**
 * @brief Handles computation for intiating a player turn. Takes care of stuff such as getting valid moves
 *        Verifying user position choice. Manages current dot, and turn count.
 *        Finally initiates the move, returning a boolean indicating if the move was successful or not.
 * 
 * @param p Point to the human player p.
 * @param choice The position choice from the user.
 * @param enemylist Vector of enemies currently on the board.
 * @return true Boolean indicating return status.
 * @return false 
 */
bool Game :: TakeTurn(Player *p, const std::string &choice, std::vector<Player *> &enemylist){

    std :: vector <Position> valid_player_pos = this->board_->GetMoves(p);

    std :: vector <std :: string> string_moves = this->GetMoveNames(p, valid_player_pos);

    Position pos_choice = this -> GetPositionFromChoice(choice, string_moves, valid_player_pos);

    //int flag = 0;

    //Position impossible = {-1, -1};

    if (pos_choice.col <0 || pos_choice.col >9 || pos_choice.row > 9 || pos_choice.row < 0){
        return false;
    }

    if (this->board_->get_square_value(pos_choice) == SquareType::Dots){
        this->dots_count_ = this->dots_count_ - 1;
    }

    bool turn_movement = this->board_->MovePlayer(p, pos_choice, enemylist);

    if (turn_movement == true){
        this->turn_count_ = this->turn_count_ + 1;
    }

    return turn_movement;

}

/**
 * @brief Initiates the turn for the ghost enemies. Also takes care of interactions with pacmans. 
 *        Otherwise, similar to TakeTurn() in operation.
 * 
 * @param p  Pointer to the ghost enemy p.
 * @return true 
 * @return false 
 */

bool Game :: TakeTurnEnemy(Player *p){
    std :: vector <Position> valid_enemy_pos = this->board_->GetEnemyMoves(p);

    int pos_size = (int)valid_enemy_pos.size();

    srand(time(0));

    int rand_pos = rand() % pos_size; //random pos from the valid positions that the ghost can move to

    if((valid_enemy_pos[rand_pos] == this->players_[0]->get_position())){ //pac and ghost clash

        if(this->players_[0]->get_has_treasure() == false){ //normal pac, pac loses life

            this->players_[0]->SetLives((this->players_[0]->get_lives()-1));
            //this->board_->SetSquareValue(this->players_[0]->get_position(), SquareType::Empty);
            //this->players_[0]->SetPosition({0,0});
            //this->board_->SetSquareValue({0,0}, SquareType::Pacman);
            if(this->players_[0]->get_lives() == 0){
                this->players_[0]->SetIsDead(true);
            }
        }
        else{
            p->SetIsDead(true); //power pac, ghost dies
            this->players_[0]->SetHasTreasure();
        }
    }

    bool enemy_turn_movement = this->board_->MoveEnemy(p, valid_enemy_pos[rand_pos]); //initiating move

    if (enemy_turn_movement == true){
        this->turn_count_ = this->turn_count_ + 1;
    }

    return enemy_turn_movement;
}

/**
 * @brief Checks if the human player is dead
 * 
 * @param p Pointer to the human player
 * @return true Boolean indicating player death status
 * @return false 
 */
bool Game :: IsGameOver(Player *p){
    bool player_status = p->get_is_dead();

    this->game_over_ = player_status;

    if(this->game_over_ == true){
        return true;
    }

    else{
        return false;
    }
}

/**
 * @brief Counts if pac has collected all dots
 * 
 * @return true if all dots over
 * @return false if still dots on board
 */
bool Game :: CheckifdotsOver(){

    //manually calculating dots if constant approach doesn't work in new_game() function

    /*int dot_count = 0;

    for(int i = 0; i<10; i++){
        for (int j = 0; i<10; j++){

        }
    } */


    if (this->dots_count_ == 0){
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Creates a string with information on how many dots pac has as well as the current turn count.
 * 
 * @param p Pointer to the human player p.
 * @return std::string 
 */
std::string Game :: GenerateReport(Player *p){
    int total_entities = (int)this->players_.size();
    int original_dots = (100 - 36 - (total_entities));
    int obtained_dots = original_dots - this->dots_count_;

    //Player * human = this->players_[0];

    std :: string report = "Number of pellets collected: " + std::to_string(obtained_dots) + " in " + std::to_string(this->moves_) + " moves.";

    return report;
}

/**
 * @brief Overload output stream operator to print the game's board
 *        Also prints some of pac's attributes such as points and current lives.
 * 
 * @param os Overloaded output stream
 * @param m Passed by reference Game object m.
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &os, const Game &m){

    os << "Pacman has " << m.players_[0]->get_lives() << " lives left." << std::endl;
    os << "Pacman has " << m.players_[0]->get_points() << " points so far." << std::endl;
    os << "Pacman has made " << m.moves_ << " valid moves so far." << std::endl;
    os << "Game is currently on turn: " << m.turn_count_ << std::endl;
    os << "Printing the board now: " << std::endl;
    
    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 10; ++j){

            os << SquareTypeStringify(m.board_->get_square_value({i,j})) << "\t";
        }
        os << std::endl;
    }
    return os;
}