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
        } else if (pieces[from_index[0]][from_index[1]] == KNIGHT) {
            int x, y;

            // Left
            if (x = from_index[1] - 2, y = from_index[0] - 1; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            if (x = from_index[1] - 2, y = from_index[0] + 1; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            // Right
            if (x = from_index[1] + 2, y = from_index[0] - 1; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            if (x = from_index[1] + 2, y = from_index[0] + 1; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            // Up
            if (x = from_index[1] - 1, y = from_index[0] - 2; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            if (x = from_index[1] + 1, y = from_index[0] - 2; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            // Down
            if (x = from_index[1] - 1, y = from_index[0] + 2; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }

            if (x = from_index[1] + 1, y = from_index[0] + 2; colors[y][x] != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(y);
                valid_x.push_back(x);
            }
        } else if (pieces[from_index[0]][from_index[1]] == BISHOP) {
            bool go_up_left = true, go_up_right = true, go_down_left = true, go_down_right = true;
            int i = 1;

            while (go_up_left || go_up_right || go_down_left || go_down_right) {
                color c;
                if (go_up_left) {
                    if (c = colors[from_index[0] - i][from_index[1] - i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] - i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] - i);

                        go_up_left = false;
                    } else {
                        go_up_left = false;
                    }
                }

                if (go_up_right) {
                    if (c = colors[from_index[0] - i][from_index[1] + i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] + i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] + i);

                        go_up_right = false;
                    } else {
                        go_up_right = false;
                    }
                }

                if (go_down_left) {
                    if (c = colors[from_index[0] + i][from_index[1] - i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] - i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] - i);

                        go_down_left = false;
                    } else {
                        go_down_left = false;
                    }
                }

                if (go_down_right) {
                    if (c = colors[from_index[0] + i][from_index[1] + i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] + i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] + i);

                        go_down_right = false;
                    } else {
                        go_down_right = false;
                    }
                }

                i++;
            }
        } else if (pieces[from_index[0]][from_index[1]] == ROOK) {
            bool go_left = true, go_right = true, go_up = true, go_down = true;
            int i = 1;

            while (go_left || go_right || go_up || go_down) {
                color c;

                if (go_left) {
                    if (c = colors[from_index[0]][from_index[1] - i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] - i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] - i);

                        go_left = false;
                    } else {
                        go_left = false;
                    }
                }

                if (go_right) {
                    if (c = colors[from_index[0]][from_index[1] + i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] + i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] + i);

                        go_right = false;
                    } else {
                        go_right = false;
                    }
                }

                if (go_up) {
                    if (c = colors[from_index[0] - i][from_index[1]]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1]);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1]);

                        go_up = false;
                    } else {
                        go_up = false;
                    }
                }

                if (go_down) {
                    if (c = colors[from_index[0] + i][from_index[1]]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1]);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1]);

                        go_down = false;
                    } else {
                        go_down = false;
                    }
                }

                i++;
            }
        } else if (pieces[from_index[0]][from_index[1]] == QUEEN) {
            bool go_left = true, go_right = true, go_up = true, go_down = true,
                 go_up_left = true, go_up_right = true, go_down_left = true, go_down_right = true;
            int i = 1;

            while (go_left || go_right || go_up || go_down || go_up_left 
                   || go_up_right || go_down_left || go_down_right) {
                color c;

                if (go_left) {
                    if (c = colors[from_index[0]][from_index[1] - i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] - i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] - i);

                        go_left = false;
                    } else {
                        go_left = false;
                    }
                }

                if (go_right) {
                    if (c = colors[from_index[0]][from_index[1] + i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] + i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0]);
                        valid_x.push_back(from_index[1] + i);

                        go_right = false;
                    } else {
                        go_right = false;
                    }
                }

                if (go_up) {
                    if (c = colors[from_index[0] - i][from_index[1]]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1]);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1]);

                        go_up = false;
                    } else {
                        go_up = false;
                    }
                }

                if (go_down) {
                    if (c = colors[from_index[0] + i][from_index[1]]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1]);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1]);

                        go_down = false;
                    } else {
                        go_down = false;
                    }
                }

                if (go_up_left) {
                    if (c = colors[from_index[0] - i][from_index[1] - i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] - i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] - i);

                        go_up_left = false;
                    } else {
                        go_up_left = false;
                    }
                }

                if (go_up_right) {
                    if (c = colors[from_index[0] - i][from_index[1] + i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] + i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] - i);
                        valid_x.push_back(from_index[1] + i);

                        go_up_right = false;
                    } else {
                        go_up_right = false;
                    }
                }

                if (go_down_left) {
                    if (c = colors[from_index[0] + i][from_index[1] - i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] - i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] - i);

                        go_down_left = false;
                    } else {
                        go_down_left = false;
                    }
                }

                if (go_down_right) {
                    if (c = colors[from_index[0] + i][from_index[1] + i]; c == NOCOLOR) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] + i);
                    } else if (c != colors[from_index[0]][from_index[1]]) {
                        valid_y.push_back(from_index[0] + i);
                        valid_x.push_back(from_index[1] + i);

                        go_down_right = false;
                    } else {
                        go_down_right = false;
                    }
                }

                i++;
            }
        } else if (pieces[from_index[0]][from_index[1]] == KING) {
            color c;

            if (c = colors[from_index[0]][from_index[1] - 1]; c == NOCOLOR) {
                valid_y.push_back(from_index[0]);
                valid_x.push_back(from_index[1] - 1);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0]);
                valid_x.push_back(from_index[1] - 1);
            }
            
            if (c = colors[from_index[0]][from_index[1] + 1]; c == NOCOLOR) {
                valid_y.push_back(from_index[0]);
                valid_x.push_back(from_index[1] + 1);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0]);
                valid_x.push_back(from_index[1] + 1);
            }
        
            if (c = colors[from_index[0] - 1][from_index[1]]; c == NOCOLOR) {
                valid_y.push_back(from_index[0] - 1);
                valid_x.push_back(from_index[1]);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0] - 1);
                valid_x.push_back(from_index[1]);
            }
        
            if (c = colors[from_index[0] + 1][from_index[1]]; c == NOCOLOR) {
                valid_y.push_back(from_index[0] + 1);
                valid_x.push_back(from_index[1]);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0] + 1);
                valid_x.push_back(from_index[1]);
            }
        
            if (c = colors[from_index[0] - 1][from_index[1] - 1]; c == NOCOLOR) {
                valid_y.push_back(from_index[0] - 1);
                valid_x.push_back(from_index[1] - 1);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0] - 1);
                valid_x.push_back(from_index[1] - 1);
            }
            if (c = colors[from_index[0] - 1][from_index[1] + 1]; c == NOCOLOR) {
                valid_y.push_back(from_index[0] - 1);
                valid_x.push_back(from_index[1] + 1);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0] - 1);
                valid_x.push_back(from_index[1] + 1);
            }
        
            if (c = colors[from_index[0] + 1][from_index[1] - 1]; c == NOCOLOR) {
                valid_y.push_back(from_index[0] + 1);
                valid_x.push_back(from_index[1] - 1);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0] + 1);
                valid_x.push_back(from_index[1] - 1);
            }
            if (c = colors[from_index[0] + 1][from_index[1] + 1]; c == NOCOLOR) {
                valid_y.push_back(from_index[0] + 1);
                valid_x.push_back(from_index[1] + 1);
            } else if (c != colors[from_index[0]][from_index[1]]) {
                valid_y.push_back(from_index[0] + 1);
                valid_x.push_back(from_index[1] + 1);
            }
        }

        for (int i = 0; i < valid_y.size(); i++) {
            if ((valid_y[i] == to_index[0] && valid_x[i] == to_index[1]) &&
                (valid_y[i] >= 0 && valid_y[i] <= 7 && valid_x[i] >= 0 && valid_x[i] <= 7)) {
                return true;
            }
        }

        return false;
    }

    void move_piece(int to_index[2], int from_index[2], color &turn) {
        if (colors[from_index[0]][from_index[1]] != turn) {
            return;
        } else {
            turn = (turn == WHITE) ? BLACK : WHITE;
        }

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
    color turn = WHITE;

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

        cout << " What is " << ((turn == WHITE)? "white's" : "black's") << " move (\"quit\" to quit, input format is \"A2-C3\")? ";
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

            board.move_piece(to_index, from_index, turn);

            system("clear");
        }

        bool white_king_found = false, black_king_found = false;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                color piece_color = board.colors[i][j];
                piece piece_type = board.pieces[i][j];

                if (piece_type == KING) {
                    if (piece_color == WHITE) {
                        white_king_found = true;
                    } else {
                        black_king_found = true;
                    }
                }
            }
        }

        if (!white_king_found) {
            cout << "Black wins!" << endl;
            running = false;
        } else if (!black_king_found) {
            cout << "White wins!" << endl;
            running = false;
        }
    }

    return 0;
}