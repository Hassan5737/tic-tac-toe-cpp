#include <iostream>
#include <algorithm>
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

// Display board
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

// Convert position
void getPosition(int position, int &row, int &col)
{
    int index = position - 1;
    row = index / 3;
    col = index % 3;
}

bool isCellTaken(int row, int col)
{
    return (board[row][col] == 'X' || board[row][col] == 'O');
}

// 🧠 Evaluate board
int evaluate()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'O') return 10;
            if (board[i][0] == 'X') return -10;
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == 'O') return 10;
            if (board[0][i] == 'X') return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'O') return 10;
        if (board[0][0] == 'X') return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'O') return 10;
        if (board[0][2] == 'X') return -10;
    }

    return 0;
}

bool isMovesLeft()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!isCellTaken(i, j))
                return true;

    return false;
}

// 🤯 Minimax
int minimax(bool isMax)
{
    int score = evaluate();

    if (score == 10 || score == -10)
        return score;

    if (!isMovesLeft())
        return 0;

    if (isMax)
    {
        int best = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (!isCellTaken(i, j))
                {
                    char temp = board[i][j];
                    board[i][j] = 'O';

                    best = max(best, minimax(false));

                    board[i][j] = temp;
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (!isCellTaken(i, j))
                {
                    char temp = board[i][j];
                    board[i][j] = 'X';

                    best = min(best, minimax(true));

                    board[i][j] = temp;
                }
            }
        }
        return best;
    }
}

// 🤖 Smart AI
void computerMove(char computerPlayer)
{
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!isCellTaken(i, j))
            {
                char temp = board[i][j];
                board[i][j] = 'O';

                int moveVal = minimax(false);

                board[i][j] = temp;

                if (moveVal > bestVal)
                {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestRow][bestCol] = computerPlayer;
    cout << "Computer played at position " << (bestRow * 3 + bestCol + 1) << "\n";
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

void switchPlayer(char &currentPlayer)
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool checkWin(char player)
{
    return evaluate() == (player == 'O' ? 10 : -10);
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
        cout << "1. Player vs Player\n2. Player vs Computer\nChoose: ";
        cin >> mode;

        string playerX, playerO;

        cout << "Enter name for Player X: ";
        cin >> playerX;

        playerO = (mode == 1) ? "PlayerO" : "Computer";

        char currentPlayer = 'X';
        bool isWin = false;

        for (int i = 0; i < 9; i++)
        {
            displayBoard();

            string currentName = (currentPlayer == 'X') ? playerX : playerO;

            cout << "Turn: " << currentName << " (" << currentPlayer << ")\n";

            if (mode == 2 && currentPlayer == 'O')
                computerMove(currentPlayer);
            else
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

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
}