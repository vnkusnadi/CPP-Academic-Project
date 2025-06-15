// === Region: Project Declaration ===
//
//  COMP2011 Fall 2024
//  PA2: MineSweeper-Game-With-Recursion
//
//  Your name: KUSNADI, Vicko Nicholas
//  Your ITSC email: vnkusnadi@connect.ust.hk
//
//  Possible usage of the program:
//
//  Method 1: You can display the output on the terminal
//
//  Mac/Linux: ./pa2 < testcase/inputX.txt
//  Windows  :  Get-Content testcase/inputX.txt | ./pa2
//
//  Method 2: You can redirect the output to a text file, and then open the text file for checking
//
//  Mac/Linux: ./pa2 < testcase/inputX.txt > myOutputX.txt
//  Winodws  :  Get-Content testcase/inputX.txt | ./pa2 > myOutputX.txt
//
// =====================================
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_ROWS = 20;
const int MAX_COLS = 30;

const char CELL_EMPTY = '.';
const char CELL_MINE = '*';
const char CELL_EMPTY_EXPLORED = ' ';

enum GameOptionType
{
    GAME_OPTION_EXIT = 0,
    GAME_OPTION_LOAD_INPUT,
    GAME_OPTION_MAKE_MOVE,
    MAX_GAME_OPTION
};
const char* GAME_OPITION_TEXT[] = {
    "Exit the Game",
    "Load mine map",
    "Make a move" };


bool isValidRowCol(int row, int col, int numRows, int numCols)
{
    return (row >= 0) && (row < numRows) && (col >= 0) && (col < numCols);
}


void displayGameOptionMenu()
{
    int maxGameOption = int(MAX_GAME_OPTION);
    cout << "== Game Menu ==" << endl;
    for (int i = 0; i < maxGameOption; i++)
    {
        cout << i << ": " << GAME_OPITION_TEXT[i] << endl;
    }
}


// Implement fillMapUsingRecursion
// This function fills in a 2D array with the input character in a given range using recursion
// Note: used recursion to implement this function
//
// @param map: The 2D array storing the map information
// @param startRow: The start row index
// @param startCol: The start column index
// @param endRow: The end row index
// @param endCol: The end column index
// @param initChar: The character to fill the 2D array
void fillMapUsingRecursion(char map[MAX_ROWS][MAX_COLS], int startRow, int startCol, int endRow, int endCol, char initChar)
{
    if (startRow > endRow)return;
    if (startCol > endCol) {
        startRow = startRow + 1;
        startCol = 0;
    }
    map[startRow][startCol] = initChar;
    fillMapUsingRecursion(map, startRow, startCol + 1, endRow, endCol, initChar);

}

// Implement countCharFromMapUsingRecursion
// This function counts the number of characters in a 2D array in a given range using recursion
// Note: used recursion to implement this function
//
// @param map: The 2D array storing the map information
// @param startRow: The start row index
// @param startCol: The start column index
// @param endRow: The end row index
// @param endCol: The end column index
// @param ch: The character to be counted from the 2D array
int countCharFromMapUsingRecursion(const char map[MAX_ROWS][MAX_COLS], int startRow, int startCol, int endRow, int endCol, char ch)
{
    int count = 0;
    if (startRow > endRow) {
        return count;
    }
    if (startCol > endCol) {
        return countCharFromMapUsingRecursion(map, startRow + 1, 0, endRow, endCol, ch);
    }

    if (map[startRow][startCol] == ch) {
        return count = countCharFromMapUsingRecursion(map, startRow, startCol + 1, endRow, endCol, ch) + 1;
    }
    else {
        return count = countCharFromMapUsingRecursion(map, startRow, startCol + 1, endRow, endCol, ch) + 0;
    }
}

// TODO: Implement countCharFromMapUsingRecursion
// This function explores (i.e., updates) the current map
// Note: used recursion to implement this function
//
// @param realMap: The 2D array storing the real map information
// @param currentMap: The 2D array storing the current map (i.e., the exploring map) information
// @param numRows: The number of rows for the maps (both maps have the same size)
// @param numCols: The number of columns for the maps (both maps have the same size)
// @param row: The row index to explore
// @param col: The col index to explore

// Helper function
int count_surroundings(const char realMap[MAX_ROWS][MAX_COLS], int row, int col, int numRows, int numCols) {
    // count mines from sides
    int count = 0;
    // case 1: normal (max 8)
    if ((row > 0 && col > 0) && (row < numRows - 1 && col < numCols - 1)) {
        count =
            countCharFromMapUsingRecursion(realMap, row - 1, col - 1, row - 1, col + 1, '*') +
            countCharFromMapUsingRecursion(realMap, row, col - 1, row, col + 1, '*') +
            countCharFromMapUsingRecursion(realMap, row + 1, col - 1, row + 1, col + 1, '*');
    }
    // case 2: first and last row (max 5)
    else if (((row == 0) && col > 0 && col < numCols - 1)) {
        count = countCharFromMapUsingRecursion(realMap, row, col - 1, row, col + 1, '*') +
            countCharFromMapUsingRecursion(realMap, row + 1, col - 1, row + 1, col + 1, '*');
    }
    else if (((row == numRows - 1) && col > 0 && col < numCols - 1)) {
        count = countCharFromMapUsingRecursion(realMap, row, col - 1, row, col + 1, '*') +
            countCharFromMapUsingRecursion(realMap, row - 1, col - 1, row - 1, col + 1, '*');
    }
    //  case 3: first and last column (max 5)
    else if (((col == 0) && row > 0 && row < numRows - 1)) {
        count =
            countCharFromMapUsingRecursion(realMap, row - 1, col, row - 1, col + 1, '*') +
            countCharFromMapUsingRecursion(realMap, row, col, row, col + 1, '*') +
            countCharFromMapUsingRecursion(realMap, row + 1, col, row + 1, col + 1, '*');
    }
    else if (((col == numCols - 1) && row > 0 && row < numRows - 1)) {
        count =
            countCharFromMapUsingRecursion(realMap, row - 1, col - 1, row - 1, col, '*') +
            countCharFromMapUsingRecursion(realMap, row, col - 1, row, col, '*') +
            countCharFromMapUsingRecursion(realMap, row + 1, col - 1, row + 1, col, '*');
    }
    //  case 4: edges (max 3)
    else {
        if ((row == 0 && col == 0)) {
            count = countCharFromMapUsingRecursion(realMap, row, col, row, col + 1, '*') +
                countCharFromMapUsingRecursion(realMap, row + 1, col, row + 1, col + 1, '*');
        }
        else if ((row == 0 && col == numCols - 1)) {
            count = countCharFromMapUsingRecursion(realMap, row, col - 1, row, col, '*') +
                countCharFromMapUsingRecursion(realMap, row + 1, col - 1, row + 1, col, '*');
        }
        else if ((row == numRows - 1 && col == 0)) {
            count = countCharFromMapUsingRecursion(realMap, row - 1, col, row - 1, col + 1, '*') +
                countCharFromMapUsingRecursion(realMap, row, col, row, col + 1, '*');
        }
        else if ((row == numRows - 1 && col == numCols - 1)) {
            count = countCharFromMapUsingRecursion(realMap, row - 1, col - 1, row - 1, col, '*') +
                countCharFromMapUsingRecursion(realMap, row, col - 1, row, col, '*');
        }
    }
    return count;
}


void exploreMapUsingRecursion(const char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
    int numRows, int numCols, int row, int col)
{
    // check row and col validity
    if (!isValidRowCol(row, col, numRows, numCols) || currentMap[row][col] != CELL_EMPTY) {
        return;
    }

    // count surroundings
    int count = 0;
    if (currentMap[row][col] == '*') {
        currentMap[row][col] = '.';
    }
    else {
        count = count_surroundings(realMap, row, col, numRows, numCols);
        switch (count) {
        case 0: currentMap[row][col] = ' ';break;
        case 1: currentMap[row][col] = '1';break;
        case 2: currentMap[row][col] = '2';break;
        case 3: currentMap[row][col] = '3';break;
        case 4: currentMap[row][col] = '4';break;
        case 5: currentMap[row][col] = '5';break;
        case 6: currentMap[row][col] = '6';break;
        case 7: currentMap[row][col] = '7';break;
        case 8: currentMap[row][col] = '8';break;
            // when self count as bomb
        default: currentMap[row][col] = ' '; break;
        }
    }

    // explore map
    if (currentMap[row][col] == ' ') {
        if (isValidRowCol(row - 1, col - 1, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row - 1, col - 1); }
        if (isValidRowCol(row - 1, col, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row - 1, col); }
        if (isValidRowCol(row - 1, col + 1, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row - 1, col + 1); }
        if (isValidRowCol(row, col - 1, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row, col - 1); }
        if (isValidRowCol(row, col + 1, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row, col + 1); }
        if (isValidRowCol(row + 1, col - 1, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row + 1, col - 1); }
        if (isValidRowCol(row + 1, col, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row + 1, col); }
        if (isValidRowCol(row + 1, col + 1, numRows, numCols)) { exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row + 1, col + 1); }
    }
    else {
        return;
    }
}




void displayMap(char map[MAX_ROWS][MAX_COLS], int numRows, int numCols)
{
    int r, c;

    // display column numbers
    cout << "  ";
    for (c = 0; c < numCols; c++)
        cout << c % 10 << " ";
    cout << endl;

    // display map and row numbers (on the left)
    for (r = 0; r < numRows; r++)
    {
        cout << r % 10 << " ";
        for (c = 0; c < numCols; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}

void handleLoadMap(char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
    int& numRows, int& numCols)
{

    char filename[100];
    int r, c;

    cout << "Enter the map file name: ";
    cin >> filename;
    fstream fin(filename);
    fin >> numRows >> numCols;

    // Fill both the realMap and currentMap as CELL_EMPTY
    fillMapUsingRecursion(realMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);
    fillMapUsingRecursion(currentMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);

    fin.ignore(); // ignore and move to the next line, start to read the map characters

    for (r = 0; r < numRows; r++)
    {
        for (c = 0; c < numCols; c++)
        {
            fin >> realMap[r][c];
        }
    }
    fin.close();
}



bool handleMakeMove(char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
    int numRows, int numCols)
{
    int row, col;

    cout << "Enter your move (row column): ";
    cin >> row >> col;

    if (!isValidRowCol(row, col, numRows, numCols))
    {
        cout << "Error: Invalid row/column: " << row << " " << col << endl;
        return false;
    }

    if (realMap[row][col] == CELL_MINE)
    {
        cout << "Game over: hit a mine at row/column: " << row << " " << col << endl;
        return true;
    }

    if (currentMap[row][col] != CELL_EMPTY)
    {
        cout << "Error: The cell row/column is explored: " << row << " " << col << endl;
        return false;
    }

    exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row, col);
    cout << "Success: Explore the current map at row/column: " << row << " " << col << endl;
    cout << "The current map: " << endl;
    displayMap(currentMap, numRows, numCols);
    return false;
}

bool checkGameWin(char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
    int numRows, int numCols)
{
    // count the number of mines from the real map
    int countMines = countCharFromMapUsingRecursion(realMap, 0, 0, numRows - 1, numCols - 1, CELL_MINE);

    // count the number of empty cells in the current map
    int countEmpty = countCharFromMapUsingRecursion(currentMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);

    cout << "The total number of mines in the real map is: " << countMines << endl;
    cout << "The total number of empty cells in the current map is: " << countEmpty << endl;

    // End the game if both numbers are equal
    return countMines == countEmpty;
}

int main()
{

    int inputOption;
    GameOptionType gameOption;
    bool gameFinish = false;
    char realMap[MAX_ROWS][MAX_COLS];
    char currentMap[MAX_ROWS][MAX_COLS];
    int numRows, numCols;

    numRows = numCols = 0;

    while (!gameFinish)
    {
        displayGameOptionMenu();
        cout << "Enter your option: ";
        cin >> inputOption;
        gameOption = GameOptionType(inputOption);
        switch (gameOption)
        {
        case GAME_OPTION_EXIT:
            gameFinish = true;
            break;
        case GAME_OPTION_LOAD_INPUT:
            handleLoadMap(realMap, currentMap, numRows, numCols);
            cout << "The real map: " << endl;
            displayMap(realMap, numRows, numCols);
            cout << "The current map: " << endl;
            displayMap(currentMap, numRows, numCols);
            break;
        case GAME_OPTION_MAKE_MOVE:
            gameFinish = handleMakeMove(realMap, currentMap, numRows, numCols);
            if (!gameFinish)
            {
                if (checkGameWin(realMap, currentMap, numRows, numCols))
                {
                    cout << "Game finished! All non-mine cells are explored!" << endl;
                    gameFinish = true;
                }
            }
            break;
        default:
            cout << "Unsupported option: " << inputOption << endl;
        }
    }

    return 0;
}
