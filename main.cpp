#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

enum piece {
    NOPIECE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum color {
    NOCOLOR = -1, BLACK, WHITE
};

struct Board {
    piece pieces[8][8] = {
        {ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK},
        {PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
        {},
        {},
        {},
        {},
        {PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
        {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK}
    };

    color colors[8][8] = {
        {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
        {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
        {NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR},
        {NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR},
        {NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR},
        {NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR},
        {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE},
        {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE}
    };

    bool check_piece(int to_index[2], int from_index[2]) {
        vector<int> valid_y;
        vector<int> valid_x;

        // Pawn
        if (pieces[from_index[0]][from_index[1]] == PAWN) {
            // White pawn
            if (colors[from_index[0]][from_index[1]] == WHITE) {
                // Starting move
                if (from_index[0] == 6) {
                    // Able to move two spaces
                    if (pieces[to_index[0]][from_index[1]] == NOPIECE && pieces[to_index[0] + 1][from_index[1]] == NOPIECE) {
                        valid_y.push_back(4);
                        valid_x.push_back(from_index[1]);
                    }
                }

                // Always check this
                if (pieces[to_index[0]][from_index[1]] == NOPIECE) {
                    valid_y.push_back(from_index[0] - 1);
                    valid_x.push_back(from_index[1]);
                }

                // Taking pieces
                if (colors[from_index[0] - 1][from_index[1] - 1] == BLACK) {
                    valid_y.push_back(from_index[0] - 1);
                    valid_x.push_back(from_index[1] - 1);
                }

                if (colors[from_index[0] - 1][from_index[1] + 1] == BLACK) {
                    valid_y.push_back(from_index[0] - 1);
                    valid_x.push_back(from_index[1] + 1);
                }
            // Black pawn
            } else {
                // Starting move
                if (from_index[0] == 1) {
                    if (pieces[to_index[0]][from_index[1]] == NOPIECE && pieces[to_index[0] - 1][from_index[1]] == NOPIECE) {
                        valid_y.push_back(3);
                        valid_x.push_back(from_index[1]);
                    }
                }

                if (pieces[to_index[0]][from_index[1]] == NOPIECE) {
                    valid_y.push_back(from_index[0] + 1);
                    valid_x.push_back(from_index[1]);
                }

                // Taking pieces
                if (colors[from_index[0] + 1][from_index[1] - 1] == WHITE) {
                    valid_y.push_back(from_index[0] + 1);
                    valid_x.push_back(from_index[1] - 1);
                }

                if (colors[from_index[0] + 1][from_index[1] + 1] == WHITE) {
                    valid_y.push_back(from_index[0] + 1);
                    valid_x.push_back(from_index[1] + 1);
                }
            }
        }

        for (int i = 0; i < valid_y.size(); i++) {
            if (valid_y[i] == to_index[0] && valid_x[i] == to_index[1]) {
                return true;
            }
        }

        return false;
    }

    void move_piece(int to_index[2], int from_index[2]) {
        if (check_piece(to_index, from_index)) {
            pieces[to_index[0]][to_index[1]] = pieces[from_index[0]][from_index[1]];
            pieces[from_index[0]][from_index[1]] = NOPIECE;

            colors[to_index[0]][to_index[1]] = colors[from_index[0]][from_index[1]];
            colors[from_index[0]][from_index[1]] = NOCOLOR;
        }
    }

    string get_piece(int y, int x) {
        string output;

        if (colors[y][x] == WHITE) {
            if (pieces[y][x] == PAWN) {
                output = "wP";
            } else if (pieces[y][x] == KNIGHT) {
                output = "wH";
            } else if (pieces[y][x] == BISHOP) {
                output = "wB";
            } else if (pieces[y][x] == ROOK) {
                output = "wR";
            } else if (pieces[y][x] == QUEEN) {
                output = "wQ";
            } else if (pieces[y][x] == KING) {
                output = "wK";
            }
        } else if (colors[y][x] == BLACK) {
            if (pieces[y][x] == PAWN) {
                output = "bP";
            } else if (pieces[y][x] == KNIGHT) {
                output = "bH";
            } else if (pieces[y][x] == BISHOP) {
                output = "bB";
            } else if (pieces[y][x] == ROOK) {
                output = "bR";
            } else if (pieces[y][x] == QUEEN) {
                output = "bQ";
            } else if (pieces[y][x] == KING) {
                output = "bK";
            }
        } else {
            output = "--";
        }

        return output;
    }
};

int main() {
    bool running = true;

    Board board;

    char chars[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    while (running) {
        string input;

        for (int i = 0; i < 8; i++) {
            cout << i << " ";

            for (int j = 0; j < 8; j++) {
                string output = board.get_piece(i, j);

                cout << " " << output;
            }
            cout << endl;
        }

        cout << "   A  B  C  D  E  F  G  H" << endl << endl;

        cout << " What is your move (\"quit\" to quit, input format is \"A2-C3\")? ";
        cin >> input;

        if (input == "quit") {
            running = false;
        } else {
            // Movement
            int from_index[2] = {-1, -1};
            int to_index[2] = {-1, -1};

            for (int i = 0; i < 8; i++) {
                if (chars[i] == input[0]) {
                    from_index[1] = i;
                }

                if (chars[i] == input[3]) {
                    to_index[1] = i;
                }
            }

            from_index[0] = input[1] - '0';
            to_index[0] = input[4] - '0';

            piece from_piece = board.pieces[from_index[0]][from_index[1]];

            board.move_piece(to_index, from_index);

            system("clear");
        }

    }

    return 0;
}