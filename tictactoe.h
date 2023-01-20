//
// Created by Benjamin Ries-Roncalli on 5/12/22.
//

#ifndef MAIN_TICTACTOE_TICTACTOE_H
#define MAIN_TICTACTOE_TICTACTOE_H

#include "string"

class tictactoe {
public:
    void startSeries(); // runs a series of games of tic-tac-toe
private:
    const int MAX_BOARDSIZE = 25;
    int playGame(int size); // plays one game of tic-tac-toe
    void bootup(); // clears screen & explains game
    void scoreboard(int player1_wins, int player2_wins, int ties); // displays running score of games
    void boardDeleter(std::string **board, int size); // deletes board pointer
    void displayBoard(std::string** board, int size); // pretty display of 2D array board w/ current pieces placed
    void askMove(std::string **board, int size, int turn); // asks user for move, checks if valid, & updates 2D board array accordingly
    std::string** makeBoard(int size); // initializes empty board (2D array) of size
    int winCheck(std::string** board, int size, int turns); //returns 1 if p1 wins, 2 if p2 wins, 3 if tie, 0 if still going
};


#endif // MAIN_TICTACTOE_TICTACTOE_H
