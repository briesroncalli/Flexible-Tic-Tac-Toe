//
// Created by Benjamin Ries-Roncalli on 5/12/22.
//

#include "tictactoe.h"
#include "string"
#include "iostream"
using namespace std; 

// builds & returns empty gameboard that is 2D array
string **tictactoe::makeBoard(int size) {
    // 1D array of pointers to rows
    string **rowPointer = nullptr;
    rowPointer = new string *[size];

    // find space for rows that rowPointer points to
    for (int row = 0; row < size; row++)
        rowPointer[row] = new string[size];

    // fill the addresses the rowPointers point to
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            rowPointer[row][col] = " "; // initializes board to be empty

    return rowPointer;
}

// displays formatted board w/ current game state
void tictactoe::displayBoard(string **board, int size) {
    cout << "      ";
    // display column index
    for (int col=0; col<size; col++) {
        if (col < 10) { // double digits means column index display needs new spacing
            cout << " [" << col << "]  ";
        } else {  // started 1 earlier than double digits bc it looked better
            cout << " [" << col << "] ";
        }
    }

    for (int row=0; row<size; row++) {
        cout << "       ";
        if (row != 0 && row !=-1) {
            for (int i = 0; i < size; i++)
                cout << "------";
        }
        cout << endl;
        for (int col = -1; col < size; col++) {
            if (col == 0) {
                cout << "  " << board[row][col];
            } else if (col == size - 1) {
                cout << "  |  " << board[row][col];
            } else if (col == -1) { // display row index
                cout << "[" << row << "]:  " ;
            } else {
                    cout << "  |  " << board[row][col];
            }
        }
        cout << endl;
    }
}

// asks player for row & column, places the player's corresponding piece if valid choice
void tictactoe::askMove(string **board, int size, int turn) {
    bool valid_move = false;
    int row = -1; // initialized to -1 so not valid - forces user to pick square
    int col = -1; // initialized to -1 so not valid - forces user to pick square

    string player = "X"; // player 1 is X's & goes first
    if(turn %2 == 1) { // triggered every other turn & forces alternating turns
        player = "O"; // player 2 is O's & goes second
    }

    // force user to make valid choice for row & col (must be free)
    while (!valid_move) {

        // user must choose row that is within size of board
        bool valid_row = false;
        while (!valid_row) {
            cout << "row: ";
            cin >> row;
            if (0 <= row && row < size) {
                valid_row = true;
            } else {
                cout << "Invalid entry for row. Enter an integer between 0 and " << size - 1 << endl;
            }
        }

        // user must choose col that is within size of board
        bool valid_col = false;
        while (!valid_col) {
            cout << "column: ";
            cin >> col;
            if (0 <= col && col < size) {
                valid_col = true;
            } else {
                cout << "Invalid entry for column. Enter an integer between 0 and " << size - 1 << endl;
            }
        }

        // force user to pick empty space
        if (board[row][col] != " ") {
            cout << "Space already taken! Enter another space." << endl;
        } else {
            valid_move = true;
        }
    }

    board[row][col] = player; // fill board space with player's corresponding piece if space empty
}

//returns 0 for ongoing game, 1 for player 1 win, 2 for player 2 win, 3 for tie
int tictactoe::winCheck(string **board, int size, int turns) {
    int mainDiagXcount = 0;
    int mainDiagOcount = 0;
    int minDiagXcount = 0;
    int minDiagOcount = 0;

    // find if either player has a full diagonal
    for (int n = 0; n < size; n++) {
        // major diagonal check
        if (board[n][n] == "X") {
            mainDiagXcount++;
        } else if (board[n][n] == "O") {
            mainDiagOcount++;
        }

        // minor diagonal check
        if (board[n][size-1-n] == "X") {
            minDiagXcount++;
        } else if (board[n][size-1-n] == "O") {
            minDiagOcount++;
        }
    }

    if (mainDiagOcount == size || minDiagOcount == size) {
        return 2; // player 2 is O's
    } else if (mainDiagXcount == size || minDiagXcount == size) {
        return 1; // player 1 is X's
    }

    // find if either player has a full row
    for (int row = 0; row < size; row++) {
        int xRowSum = 0;
        int oRowSum = 0;
        for (int col = 0; col < size; col++) {
            if (board[row][col] == "X") {
                xRowSum++;
            } else if (board[row][col] == "O") {
                oRowSum++;
            }
        }
        if (oRowSum == size) {
            return 2; // player 2 is O's
        } else if (xRowSum == size) {
            return 1; // player 1 is X's
        }
    }

    // find if either player has a full column
    for (int col = 0; col < size; col++) {
        int xColSum = 0;
        int oColSum = 0;
        for (int row = 0; row < size; row++) {
            if (board[row][col] == "X") {
                xColSum++;
            } else if (board[row][col] == "O") {
                oColSum++;
            }
        }
        if (oColSum == size) {
            return 2; // player 2 is O's
        } else if (xColSum == size) {
            return 1; // player 1 is X's
        }
    }

    // check for tie
    if (turns >= size*size-1){
        return 3;
    }

    return 0;
}

// plays one game of tic-tac-toe and returns 1 if player 1 won, 2 if player 2 won, 3 if tie
int tictactoe::playGame(int size) {
    // set up board
    string **board = nullptr;
    board = makeBoard(size);

    int turn = 0;
    int player = 0; // player 1 is X's, player 2 is O's
    string piece = "";

    int gameWon = 0;

    while (gameWon == 0){
        cout << endl;
        player =  turn % 2 + 1;
        if (player == 1){
            piece = "X";
        } else {
            piece = "O";
        }
        displayBoard(board, size);
        cout << endl;
        cout << "PLAYER " << player << " TURN: place an " << piece << "!" << endl;
        askMove(board, size, turn);
        gameWon = winCheck(board, size, turn);
        turn++;
    }
    displayBoard(board, size);

    for (int i = 0; i < 4; i++)
        cout << endl;

    // delete board 2D array if game over
    //boardDeleter(board, size);

    return gameWon;
}

// clears screen & prints instructions
void tictactoe::bootup() {
    for (int i=0; i<25; i++)
        cout << endl;
    cout << "Welcome to P2 - Tic-Tac-Toe: a Silly Little Game by Silly Little Games Inc.!!" << endl << endl;
    cout << "INSTRUCTIONS:" << endl;
    cout << "In this two player game, one player places the X pieces and the other player places the O pieces on a game board." << endl;
    cout << "To place a piece, simply enter the row and column numbers of the blank space on your turn when prompted." << endl;
    cout << "The basic game board is a grid of 9 spaces, in a 3 x 3 arrangement, shown below, but we can play with any square, odd length board! " << endl << endl;
    // example board display (not used)
    string **board = nullptr;
    board = makeBoard(3);
    displayBoard(board, 3);
    cout << endl << "The first player to fill a row, column, or diagonal with only their pieces wins!" << endl << endl;

    string pause;
    cout << "Ready? Insert any key to start: ";
    cin >> pause;

    for (int i = 0; i < 4; i++)
        cout << endl;
}

// displays scoreboard with running statistics
void tictactoe::scoreboard(int player1_wins, int player2_wins, int ties) {
    for (int i = 0; i<4; i++)
        cout << endl;
    cout << " ";
    for (int i = 0; i<59; i++)
        cout << "_";
    cout << endl;
    cout << "|   SCOREBOARD:   |";
    for (int i = 0; i<41; i++)
        cout << " ";
    cout << "|" << std::endl;
    cout << "|_________________|";
    for (int i = 0; i<41; i++)
        cout << " ";
    cout << "|" << std::endl;
    cout << "|";
    for (int i = 0; i<59; i++)
        cout << " ";
    cout << "|" << std::endl << "|";
    for (int i = 0; i<4; i++)
        cout << " ";
    cout << "Player 1 Wins: " << player1_wins; // 15 characters
    for (int i = 0; i<6; i++)
        cout << " ";
    cout << "Player 2 Wins: " << player2_wins; // 15 characters
    for (int i = 0; i<6; i++)
        cout << " ";
    cout << "Ties: " << ties; // 6 characters
    for (int i = 0; i<4; i++)
        cout << " ";
    cout << "|" << endl << "|";
    for (int i = 0; i<59; i++)
        cout << "_";
    cout << "|";
    for (int i = 0; i<4; i++)
        cout << endl;
}

void tictactoe::startSeries() {
    int result  = 0;
    int player1Wins = 0;
    int player2Wins = 0;
    int ties = 0;
    int board_size = -1; // initialized to be invalid & trigger while loop
    bootup();

    string another_game = "Y";

    while (another_game == "Y" || another_game == "y") {
        board_size = -1; // update to be invalid & trigger while loop
        // ask user for board size & check if valid size
        while(3 > board_size || board_size > MAX_BOARDSIZE) {
            cout << "Enter the size board you want to play (3 is standard game): ";
            cin >> board_size;
            if (3 > board_size){
                cout << endl << "Board size must be larger than 3!" << endl;
            } else if (board_size > MAX_BOARDSIZE) {
                cout << endl << "Board size entered is too large! The maximum size is: " << MAX_BOARDSIZE << endl;
            }
        }

        // display to separate games
        for (int i = 0; i < 30; i++)
            cout << "=";
        cout << " NEW GAME ";
        for (int i = 0; i < 30; i++)
            cout << "=";
        for (int x = 0; x < 4; x++)
            cout << endl;

        // play one game of tic-tac-toe; returns 1 if player 1 won, 2 if player 2 won, 3 if tie
        result = playGame(board_size);

        if(result == 1) {
            cout << "PLAYER 1 WINS!!" << endl;
            player1Wins++;
        } else if (result == 2) {
            cout << "PLAYER 2 WINS!!" << endl;
            player2Wins++;
        } else {
            cout << "TIE GAME!!" << endl;
            ties++;
        }

        scoreboard(player1Wins, player2Wins, ties);

        cout << "Play again? Enter `Y` or `y` to play again, any other key to end: ";
        cin >> another_game;

        for (int x = 0; x < 4; x++)
            cout << endl;
    }

    cout << "Thanks for playing!!";
}

// method for deallocating memory of board 2D array
void tictactoe::boardDeleter(std::string **board, int size) {
    for (int row = 0; row < size; row++) {
        delete[] board[row];
    }
    delete[] board;
}