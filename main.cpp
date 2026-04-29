#include <iostream>
using namespace std;

// Game board
char board[3][3];

// Initialize board
void initializeBoard()
{
    char value = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = value;
            value++;
        }
    }
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

            if (j < 2)
                cout << "|";
        }

        cout << endl;

        if (i < 2)
            cout << "---+---+---" << endl;
    }

    cout << endl;
}

// Player move with validation
void playerMove(char currentPlayer)
{
    int position;

    while (true)
    {
        cout << "Player " << currentPlayer << ", enter position (1-9): ";
        cin >> position;

        if (position < 1 || position > 9)
        {
            cout << "Invalid input. Try again.\n";
            continue;
        }

        int index = position - 1;
        int row = index / 3;
        int col = index % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O')
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
    if (currentPlayer == 'X')
        currentPlayer = 'O';
    else
        currentPlayer = 'X';
}

int main()
{
    initializeBoard();

    char currentPlayer = 'X';

    // Game loop (9 moves max)
    for (int i = 0; i < 9; i++)
    {
        displayBoard();
        playerMove(currentPlayer);
        switchPlayer(currentPlayer);
    }

    displayBoard();

    cout << "Game Over!" << endl;

    return 0;
}