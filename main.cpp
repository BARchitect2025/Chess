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
            cout << chars[i] << " ";

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

        cout << "   1  2  3  4  5  6  7  8" << endl << endl;

        cout << " What is your move (\"quit\" to quit, input format is \"a2-c3\")? ";
        cin >> input;

        if (input == "quit") {
            running = false;
        }

        system("clear");
    }

    return 0;
}