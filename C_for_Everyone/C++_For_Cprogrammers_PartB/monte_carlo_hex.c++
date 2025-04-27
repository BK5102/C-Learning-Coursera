#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

enum Cell { EMPTY, BLUE, RED };

class HexBoard {
public:
    int size;
    vector<vector<Cell>> board;

    HexBoard(int n) : size(n), board(n, vector<Cell>(n, EMPTY)) {}

    void drawBoard() const {
        for (int i = 0; i < size; ++i) {
            cout << string(i * 2, ' ');
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == EMPTY)
                    cout << ".";
                else if (board[i][j] == BLUE)
                    cout << "B";
                else
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

    bool isLegalMove(int i, int j) const {
        return (i >= 0 && i < size && j >= 0 && j < size && board[i][j] == EMPTY);
    }

    void makeMove(int i, int j, Cell player) {
        board[i][j] = player;
    }

    bool hasPlayerWon(Cell player) const {
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
                    return true;

                for (auto [nx, ny] : getNeighbors(x, y)) {
                    if (!visited[nx][ny] && board[nx][ny] == BLUE) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        } else {
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
                    return true;

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

    vector<pair<int, int>> getLegalMoves() const {
        vector<pair<int, int>> moves;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (board[i][j] == EMPTY)
                    moves.push_back({i, j});
        return moves;
    }

    vector<pair<int, int>> getNeighbors(int x, int y) const {
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

class MonteCarloAI {
private:
    Cell aiPlayer;
    Cell humanPlayer;
    mt19937 rng;

public:
    MonteCarloAI(Cell aiColor) : aiPlayer(aiColor), humanPlayer(aiColor == BLUE ? RED : BLUE) {
        rng.seed(chrono::steady_clock::now().time_since_epoch().count());
    }

    pair<int, int> getBestMove(HexBoard board, int simulationsPerMove = 1000) {
        vector<pair<int, int>> legalMoves = board.getLegalMoves();
        pair<int, int> bestMove = legalMoves[0];
        double bestWinRate = -1.0;

        for (auto [x, y] : legalMoves) {
            int wins = 0;

            for (int sim = 0; sim < simulationsPerMove; ++sim) {
                HexBoard tempBoard = board;
                tempBoard.makeMove(x, y, aiPlayer);

                vector<pair<int, int>> movesLeft = tempBoard.getLegalMoves();
                shuffle(movesLeft.begin(), movesLeft.end(), rng);

                Cell currentPlayer = humanPlayer;
                for (auto [nx, ny] : movesLeft) {
                    tempBoard.makeMove(nx, ny, currentPlayer);
                    currentPlayer = (currentPlayer == BLUE) ? RED : BLUE;
                }

                if (tempBoard.hasPlayerWon(aiPlayer))
                    wins++;
            }

            double winRate = static_cast<double>(wins) / simulationsPerMove;
            if (winRate > bestWinRate) {
                bestWinRate = winRate;
                bestMove = {x, y};
            }
        }

        return bestMove;
    }
};

int main() {
    int boardSize = 11;
    HexBoard game(boardSize);

    string playerColor;
    cout << "Choose your color (B for Blue, R for Red): ";
    cin >> playerColor;
    Cell human = (playerColor == "B" || playerColor == "b") ? BLUE : RED;
    Cell ai = (human == BLUE) ? RED : BLUE;

    MonteCarloAI aiPlayer(ai);
    Cell currentPlayer = BLUE;

    while (true) {
        game.drawBoard();

        if (currentPlayer == human) {
            int x, y;
            cout << "Your move (row column): ";
            cin >> x >> y;

            if (!game.isLegalMove(x, y)) {
                cout << "Illegal move, try again!" << endl;
                continue;
            }

            game.makeMove(x, y, human);
        } else {
            cout << "AI is thinking..." << endl;
            auto [x, y] = aiPlayer.getBestMove(game, 500); // use 500 or 1000 trials depending on speed
            game.makeMove(x, y, ai);
            cout << "AI moves at (" << x << ", " << y << ")" << endl;
        }

        if (game.hasPlayerWon(human)) {
            game.drawBoard();
            cout << "You win!" << endl;
            break;
        } else if (game.hasPlayerWon(ai)) {
            game.drawBoard();
            cout << "AI wins!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == BLUE) ? RED : BLUE;
    }

    return 0;
}
