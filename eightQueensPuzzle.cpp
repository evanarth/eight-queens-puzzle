/*
 *  8 queens puzzle - March 13, 2015
 *  
 *  fits 8 queens on a chessboard using recursive approach
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>

//------------------------------------------------------------------------------
// initialize data structures

// location on the board
struct boardLoc {
    int r, c; // row and column
};

// allow these locations to be added
static boardLoc operator+ (const boardLoc& a, const boardLoc& b) {
    boardLoc output;
    output.r = a.r + b.r;
    output.c = a.c + b.c;
    return output;
};

// store where successful queen placements have been
int numQueenLoc, numRows = 8, numSolutions = 0;
boardLoc queenLoc [8];

//------------------------------------------------------------------------------
// basic functions of system

// check if this placement of the queen is valid
bool isMoveValid (boardLoc newMove) {
    
    if ( newMove.r < 0 || newMove.r > 7 || newMove.c < 0 || newMove.c > 7 )
        return false; // this spot is outside the board
    
    // check every other queen: on same column, row, or diagonal?
    for ( int i = 0; i < numQueenLoc; i++ ) {
        boardLoc thisQueen = queenLoc[i];
        
        if ( thisQueen.r == newMove.r || thisQueen.c == newMove.c )
            return false; // shares a row or column with a queen
        else if ( abs(thisQueen.r - newMove.r) == abs(thisQueen.c - newMove.c) )
            return false; // shares a diagonal with a queen
    }
    return true; // this spot is fine!
}

// print locations of queens
void printQueenLoc (void) {
    
    // make a blank board
    char allQueenLoc[8][8];
    for ( int i = 0; i < 8; i++ )
        for ( int j = 0; j < 8; j++ )
            allQueenLoc[i][j] = '0';
    
    // add in all the queen locations
    for ( int i = 0; i < numQueenLoc; i++ )
        allQueenLoc[queenLoc[i].r][queenLoc[i].c] = 'x';
    
    // print the board
    numSolutions++;
    printf("\n %d queens - solution %d\n", numQueenLoc, numSolutions);
    for ( int i = 0; i < numQueenLoc; i++ )
        printf("%d  %d\n", queenLoc[i].r, queenLoc[i].c);
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ )
            printf("%c  ", allQueenLoc[i][j]);
        printf("\n");
    }
    printf("\n");
}

//------------------------------------------------------------------------------
// the core recursive addition of queens

// recursive adding queens
void addQueens ( int newCol ) {
    
    boardLoc newMove;
    newMove.c = newCol;
    
    for ( int i = 0; i < numRows; i++ ) {
        newMove.r = i;
        if ( isMoveValid(newMove) ) {
            queenLoc[numQueenLoc] = newMove;
            numQueenLoc++;
            
            if ( numQueenLoc == 8 )
                printQueenLoc();
            else
                addQueens( newCol+1 );
            
            numQueenLoc--;
        }
    }
}


//==============================================================================
int main( ) { // run the program
//==============================================================================
    
    // just do all solutions exhaustively (only 92 possible!)
    numQueenLoc = 0;
    int newCol = 0;
    boardLoc newMove;
    newMove.c = newCol;
    
    for ( int i = 0; i < numRows; i++ ) {
        newMove.r = i;
        
        // first move must be vaild, so it doesn't need checking before recording it
        queenLoc[numQueenLoc] = newMove;
        numQueenLoc++;
        
        addQueens( newCol+1 );
        
        numQueenLoc--;
    }
    
    
//    // since all solutions can be symmetric through the middle, only add queens
//    // for rows 0, 1, 2, 3
//    for ( int i = 0; i < numRows/2; i++ ) {
//        boardLoc newMove;
//        newMove.r = i;
//        newMove.c = 0;
//        
//        // first move must be vaild, so it doesn't need checking before recording it
//        queenLoc[0] = newMove;
//        numQueenLoc = 1;
//        
//        addQueens( 1 );
//    }
    
    return 0;
}



