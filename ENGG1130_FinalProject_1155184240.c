/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Nguyen Ba Minh
 * Student ID    : 1155184240
 */

//This project is built as Notakto game - Tic-tac-toe game with 2 gameboards

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

void initGameBoard(int gameBoard[3][3]) {      
    int n = 1;
    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j <= 2; j++) {
            gameBoard[i][j] = n + '0';
            n++;
        }
    }
}

void printGameBoard(int gameBoard[3][3]) {         
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            printf("|%c", gameBoard[i][j]);
        }
        printf("|\n");
    }
}

void printTwoGameBoards(int gameBoard1[3][3], int gameBoard2[3][3]) {     
    printf("\n");
    printf("# Game Board 1 #\n");
    printGameBoard(gameBoard1);
    printf("# Game Board 2 #\n");
    printGameBoard(gameBoard2);
}

int isGameBoardDead(int gameBoard[3][3]){     
    int winner = 0;

    // check rows
    for (int i = 0; i < 3; i++) {
        if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][0]  == gameBoard[i][2])
            winner = 1;
    }

    // check columns
    for (int j = 0; j < 3; j++) {
        if (gameBoard[0][j] == gameBoard[1][j] && gameBoard[0][j] == gameBoard[2][j])
            winner = 1;
    }

    // check diagonals
    if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[0][0] == gameBoard[2][2])
        winner = 1;
    
    if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[0][2] == gameBoard[2][0])
        winner = 1;
    
    return winner;
}

void updateGameBoard(int gameBoard[3][3]) {  
    int cell;
    int row, col;
    printf("Choose the cell:\n");
    
    do {
        scanf("%d", &cell);
        col = (cell-1) % 3;
        row = (cell - col)/3;
        
        if (row == 0) {row += 2;}
        else if (row == 2) {row -= 2;} 

        if (cell < 1 || cell > 9) {
            printf("Input out of range. Please input again:\n");
        }
        else if (gameBoard[row][col] > '9' || gameBoard[row][col] < '1') {
            printf("The chosen cell is occupied. Please input again:\n");
        }
        else {
            gameBoard[row][col] = 'X';
            break;
        }
    } while (1);
}

void placeCrossByHumanPlayer(int gBoard1[3][3], int gBoard2[3][3]) {
    int gb_num;
    printf("Choose the game board:\n");
    while (1) {
        scanf("%d", &gb_num);
        if (gb_num > 2 || gb_num < 1) 
            printf("Input out of range. Please input again:\n");
        else if ( (gb_num == 1 && isGameBoardDead(gBoard1) == 1) || (gb_num == 2 && isGameBoardDead(gBoard2) == 1) ) 
            printf("The chosen game board is dead. Please input again:\n");
        else
            break;
    }

    if (gb_num == 1) {
        updateGameBoard(gBoard1);
    }
    else if (gb_num == 2) {
        updateGameBoard(gBoard2);
    }
}

int countNumOfCrosses(int gameBoard[3][3]) {
    int cross_num = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] == 'X') {
                cross_num++;
            }
        }
    }
    return cross_num;
}

void computer_gameboard1_caseA(int gb[3][3]) {
    int board[9];
    int n = 0;
    printf("Choose the cell:\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[n] = gb[i][j];
            n++;
        }
    }
    for (int x = 0; x < 9; x++) {
        int n; 
        for (int y = x+1; y < 9; y++) {
            if ( (int)(board[x]-'0') >= (int)(board[y]-'0') )
                {n = board[x]; board[x] = board[y]; board[y] = n;}
        }
    }
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            if (gb[a][b] == board[0]) {
                printf("%c\n", gb[a][b]);
                gb[a][b] = 'X';
            }
        }
    }
}

void computer_gameboard2_caseA(int gb[3][3]) {
    int board[9];
    int n = 0;
    printf("Choose the cell:\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[n] = gb[i][j];
            n++;
        }
    }
    for (int x = 0; x < 9; x++) {
        int n; 
        for (int y = x+1; y < 9; y++) {
            if ( (int)(board[x]-'0') >= (int)(board[y]-'0') )
                {n = board[x]; board[x] = board[y]; board[y] = n;}
        }
    }
    int cell = 8 - countNumOfCrosses(gb);
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            if (gb[a][b] == board[cell]) {
                printf("%c\n", gb[a][b]);
                gb[a][b] = 'X';
            }
        }
    }
}

void computer_gameboard1_caseB(int gb[3][3]) {
    printf("Choose the cell:\n");
    int board[9];
    int n = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[n] = gb[i][j];
            n++;
        }
    }
    for (int x = 0; x < 9; x++) {
        int n; 
        for (int y = x+1; y < 9; y++) {
            if ( (int)(board[x]-'0') >= (int)(board[y]-'0') )
                {n = board[x]; board[x] = board[y]; board[y] = n;}
        }
    }

    int count = 0;
    while (1) {
        int flag = 0;
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                if (gb[a][b] == board[count]) {
                    gb[a][b] = 'X';
                    if (isGameBoardDead(gb) == 1 && count < 8 - countNumOfCrosses(gb)) {
                        gb[a][b] = board[count];
                    }
                    else if (isGameBoardDead(gb) == 1 && count == 8 - countNumOfCrosses(gb)) {
                        flag = 1;
                        break;
                    }
                    else if (isGameBoardDead(gb) == 0) {
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if (flag == 1) {
            break;
        }
        count++;
    }
    printf("%c\n", board[count]);
}

void computer_gameboard2_caseB(int gb[3][3]) {
    printf("Choose the cell:\n");
    int board[9];
    int n = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[n] = gb[i][j];
            n++;
        }
    }
    for (int x = 0; x < 9; x++) {
        int n; 
        for (int y = x+1; y < 9; y++) {
            if ( (int)(board[x]-'0') >= (int)(board[y]-'0') )
                {n = board[x]; board[x] = board[y]; board[y] = n;}
        }
    }
    int count = 8;
    while(1) {
        int cell = count - countNumOfCrosses(gb);
        int flag = 0;
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                if (gb[a][b] == board[cell]) {
                    gb[a][b] = 'X';
                    if (isGameBoardDead(gb) == 1 && cell > 0) {
                        gb[a][b] = board[cell];
                    }
                    else if (isGameBoardDead(gb) == 1 && cell == 0) {
                        flag = 1;
                        break;
                    }
                    else if (isGameBoardDead(gb) == 0) {
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if (flag == 1) {
            break;
        }
        count--;
    }
    printf("%c\n", board[count - countNumOfCrosses(gb)+1]);
}

void placeCrossByComputerPlayer(int gb1[3][3], int gb2[3][3]) {
    // Case A
    printf("Choose the game board:\n");

    if (isGameBoardDead(gb1) == 0 && isGameBoardDead(gb2) == 0) {
        if (countNumOfCrosses(gb1) < countNumOfCrosses(gb2)) {
            printf("1\n");
            computer_gameboard1_caseA(gb1);
        }
        else if (countNumOfCrosses(gb1) > countNumOfCrosses(gb2)) {
            printf("2\n");
            computer_gameboard2_caseA(gb2);
        } 
    }
    // Case B
    else if ( (isGameBoardDead(gb1)+isGameBoardDead(gb2)) == 1) {
        if (isGameBoardDead(gb1) == 0) {
            printf("1\n");
            computer_gameboard1_caseB(gb1);
        }
        else if (isGameBoardDead(gb1) == 1) {
            printf("2\n");
            computer_gameboard2_caseB(gb2);
        }
    }
}

int main() {
    int gameEnd = 0;
    int numOfHumanPlayers;
    printf("Enter the number of human players [1-2]:\n");
    scanf("%d", &numOfHumanPlayers);
    while (numOfHumanPlayers != 1 && numOfHumanPlayers != 2) {
        printf("Enter the number of human players [1-2]:\n");
        scanf("%d", &numOfHumanPlayers);
    }
    
    int gameBoard1[3][3], gameBoard2[3][3];
    initGameBoard(gameBoard1);
    initGameBoard(gameBoard2);
    printTwoGameBoards(gameBoard1, gameBoard2);

       //start to play
    
        // 2 players
    if (numOfHumanPlayers == 2) { 
        while (gameEnd != 2){
        //player 1
            printf("# Player 1's turn #\n");
            placeCrossByHumanPlayer(gameBoard1, gameBoard2);
            gameEnd = isGameBoardDead(gameBoard1) + isGameBoardDead(gameBoard2);
            
            if (gameEnd == 2) {
                printTwoGameBoards(gameBoard1, gameBoard2);
                printf("Congratulations! Player 2 wins!\n");
                break;
            }       
            printTwoGameBoards(gameBoard1, gameBoard2);

        //player 2
            printf("# Player 2's turn #\n");
            placeCrossByHumanPlayer(gameBoard1, gameBoard2);
            gameEnd = isGameBoardDead(gameBoard1) + isGameBoardDead(gameBoard2);
            
            if (gameEnd == 2) {
                printTwoGameBoards(gameBoard1, gameBoard2);
                printf("Congratulations! Player 1 wins!\n");
                break;
            }
            printTwoGameBoards(gameBoard1, gameBoard2);
        }
    }

        // Computer VS Human
    else if (numOfHumanPlayers == 1) { 
        while (gameEnd != 2) {
            //player 1
            printf("# Player 1's turn #\n");
            placeCrossByHumanPlayer(gameBoard1, gameBoard2);
            gameEnd = isGameBoardDead(gameBoard1) + isGameBoardDead(gameBoard2);
            
            if (gameEnd == 2) {
                printTwoGameBoards(gameBoard1, gameBoard2);
                printf("Computer wins!\n");
                break;
            }       
            printTwoGameBoards(gameBoard1, gameBoard2);

            //Computer's turn
            printf("# Computer's turn #\n");
            placeCrossByComputerPlayer(gameBoard1, gameBoard2);
            gameEnd = isGameBoardDead(gameBoard1) + isGameBoardDead(gameBoard2);

            if (gameEnd == 2) {
                printTwoGameBoards(gameBoard1, gameBoard2);
                printf("Congratulations! Player 1 wins!\n");
                break;
            }
            printTwoGameBoards(gameBoard1, gameBoard2);
        }
    }

    return 0;
}
