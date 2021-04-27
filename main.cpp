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

enum Field {
    Empty,
    Cross,
    Circle
};


struct Game {

    int gameSize;

    vector<vector<Field>> area;


    explicit Game(const int n) {
        gameSize = n;

        area.resize(n);
        for ( int i = 0; i < n; i++) {
            area[i].resize(n, Empty);
        }

    }

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
                    case 0:
                        outStr += " |";
                        break;

                    case 1 :
                        outStr += "X|";
                        break;

                    case 2 :
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

bool completedRow(Game & game) {
    for (auto row: game.area) {
        bool flag = true;
        for (Field field: row) {
            if (field != 1) {
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
            if (field != 2) {
                flag = false;
            }
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

bool completedColumn(Game & game) {
    int n = game.gameSize;
    for (int i = 0; i < n; i++) {

        bool flag = true;

        for (int j = 0; j < n; j++) {

            if (game.area[j][i] != 1 ) {
                flag = false;
            }

        }
        if (flag) {
            return true;
        }
        flag = false;
        for (int j = 0; j < n; j++) {

            if (game.area[j][i] != 2 ) {
                flag = false;
            }

        }
        if (flag) {
            return true;
        }

    }
    return false;
}

bool completedDiagonal(Game & game) {
    int n = game.gameSize;
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[i][i] != 1) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[i][i] != 2) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[n - 1 - i][n - 1 - i] != 1) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    flag = true;
    for (int i = 0; i < n; i++) {
        if (game.area[n - 1 - i][n - 1 - i] != 2) {
            flag = false;
        }
    }
    if (flag) {
        return true;
    }
    return false;
}

bool areaFull(Game & game) {
    bool flag = true;
    for (int i = 0; i < game.gameSize; i++) {
        for (int j = 0; j <game.gameSize; j++) {
            if (game.area[i][j] == 0) {
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

bool gameNotFinished(Game & game) {
    if (completedRow(game) || completedColumn(game) || completedDiagonal(game) || areaFull(game)) {
        return false;
    } else {
        return true;
    }
}

int main() {

    int gameSize;

    cout << "Enter play-area size n:" << endl;
    cin >> gameSize;

    Game game(gameSize);

    int count = 0;

    while (gameNotFinished(game) ) {
        int x,y;
        cout << game.toString() << endl;
        if (count % 2 == 0) {
            cout << "Player 1: Enter field coords:" << endl;
        } else {
            cout << "Player 2: Enter field coords:" << endl;
        }
        cout << "X:";
        cin >> x;
        cout << "Y:";
        cin >> y;
        if ( x < 0 || x > gameSize || y < 0 || y > gameSize ) {
            cout << "Error: Invalid coords!" << endl;
            continue;
        }
        x--;
        y--;

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
    cout << "Game finished!\n";
    cout << game.toString();

    return 0;
}

