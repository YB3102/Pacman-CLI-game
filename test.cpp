#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

#include "Player.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <vector>

// Player 
TEST_CASE ("Player"){

    SECTION("Constructor, [Player]"){

        std::string name = "YB";
        Player initPlayer = Player(name, true);

        REQUIRE(initPlayer.get_name() == "YB");
        Position a = {5,5};
        initPlayer.SetPosition(a);
        REQUIRE(initPlayer.get_position().row == a.row);
        REQUIRE(initPlayer.get_position().col == a.col);
        Position b = {6,6};
        initPlayer.SetPosition(b);
        REQUIRE(initPlayer.get_position().row == b.row);
        REQUIRE(initPlayer.get_position().col == b.col);
        REQUIRE(initPlayer.get_is_dead() == false);
        REQUIRE(initPlayer.get_has_treasure() == false);
        initPlayer.SetHasTreasure();
        REQUIRE(initPlayer.get_has_treasure() == true);
        REQUIRE(initPlayer.get_lives() == 3 );
        initPlayer.SetLives(2);
        REQUIRE(initPlayer.get_lives() == 2 );
        REQUIRE(initPlayer.get_is_human() == true);
        REQUIRE(initPlayer.get_prev_square() == "[O]");
    }

    SECTION("ToRelativePosition()"){
        Position up{5,6};
        Position b{6,6};
        Position a{5,5};
        std::string name = "YB";
        Player initPlayer = Player(name, true);

        REQUIRE(initPlayer.get_name() == "YB");
        initPlayer.SetPosition(a);
        REQUIRE(initPlayer.get_position().row == a.row );
        REQUIRE(initPlayer.get_position().col == a.col);
        initPlayer.SetPosition(b);
        REQUIRE(initPlayer.get_position().row == b.row);
        REQUIRE(initPlayer.get_position().col == b.col);

        REQUIRE(initPlayer.ToRelativePosition(up) == "up");
    }

}

// Board 

TEST_CASE ("Board"){
    // testing constructors
    Board b = Board(); //reads txt

    std::string name = "YB";
    Player* initPlayer = new Player(name, true);
    initPlayer->SetPosition({5,5});

    b.SetSquareValue(initPlayer->get_position(), SquareType::Pacman);

    REQUIRE(b.get_square_value(initPlayer->get_position()) == SquareType::Pacman);

    SECTION("GetMoves()"){
        std::vector<Position> moves = b.GetMoves(initPlayer);

        std::vector<Position> testmoves = {{6,5}, {4,5}, {5,6}};

        REQUIRE(moves.size() == testmoves.size());

        for (int i = 0; i < (int)moves.size(); i++){
            REQUIRE(moves[i].col == testmoves[i].col);
            REQUIRE(moves[i].row == testmoves[i].row);
        }
    
    }
    
    delete initPlayer;
}

TEST_CASE ("Game"){
    Game g = Game();

    std::string name = "YB";
    Player * initPlayer = new Player(name, true);
    
    initPlayer->SetPosition({5,5});

    SECTION("GetMoveNames()"){
        std :: vector <std :: string> testvector = {"down", "up", "right"};

        std::vector <Position> valid_pos = g.get_board()->GetMoves(initPlayer);

        std::vector <std:: string> move_names = g.GetMoveNames(initPlayer, valid_pos);

        REQUIRE(testvector == move_names);
    }
    
    delete initPlayer;
} 