#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

enum Cell { EMPTY, BLUE, RED };

class HexBoard {
private:
    int size;
    vector<vector<Cell>> board;

public:
    HexBoard(int n) : size(n), board(n, vector<Cell>(n, EMPTY)) {}

    void drawBoard() {
        for (int i = 0; i < size; ++i) {
            cout << string(i * 2, ' ');
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == EMPTY)
                    cout << ".";
                else if (board[i][j] == BLUE)
                    cout << "B";
                else if (board[i][j] == RED)
                    cout << "R";

                if (j != size - 1)
                    cout << " - ";
            }
            cout << endl;
            if (i != size - 1) {
                cout << string(i * 2 + 1, ' ');
                for (int j = 0; j < size; ++j) {
                    cout << "\\ ";
                    if (j != size - 1)
                        cout << "/ ";
                }
                cout << endl;
            }
        }
    }

    bool isLegalMove(int i, int j) {
        return (i >= 0 && i < size && j >= 0 && j < size && board[i][j] == EMPTY);
    }

    void makeMove(int i, int j, Cell player) {
        board[i][j] = player;
    }

    bool hasPlayerWon(Cell player) {
        vector<vector<bool>> visited(size, vector<bool>(size, false));
        queue<pair<int, int>> q;

        if (player == BLUE) {
            for (int i = 0; i < size; ++i) {
                if (board[i][0] == BLUE) {
                    q.push({i, 0});
                    visited[i][0] = true;
                }
            }

            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                if (y == size - 1)
                    return true; // reached east side

                for (auto [nx, ny] : getNeighbors(x, y)) {
                    if (!visited[nx][ny] && board[nx][ny] == BLUE) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        } else { // RED player
            for (int j = 0; j < size; ++j) {
                if (board[0][j] == RED) {
                    q.push({0, j});
                    visited[0][j] = true;
                }
            }

            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                if (x == size - 1)
                    return true; // reached south side

                for (auto [nx, ny] : getNeighbors(x, y)) {
                    if (!visited[nx][ny] && board[nx][ny] == RED) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }

        return false;
    }

    vector<pair<int, int>> getNeighbors(int x, int y) {
        vector<pair<int, int>> neighbors;
        int dx[] = {-1, -1, 0, 0, 1, 1};
        int dy[] = {0, 1, -1, 1, -1, 0};

        for (int d = 0; d < 6; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && ny >= 0 && nx < size && ny < size)
                neighbors.push_back({nx, ny});
        }
        return neighbors;
    }
};

int main() {
    int boardSize;
    cout << "Enter board size (e.g., 7 for 7x7): ";
    cin >> boardSize;

    HexBoard game(boardSize);

    Cell currentPlayer = BLUE;
    int moveCount = 0;
    while (true) {
        game.drawBoard();
        cout << (currentPlayer == BLUE ? "Blue" : "Red") << "'s turn." << endl;

        int x, y;
        cout << "Enter your move (row column): ";
        cin >> x >> y;

        if (!game.isLegalMove(x, y)) {
            cout << "Illegal move, try again!" << endl;
            continue;
        }

        game.makeMove(x, y, currentPlayer);
        moveCount++;

        if (game.hasPlayerWon(currentPlayer)) {
            game.drawBoard();
            cout << (currentPlayer == BLUE ? "Blue" : "Red") << " wins!" << endl;
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == BLUE) ? RED : BLUE;
    }

    return 0;
}
