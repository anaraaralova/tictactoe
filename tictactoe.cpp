#include <iostream>
#include <string>

using namespace std;

// Function declarations
void drawBoard(const char board[3][3]);
bool makeMove(char board[3][3], int slot, char playerSymbol);
bool checkWin(const char board[3][3], char playerSymbol);
bool checkDraw(const char board[3][3]);

int main() {
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X';
    bool gameOver = false;
    int choice;

    cout << "===========================\n";
    cout << "   Welcome to Tic-Tac-Toe  \n";
    cout << "===========================\n\n";

    while (!gameOver) {
        drawBoard(board);
        
        cout << "Player " << (currentPlayer == 'X' ? "1 (X)" : "2 (O)") << ", enter a slot (1-9): ";
        
        // Input validation for non-numeric entries
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 1 and 9.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // Attempt to process the move
        if (!makeMove(board, choice, currentPlayer)) {
            cout << "Invalid move! Slot is either out of bounds or already taken. Try again.\n\n";
            continue;
        }

        // Check state conditions
        if (checkWin(board, currentPlayer)) {
            drawBoard(board);
            cout << "Congratulations! Player " << (currentPlayer == 'X' ? "1 (X)" : "2 (O)") << " wins!\n";
            gameOver = true;
        } else if (checkDraw(board)) {
            drawBoard(board);
            cout << "It's a draw!\n";
            gameOver = true;
        } else {
            // Alternate player turn
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            cout << "\n";
        }
    }

    return 0;
}

// Renders the current 3x3 game board grid
void drawBoard(const char board[3][3]) {
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  \n";
    cout << "     |     |     \n\n";
}

// Maps the slot selection (1-9) to 2D indices and places the marker
bool makeMove(char board[3][3], int slot, char playerSymbol) {
    if (slot < 1 || slot > 9) return false;

    // Convert 1-9 to row and column index
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    // Verify if the slot is still un-marked
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = playerSymbol;
        return true;
    }

    return false;
}

// Validates all 8 winning combinations (rows, columns, diagonals)
bool checkWin(const char board[3][3], char playerSymbol) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) return true;
        if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol) return true;
    }
    // Check diagonals
    if (board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) return true;
    if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol) return true;

    return false;
}

// Verifies if the board is entirely full without a winner
bool checkDraw(const char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // Found an open slot, not a draw yet
            }
        }
    }
    return true;
}
