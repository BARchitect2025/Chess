#include <iostream>
#include <string.h>

using namespace std;

enum piece {NOPIECE, WPAWN, WKNIGHT, WBISHOP, WROOK, WQUEEN, WKING,
            BPAWN = 10, BKNIGHT, BBISHOP, BROOK, BQUEEN, BKING};

int main() {
    bool running = true;

    piece Board[8][8] = {
        {BROOK, BKNIGHT, BBISHOP, BKING, BQUEEN, BBISHOP, BKNIGHT, BROOK},
        {BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN},
        {},
        {},
        {},
        {},
        {WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN},
        {WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK}
    };

    char chars[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    while (running) {
        string input;

        for (int i = 0; i < 8; i++) {
            cout << i << " ";

            for (int j = 0; j < 8; j++) {
                char output[3];

                switch (Board[i][j]) {
                    // No Piece
                    case NOPIECE: strcpy(output, "--"); break;

                    // White
                    case WPAWN: strcpy(output, "wP"); break;
                    case WKNIGHT: strcpy(output, "wH"); break;
                    case WBISHOP: strcpy(output, "wB"); break;
                    case WROOK: strcpy(output, "wR"); break;
                    case WQUEEN: strcpy(output, "wQ"); break;
                    case WKING: strcpy(output, "wK"); break;

                    // Black
                    case BPAWN: strcpy(output, "bP"); break;
                    case BKNIGHT: strcpy(output, "bH"); break;
                    case BBISHOP: strcpy(output, "bB"); break;
                    case BROOK: strcpy(output, "bR"); break;
                    case BQUEEN: strcpy(output, "bQ"); break;
                    case BKING: strcpy(output, "bK"); break;
                }

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

            Board[to_index[0]][to_index[1]] = Board[from_index[0]][from_index[1]];
            Board[from_index[0]][from_index[1]] = NOPIECE;

            cout << endl << from_index[0] << " " << from_index[1] << endl << to_index[0] << " " << to_index[1] << endl;
        }

    }

    return 0;
}