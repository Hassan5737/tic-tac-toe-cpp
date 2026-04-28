#include <iostream>
using namespace std;

// Game board
char board[3][3];

// Initialize board with numbers 1 -> 9
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

// Player move
void playerMove(char currentPlayer)
{
    int position;
    cout << "Player " << currentPlayer << ", enter position (1-9): ";
    cin >> position;

    int index = position - 1;
    int row = index / 3;
    int col = index % 3;

    board[row][col] = currentPlayer;
}

int main()
{
    initializeBoard();

    char currentPlayer = 'X';

    displayBoard();

    playerMove(currentPlayer);

    displayBoard();

    return 0;
}