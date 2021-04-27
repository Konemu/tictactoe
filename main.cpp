#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fill;
using std::string;


// Stand in for the three possible values a field can contain. 0 = nothing, 1 = X, 2 = O
enum Field {
    Empty,
    Cross,
    Circle
};


// This class contains the size of the play area and a 2D vector containing the fields of the play area.
struct Game {

    int gameSize;

    vector<vector<Field>> area;


    // Constructor: Initialises size and creates the play area such that all fields are empty.
    explicit Game(const int n) {
        gameSize = n;

        area.resize(n);
        for ( int i = 0; i < n; i++) {
            area[i].resize(n, Empty);
        }

    }

    // Returns a representation of the play area state for printing to console.
    string toString() {
        string outStr;
        outStr += "  ";
        for (int i = 1; i <= gameSize; i++) {
            outStr += "|" + std::to_string(i);
        }
        outStr += "|x\n";
        int k = 1;
        for (auto row: area) {
            outStr += " " + std::to_string(k) + "|";
            for (Field field: row) {
                switch (field) {
                    case Empty:
                        outStr += " |";
                        break;

                    case Cross :
                        outStr += "X|";
                        break;

                    case Circle :
                        outStr += "O|";
                        break;

                }
            }
            outStr += "\n";
            k++;
        }
        outStr += " y\n";
        return outStr;
    }
};

// Returns true if any row contains marks of only one type.
bool completedRow(Game & game) {
    for (auto row: game.area) {
        bool flag = true;
        for (Field field: row) {
            if (field != Cross) {
                flag = false;
            }
        }
        if (flag) {
            return true;
        }
    }
    for (auto row: game.area) {
        bool flag = true;
        for (Field field: row) {
            if (field != Circle) {
                flag = false;
            }
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

// Returns true if any column contains marks of only one type.
bool completedColumn(Game & game) {
    int n = game.gameSize;
    for (int i = 0; i < n; i++) {

        bool flag = true;

        for (int j = 0; j < n; j++) {

            if (game.area[j][i] != Cross ) {
                flag = false;
            }

        }
        if (flag) {
            return true;
        }
        flag = true;
        for (int j = 0; j < n; j++) {

            if (game.area[j][i] != Circle ) {
                flag = false;
            }

        }
        if (flag) {
            return true;
        }

    }
    return false;
}

// Returns true if any one of the two diagonals contains marks of only one type. Ugly AF!
bool completedDiagonal(Game & game) {
    int n = game.gameSize;
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[i][i] != Cross) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[i][i] != Circle) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[n - 1 - i][n - 1 - i] != Cross) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[n - 1 - i][n - 1 - i] != Circle) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    return false;
}

// Returns true if all fields have been marked.
bool areaFull(Game & game) {
    bool flag = true;
    for (int i = 0; i < game.gameSize; i++) {
        for (int j = 0; j <game.gameSize; j++) {
            if (game.area[i][j] == Empty) {
                flag = false;
            }
        }
    }
    if (flag) {
        return true;
    } else {
        return false;
    }

}

// Checks if game is finished.
bool gameNotFinished(Game & game) {
    if (completedRow(game) || completedColumn(game) || completedDiagonal(game) || areaFull(game)) {
        return false;
    } else {
        return true;
    }
}

// Runs the game.
int main() {

    int gameSize;

    // User specifies size of play area:
    cout << "Enter play-area size n:" << endl;
    cin >> gameSize;

    // Game instance is created with specified size.
    Game game(gameSize);

    int count = 0;

    // Runs as long as the game is not over.
    while (gameNotFinished(game) ) {

        int x,y;

        // Print game to console.
        cout << game.toString() << endl;

        // Players take turns´marking fields.
        if (count % 2 == 0) {
            cout << "Player 1: Enter field coords:" << endl;
        } else {
            cout << "Player 2: Enter field coords:" << endl;
        }
        cout << "X:";
        cin >> x;
        cout << "Y:";
        cin >> y;
        // Check if coordinates are valid.
        if ( x < 0 || x > gameSize || y < 0 || y > gameSize ) {
            cout << "Error: Invalid coords!" << endl;
            continue;
        }
        x--;
        y--;

        // Mark field while checking if it is already marked.
        if (count % 2 == 0) {
            if (game.area[y][x] == Empty) {
                game.area[y][x] = Cross;
            } else {
                cout << "Error: field already populated." << endl;
                continue;
            }

        } else {
            if (game.area[y][x] == Empty) {
                game.area[y][x] = Circle;
            } else {
                cout << "Error: field already populated." << endl;
                continue;
            }
        }

        count++;
    }
    // Print final game state.
    cout << "Game finished!\n";
    cout << game.toString();

    return 0;
}

