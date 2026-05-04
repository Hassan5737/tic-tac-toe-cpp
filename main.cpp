#include <iostream>
using namespace std;

char board[3][3];

// Colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

// Initialize board
void initializeBoard()
{
    char value = '1';

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = value++;
}

// Display board with colors
void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << "   ";

        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
                cout << GREEN << board[i][j] << RESET;
            else if (board[i][j] == 'O')
                cout << RED << board[i][j] << RESET;
            else
                cout << board[i][j];

            if (j < 2)
                cout << "   |   ";
        }

        cout << "\n";

        if (i < 2)
            cout << "  ---------------------\n";
    }

    cout << "\n";
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

// Player move
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

//  Computer move (simple AI)
void computerMove(char computerPlayer)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!isCellTaken(i, j))
            {
                board[i][j] = computerPlayer;
                cout << "Computer played at position " << (i * 3 + j + 1) << "\n";
                return;
            }
        }
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
    char playAgain;

    do
    {
        initializeBoard();

        cout << "=========================\n";
        cout << "      TIC TAC TOE        \n";
        cout << "=========================\n\n";

        int mode;
        cout << "Choose mode:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Enter choice: ";
        cin >> mode;

        string playerX, playerO;

        cout << "Enter name for Player X: ";
        cin >> playerX;

        if (mode == 1)
        {
            cout << "Enter name for Player O: ";
            cin >> playerO;
        }
        else
        {
            playerO = "Computer";
        }

        char currentPlayer = 'X';
        bool isWin = false;

        for (int i = 0; i < 9; i++)
        {
            displayBoard();

            string currentName = (currentPlayer == 'X') ? playerX : playerO;

            cout << "Turn: " << currentName << " (" << currentPlayer << ")\n";

           
            if (mode == 2 && currentPlayer == 'O')
            {
                computerMove(currentPlayer);
            }
            else
            {
                playerMove(currentPlayer, currentName);
            }

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

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";

    return 0;
}