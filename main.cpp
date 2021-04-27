#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fill;

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
        for ( auto row: area ) {
            row.resize(n);
            fill(row.begin(), row.end(), Empty);
        }

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

}

bool completedDiagonal(Game & game) {


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

    while (gameNotFinished(game) ) {

    }

    return 0;
}

