#include <iostream>
using namespace std;


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

bool checkWin(char currentPlayer)
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
        {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
    {
        return true;
    }

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
    {
        return true;
    }

    return false;
}

int main()
{
    initializeBoard();

    char currentPlayer = 'X';
    bool isWin = false;

    for (int i = 0; i < 9; i++)
    {
        displayBoard();
        playerMove(currentPlayer);

        if (checkWin(currentPlayer))
        {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!" << endl;
            isWin = true;
            break;
        }

        switchPlayer(currentPlayer);
    }

    if (!isWin)
    {
        displayBoard();
        cout << "It's a draw!" << endl;
    }

    return 0;
}