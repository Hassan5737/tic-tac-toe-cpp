#include <iostream>
using namespace std;

char board[3][3];

// Initialize board
void initializeBoard()
{
    char value = '1';

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = value++;
}

// Display board
void displayBoard()
{
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }

        cout << endl;
        if (i < 2) cout << "---+---+---" << endl;
    }

    cout << endl;
}

// Convert position to row & col
void getPosition(int position, int &row, int &col)
{
    int index = position - 1;
    row = index / 3;
    col = index % 3;
}

// Check if cell is taken
bool isCellTaken(int row, int col)
{
    return (board[row][col] == 'X' || board[row][col] == 'O');
}

// Player move with validation (UPDATED)
void playerMove(char currentPlayer, string currentName)
{
    int position, row, col;

    while (true)
    {
        cout << currentName << " (" << currentPlayer << "), enter position (1-9): ";
        cin >> position;

        if (position < 1 || position > 9)
        {
            cout << "Invalid input. Try again.\n";
            continue;
        }

        getPosition(position, row, col);

        if (isCellTaken(row, col))
        {
            cout << "Cell already taken. Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        break;
    }
}

// Switch player
void switchPlayer(char &currentPlayer)
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Check win
bool checkWin(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }

    return false;
}

int main()
{
    initializeBoard();

    string playerX, playerO;

    cout << "Enter name for Player X: ";
    cin >> playerX;

    cout << "Enter name for Player O: ";
    cin >> playerO;

    char currentPlayer = 'X';
    bool isWin = false;

    for (int i = 0; i < 9; i++)
    {
        displayBoard();

        string currentName = (currentPlayer == 'X') ? playerX : playerO;

        playerMove(currentPlayer, currentName);

        if (checkWin(currentPlayer))
        {
            displayBoard();
            cout << currentName << " wins!\n";
            isWin = true;
            break;
        }

        switchPlayer(currentPlayer);
    }

    if (!isWin)
    {
        displayBoard();
        cout << "It's a draw!\n";
    }

    return 0;
}