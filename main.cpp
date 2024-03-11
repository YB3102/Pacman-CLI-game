#include "Player.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

int main(){
    Game pacman = Game();

    std::vector <Player*> enemy;

    std::cout << "Please input your name for the player. " << std::endl;

    std::string player_string = "";

    std::cin>>player_string;

    Player * human = new Player(player_string,true); //name of player
    

    //Player * test_enemy = new Player("Ghost1", false);

    //test_enemy->SetPosition({0,3});

    std :: cout << "Please enter the number of enemies. 2 is minimum. Max is 4." << std :: endl;
    int enemy_input = -1;

    //enemy.push_back(test_enemy);
    //ask if there should be a limit on ghosts

    while (enemy_input < 2 || enemy_input >= 5){
        std::cin >> enemy_input;
    }

    std :: cout << "Game is beginning now. Collect all the pellets to finish the game." << std :: endl;
    std :: cout << "Remember that the ghosts will move even if you run into a wall." << std :: endl;
    std :: cout << "Collect treasure to kill a ghost. Another ghost will respawn at a random square after its death." << std::endl;


    int menu_loop_flag = 0;

    pacman.NewGame(human, enemy, enemy_input); //initializing new game

    std::cout << pacman << std::endl;

    while( (pacman.IsGameOver(human) !=true) && (pacman.CheckifdotsOver() != true) ){

        if (menu_loop_flag == 0){
            // player take turn

            enemy = pacman.get_enemies_(); //enemies vector

            Board * gameBoard = pacman.get_board(); //board

            std :: vector <std :: string> valid_positions = pacman.GetMoveNames(human, gameBoard->GetMoves(human));

            std::cout << "Select one of the following. WASD for directions is also fine: " << std::endl;

            for (std :: string pos_choice : valid_positions){
                std::cout << pos_choice << std::endl; //printing the valid positions to the users
            }

            std :: string choicealpha; //user pos choice

            std::cin >> choicealpha;

            //Position choicePosition = pacman.GetPositionFromChoice(choicealpha, valid_positions, gameBoard->GetMoves(human));

            bool player_turn = pacman.TakeTurn(human, choicealpha, enemy); //player turn

            if (player_turn == true){ //player turn success
                pacman.IncrementMoves();
                std::cout << "Board after your turn: " << std::endl;
                std::cout << pacman << std::endl;
            } 
            else{ //invalid choice reinput
                std::cout << "Invalid input. Please re-enter a correct choice. WASD for movement is fine as well." << std::endl;
            }

            // enemy ake turn
            for(Player * test_enemy : enemy){ //iterating each enemy

                bool enemy_turn = false;
                if (test_enemy->get_is_dead() == false){ //take turn if still alive 
                    enemy_turn = pacman.TakeTurnEnemy(test_enemy);
                }
                else{ //if killed, generate new ghost
                    std::cout << test_enemy->get_name() << " has been defeated." << std::endl;
                    //gameBoard->SetSquareValue(test_enemy->get_position(), 
                    std::cout << "Board with enemy dead: " << std::endl;
                    std::cout << pacman << std::endl;
                    std::cout << "Generating a new enemy." << std::endl;
                    Player * new_ghost = pacman.GenGhost(test_enemy);
                    enemy.erase(std::remove(enemy.begin(), enemy.end(), test_enemy), enemy.end()); //removing trace of ghost
                    enemy.push_back(new_ghost); //new ghost
                }

                if (enemy_turn == true){ //printing board after enemy turn
                    std::cout << "Board after " + test_enemy->get_name() + "'s turn: " << std::endl;
                    std::cout << pacman << std::endl;
                }
            }

            if(pacman.CheckifdotsOver() == true){ //game over if all dots collected
                std :: cout << "Game over" << std::endl;
                std::cout << pacman.GenerateReport(human) << std :: endl;
                delete human; //freeing mem
    
                for (Player * ghost : enemy){
                    delete ghost;
                }
                return 0;
                menu_loop_flag = 1;
            }
            if(pacman.IsGameOver(human) == true){ //game over if player dead
                std::cout << "Game over" << std::endl;
                std::cout << pacman.GenerateReport(human) << std :: endl;
                delete human; //freeing mem
    
                for (Player * ghost : enemy){
                    delete ghost;
                }
                return 0;
                menu_loop_flag = 1;
            }

        }
    }

    delete human; //freeing mem
    
    for (Player * ghost : enemy){
        delete ghost;
    }

    return 0;
}