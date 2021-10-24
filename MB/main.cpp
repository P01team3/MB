//
//Потрібно зробити бота, вибір мови при запуску програми і оформити все поліпше
//

#include <iostream>
#include <time.h>
using namespace std;

int player = 1;

int p1_ships_amount = 10;
int p2_ships_amount = 10;

void XDistribution(string** layout, int lenght, int x, int y, int rotate) {
    switch (lenght) {
    case 1:
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0) {
                    continue;
                }
                else {
                    layout[i][j] = " ○ ";
                }
            }
        }
        break;
    case 2:
        if (rotate == 0) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 2; j++) {
                    if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y + 1 && i == x)) {
                        continue;
                    }
                    else {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        else {
            for (int i = x - 1; i <= x + 2; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y && i == x + 1)) {
                        continue;
                    }
                    else {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        break;
    case 3:
        if (rotate == 0) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 2; j <= y + 2; j++) {
                    if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y + 1 && i == x) || (j == y - 1 && i == x)) {
                        continue;
                    }
                    else {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        else {
            for (int i = x - 2; i <= x + 2; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y && i == x + 1) || (j == y && i == x - 1)) {
                        continue;
                    }
                    else {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        break;
    case 4:
        if (rotate == 0) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 2; j <= y + 3; j++) {
                    if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y + 1 && i == x) || (j == y - 1 && i == x) || (j == y + 2 && i == x)) {
                        continue;
                    }
                    else {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        else {
            for (int i = x - 2; i <= x + 3; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y && i == x + 1) || (j == y && i == x - 1) || (j == y && i == x + 2)) {
                        continue;
                    }
                    else {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        break;
    }
}

void fillTempLayout(string** temp_layout) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            temp_layout[i][j] = " . ";
        }
    }
}

void createLayout(string**& layout) {
    layout = new string * [10];
    for (int l = 0; l < 10; l++) {
        layout[l] = new string[10];
    }
}

void deleteLayout(string**& layout) {
    for (int i = 0; i < 10; i++) {
        delete[] layout[i];
    }
    delete[] layout;
}

void printShootingLayout(string** layout, int x, int y) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == x && j == y) {
                cout << " X ";
            }
            else {
                cout << layout[i][j];
            }
        }
        cout << "\n";
    }
}

void shoot(string** layout, string** layout_with_ships, int x, int y, int& stop, int& ships_amount) {
    if (layout_with_ships[x][y] == " □ ") {
        layout[x][y] = " ⊠ ";
    }
    else {
        layout[x][y] = " ○ ";
        stop = 1;
        return;
    }
    if ((y != 0 && layout_with_ships[x][y - 1] == " □ ") || (y != 9 && layout_with_ships[x][y + 1] == " □ ")) {
        for (int i = y - 3; i < y + 3; i++) {
            if (i < 0) {
                continue;
            }
            else if (i + 3 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && layout[x][i + 3] == " ⊠ ") {
                XDistribution(layout, 4, x, i + 1, 0);
                ships_amount--;
                return;
            }
            else if (i < 9 && i > 0) {
                if (i + 4 < 10 && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && layout[x][i + 3] == " ⊠ " && layout_with_ships[x][i + 4] != " □ " && layout_with_ships[x][i] != " □ ") {
                    XDistribution(layout, 3, x, i + 2, 0);
                    ships_amount--;
                    return;
                }
                else if (i + 3 < 10 && i > y - 3 && i < y && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && layout_with_ships[x][i + 3] != " □ " && layout_with_ships[x][i] != " □ ") {
                    XDistribution(layout, 2, x, i + 1, 0);
                    ships_amount--;
                    return;
                }
            }
            else if (i == 0) {
                if (layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && layout_with_ships[x][i + 3] != " □ ") {
                    XDistribution(layout, 3, x, i + 1, 0);
                    ships_amount--;
                    return;
                }
                else if (layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout_with_ships[x][i + 2] != " □ ") {
                    XDistribution(layout, 2, x, i, 0);
                    ships_amount--;
                    return;
                }
            }
            else if (i == 9) {
                if (layout[x][i] == " ⊠ " && layout[x][i - 1] == " ⊠ " && layout[x][i - 2] == " ⊠ " && layout_with_ships[x][i - 3] != " □ ") {
                    XDistribution(layout, 3, x, i - 1, 0);
                    ships_amount--;
                    return;
                }
                else if (layout[x][i] == " ⊠ " && layout[x][i - 1] == " ⊠ " && layout_with_ships[x][i - 2] != " □ ") {
                    XDistribution(layout, 2, x, i - 1, 0);
                    ships_amount--;
                    return;
                }
            }
        }
    }
    else if ((x != 0 && layout_with_ships[x - 1][y] == " □ ") || (x != 9 && layout_with_ships[x + 1][y] == " □ ")) {
        for (int i = x - 3; i < x + 3; i++) {
            if (i < 0) {
                continue;
            }
            else if (i + 3 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && layout[i + 3][y] == " ⊠ ") {
                XDistribution(layout, 4, i + 1, y, 1);
                ships_amount--;
                return;
            }
            else if (i < 9 && i > 0) {
                if (i + 4 < 10 && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && layout[i + 3][y] == " ⊠ " && layout_with_ships[i + 4][y] != " □ " && layout_with_ships[i][y] != " □ ") {
                    XDistribution(layout, 3, i + 2, y, 1);
                    ships_amount--;
                    return;
                }
                else if (i + 3 < 10 && i > x - 3 && i < x && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && layout_with_ships[i + 3][y] != " □ " && layout_with_ships[i][y] != " □ ") {
                    XDistribution(layout, 2, i + 1, y, 1);
                    ships_amount--;
                    return;
                }
            }
            else if (i == 0) {
                if (layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && layout_with_ships[i + 3][y] != " □ ") {
                    XDistribution(layout, 3, i + 1, y, 1);
                    ships_amount--;
                    return;
                }
                else if (layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout_with_ships[i + 2][y] != " □ ") {
                    XDistribution(layout, 2, i, y, 1);
                    ships_amount--;
                    return;
                }
            }
            else if (i == 9) {
                if (layout[i][y] == " ⊠ " && layout[i - 1][y] == " ⊠ " && layout[i - 2][y] == " ⊠ " && layout_with_ships[i - 3][y] != " □ ") {
                    XDistribution(layout, 3, i - 1, y, 1);
                    ships_amount--;
                    return;
                }
                else if (layout[i][y] == " ⊠ " && layout[i - 1][y] == " ⊠ " && layout_with_ships[i - 2][y] != " □ ") {
                    XDistribution(layout, 2, i - 1, y, 1);
                    ships_amount--;
                    return;
                }
            }
        }
    }
    else {
        XDistribution(layout, 1, x, y, 0);
        ships_amount--;
        return;
    }
}


void shootMove(string** layout, int x, int y, int stop, string** layout_with_ships, int& ships_amount) {
    char move = ' ';
    if (stop == 0) {
        cout << "Гравець " << player << "\n\nВикористовуйте WASD для переміщення прицілу, та любу іншу літеру для вистрілу: ";
        cin >> move;
        switch (move) {
        case 'w':
            if (x != 0) {
                x--;
            }
            cout << "\033[2J\033[1;1H";
            printShootingLayout(layout, x, y);
            break;
        case 'a':
            if (y != 0) {
                y--;
            }
            cout << "\033[2J\033[1;1H";
            printShootingLayout(layout, x, y);
            break;
        case 's':
            if (x != 9) {
                x++;
            }
            cout << "\033[2J\033[1;1H";
            printShootingLayout(layout, x, y);
            break;
        case 'd':
            if (y != 9) {
                y++;
            }
            cout << "\033[2J\033[1;1H";
            printShootingLayout(layout, x, y);
            break;
        default:
            if (layout[x][y] == " ○ " || layout[x][y] == " ⊠ ") {
                cout << "\033[2J\033[1;1H";
                printShootingLayout(layout, x, y);
                break;
            }
            shoot(layout, layout_with_ships, x, y, stop, ships_amount);
            x = 4;
            y = 4;
            cout << "\033[2J\033[1;1H";
            printShootingLayout(layout, x, y);
            break;
        }
        shootMove(layout, x, y, stop, layout_with_ships, ships_amount);
    }
}

void twoPlayersShoot(string** layout_for_shooting_p1, string** layout_for_shooting_p2, string** layout_player_1, string** layout_player_2) {
    int x = 4, y = 4;
    int stop = 0;
    while (p1_ships_amount > 0 && p2_ships_amount > 0) {
        cout << "\033[2J\033[1;1H";
        printShootingLayout(layout_for_shooting_p1, x, y);
        if (p2_ships_amount > 0 && p1_ships_amount > 0) {
            player = 1;
            stop = 0;
            shootMove(layout_for_shooting_p1, x, y, stop, layout_player_2, p2_ships_amount);
        }
        else {
            break;
        }
        cout << "\033[2J\033[1;1H";
        printShootingLayout(layout_for_shooting_p2, x, y);
        if (p1_ships_amount > 0 && p2_ships_amount > 0) {
            player = 2;
            stop = 0;
            shootMove(layout_for_shooting_p2, x, y, stop, layout_player_1, p1_ships_amount);
        }
        else {
            break;
        }
    }
    cout << "\nПереможець - Гравець " << player << "\n";
}

void printLayout(string** layout, string** temp_layout) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (temp_layout[i][j] == " ▣ ") {
                cout << temp_layout[i][j];
            }
            else {
                cout << layout[i][j];
            }
        }
        cout << "\n";
    }
}

void shipDistribution(string** layout, string** temp_layout, int amount, int lenght, int x, int y, int rotate) {
    char move = ' ';
    if (amount > 0) {
        cout << "Гравець " << player << "\n\nВикористовуйте WASD для переміщення корабля, R для його повороту, і любу іншу букву для розміщення: ";
        cin >> move;
        switch (lenght) {
        case 1:
            switch (move) {
            case 'w':
                if (x != 0) {
                    temp_layout[x][y] = " . ";
                    x--;
                    temp_layout[x][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'a':
                if (y != 0) {
                    temp_layout[x][y] = " . ";
                    y--;
                    temp_layout[x][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 's':
                if (x != 9) {
                    temp_layout[x][y] = " . ";
                    x++;
                    temp_layout[x][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'd':
                if (y != 9) {
                    temp_layout[x][y] = " . ";
                    y++;
                    temp_layout[x][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            default:
                if (layout[x][y] == " ○ " || layout[x][y] == " □ ") {
                    cout << "\033[2J\033[1;1H";
                    printLayout(layout, temp_layout);
                    break;
                }
                layout[x][y] = " □ ";
                temp_layout[x][y] = " . ";
                XDistribution(layout, lenght, x, y, rotate);
                x = 4;
                y = 4;
                amount--;
                if (amount > 0) {
                    temp_layout[x][y] = " ▣ ";
                    cout << "\033[2J\033[1;1H";
                    printLayout(layout, temp_layout);
                }
                break;
            }
            break;
        case 2:
            switch (move) {
            case 'w':
                if (rotate == 0) {
                    if (x != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        x--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                    }
                }
                else {
                    if (x != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        x--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'a':
                if (rotate == 0) {
                    if (y != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        y--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                    }
                }
                else {
                    if (y != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        y--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 's':
                if (rotate == 0) {
                    if (x != 9) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        x++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                    }
                }
                else {
                    if (x != 8) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        x++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'd':
                if (rotate == 0) {

                    if (y != 8) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        y++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                    }
                }
                else {
                    if (y != 9) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        y++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'r':
                if (rotate == 1 && y != 9) {
                    rotate = 0;
                    temp_layout[x + 1][y] = " . ";
                    temp_layout[x][y + 1] = " ▣ ";
                }
                else if (rotate == 0 && x != 9) {
                    rotate = 1;
                    temp_layout[x][y + 1] = " . ";
                    temp_layout[x + 1][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            default:
                if (rotate == 0) {
                    if (layout[x][y] == " ○ " || layout[x][y + 1] == " ○ ") {
                        cout << "\033[2J\033[1;1H";
                        printLayout(layout, temp_layout);
                        break;
                    }
                }
                else {
                    if (layout[x][y] == " ○ " || layout[x + 1][y] == " ○ ") {
                        cout << "\033[2J\033[1;1H";
                        printLayout(layout, temp_layout);
                        break;
                    }
                }
                if (rotate == 0) {
                    layout[x][y] = " □ ";
                    layout[x][y + 1] = " □ ";
                    temp_layout[x][y] = " . ";
                    temp_layout[x][y + 1] = " . ";
                }
                else {
                    layout[x][y] = " □ ";
                    layout[x + 1][y] = " □ ";
                    temp_layout[x][y] = " . ";
                    temp_layout[x + 1][y] = " . ";
                }
                XDistribution(layout, lenght, x, y, rotate);
                x = 4;
                y = 4;
                amount--;
                if (amount > 0) {
                    temp_layout[x][y] = " ▣ ";
                    temp_layout[x][y + 1] = " ▣ ";
                    cout << "\033[2J\033[1;1H";
                    printLayout(layout, temp_layout);
                }
                rotate = 0;
                break;
            }
            break;
        case 3:
            switch (move) {
            case 'w':
                if (rotate == 0) {
                    if (x != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        x--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (x != 1) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        x--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'a':
                if (rotate == 0) {
                    if (y != 1) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        y--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (y != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        y--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 's':
                if (rotate == 0) {
                    if (x != 9) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        x++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (x != 8) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        x++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'd':
                if (rotate == 0) {
                    if (y != 8) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        y++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (y != 9) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        y++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'r':
                if (rotate == 1 && y != 0 && y != 9) {
                    rotate = 0;
                    temp_layout[x + 1][y] = " . ";
                    temp_layout[x][y + 1] = " ▣ ";
                    temp_layout[x - 1][y] = " . ";
                    temp_layout[x][y - 1] = " ▣ ";
                }
                else if (rotate == 0 && x != 0 && x != 9) {
                    rotate = 1;
                    temp_layout[x][y + 1] = " . ";
                    temp_layout[x + 1][y] = " ▣ ";
                    temp_layout[x][y - 1] = " . ";
                    temp_layout[x - 1][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            default:
                if (rotate == 0) {
                    if (layout[x][y] == " ○ " || layout[x][y + 1] == " ○ " || layout[x][y - 1] == " ○ ") {
                        cout << "\033[2J\033[1;1H";
                        printLayout(layout, temp_layout);
                        break;
                    }
                }
                else {
                    if (layout[x][y] == " ○ " || layout[x + 1][y] == " ○ " || layout[x - 1][y] == " ○ ") {
                        cout << "\033[2J\033[1;1H";
                        printLayout(layout, temp_layout);
                        break;
                    }
                }
                if (rotate == 0) {
                    layout[x][y] = " □ ";
                    layout[x][y + 1] = " □ ";
                    layout[x][y - 1] = " □ ";
                    temp_layout[x][y] = " . ";
                    temp_layout[x][y + 1] = " . ";
                    temp_layout[x][y - 1] = " . ";
                }
                else {
                    layout[x][y] = " □ ";
                    layout[x + 1][y] = " □ ";
                    layout[x - 1][y] = " □ ";
                    temp_layout[x][y] = " . ";
                    temp_layout[x + 1][y] = " . ";
                    temp_layout[x - 1][y] = " . ";
                }
                XDistribution(layout, lenght, x, y, rotate);
                x = 4;
                y = 4;
                amount--;
                if (amount > 0) {
                    temp_layout[x][y] = " ▣ ";
                    temp_layout[x][y + 1] = " ▣ ";
                    temp_layout[x][y - 1] = " ▣ ";
                    cout << "\033[2J\033[1;1H";
                    printLayout(layout, temp_layout);
                }
                rotate = 0;
                break;
            }
            break;
        case 4:
            switch (move) {
            case 'w':
                if (rotate == 0) {
                    if (x != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y + 2] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        x--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y + 2] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (x != 1) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x + 2][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        x--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x + 2][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'a':
                if (rotate == 0) {
                    if (y != 1) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y + 2] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        y--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y + 2] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (y != 0) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x + 2][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        y--;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x + 2][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 's':
                if (rotate == 0) {
                    if (x != 9) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y + 2] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        x++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y + 2] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (x != 7) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x + 2][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        x++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x + 2][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'd':
                if (rotate == 0) {
                    if (y != 7) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + 1] = " . ";
                        temp_layout[x][y + 2] = " . ";
                        temp_layout[x][y - 1] = " . ";
                        y++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x][y + 1] = " ▣ ";
                        temp_layout[x][y + 2] = " ▣ ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                }
                else {
                    if (y != 9) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + 1][y] = " . ";
                        temp_layout[x - 1][y] = " . ";
                        temp_layout[x + 2][y] = " . ";
                        y++;
                        temp_layout[x][y] = " ▣ ";
                        temp_layout[x + 1][y] = " ▣ ";
                        temp_layout[x + 2][y] = " ▣ ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            case 'r':
                if (rotate == 1 && y < 8 && y != 0) {
                    rotate = 0;
                    temp_layout[x + 1][y] = " . ";
                    temp_layout[x][y + 1] = " ▣ ";
                    temp_layout[x - 1][y] = " . ";
                    temp_layout[x][y - 1] = " ▣ ";
                    temp_layout[x + 2][y] = " . ";
                    temp_layout[x][y + 2] = " ▣ ";
                }
                else if (rotate == 0 && x < 8 && x != 0) {
                    rotate = 1;
                    temp_layout[x][y + 1] = " . ";
                    temp_layout[x + 1][y] = " ▣ ";
                    temp_layout[x][y - 1] = " . ";
                    temp_layout[x - 1][y] = " ▣ ";
                    temp_layout[x][y + 2] = " . ";
                    temp_layout[x + 2][y] = " ▣ ";
                }
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
            default:
                if (rotate == 0) {
                    if (layout[x][y] == " ○ " || layout[x][y + 1] == " ○ " || layout[x][y - 1] == " ○ " || layout[x][y + 2] == " ○ ") {
                        cout << "\033[2J\033[1;1H";
                        printLayout(layout, temp_layout);
                        break;
                    }
                }
                else {
                    if (layout[x][y] == " ○ " || layout[x + 1][y] == " ○ " || layout[x - 1][y] == " ○ " || layout[x + 2][y] == " ○ ") {
                        cout << "\033[2J\033[1;1H";
                        printLayout(layout, temp_layout);
                        break;
                    }
                }
                if (rotate == 0) {
                    layout[x][y] = " □ ";
                    layout[x][y + 1] = " □ ";
                    layout[x][y - 1] = " □ ";
                    layout[x][y + 2] = " □ ";
                    temp_layout[x][y] = " . ";
                    temp_layout[x][y + 1] = " . ";
                    temp_layout[x][y - 1] = " . ";
                    temp_layout[x][y + 2] = " . ";
                }
                else {
                    layout[x][y] = " □ ";
                    layout[x + 1][y] = " □ ";
                    layout[x - 1][y] = " □ ";
                    layout[x + 2][y] = " □ ";
                    temp_layout[x][y] = " . ";
                    temp_layout[x + 1][y] = " . ";
                    temp_layout[x - 1][y] = " . ";
                    temp_layout[x + 2][y] = " . ";
                }
                XDistribution(layout, lenght, x, y, rotate);
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                amount--;
                break;
            }
            break;
        }
        shipDistribution(layout, temp_layout, amount, lenght, x, y, rotate);
    }
}

void fillLayoutForShoot(string** layout) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            layout[i][j] = " . ";
        }
    }
}

void fillLayout(string** layout, string** temp_layout) {
    int x = 4;
    int y = 4;
    int rotate = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 4 && j == 4) {
                temp_layout[i][j] = " ▣ ";
                layout[i][j] = " . ";
            }
            else {
                layout[i][j] = " . ";
                temp_layout[i][j] = " . ";
            }
        }
    }
    cout << "\033[2J\033[1;1H";
    printLayout(layout, temp_layout);
    shipDistribution(layout, temp_layout, 4, 1, x, y, rotate);

    temp_layout[x][y] = " ▣ ";
    temp_layout[x][y + 1] = " ▣ ";
    cout << "\033[2J\033[1;1H";
    printLayout(layout, temp_layout);
    shipDistribution(layout, temp_layout, 3, 2, x, y, rotate);

    temp_layout[x][y] = " ▣ ";
    temp_layout[x][y + 1] = " ▣ ";
    temp_layout[x][y - 1] = " ▣ ";
    cout << "\033[2J\033[1;1H";
    printLayout(layout, temp_layout);
    shipDistribution(layout, temp_layout, 2, 3, x, y, rotate);

    temp_layout[x][y] = " ▣ ";
    temp_layout[x][y + 1] = " ▣ ";
    temp_layout[x][y + 2] = " ▣ ";
    temp_layout[x][y - 1] = " ▣ ";
    cout << "\033[2J\033[1;1H";
    printLayout(layout, temp_layout);
    shipDistribution(layout, temp_layout, 1, 4, x, y, rotate);
}

int menuIfSecondIsNotBot() {
    string** layout_player_1;
    string** layout_player_2;
    string** temp_layout;
    string** layout_for_shooting_p1;
    string** layout_for_shooting_p2;
    int play_or_exit = 0;
    cout << "Введіть 1 щоб почати гру; 0 щоб вийти: ";
    cin >> play_or_exit;
    switch (play_or_exit) {
    case 1: cout << "\033[2J\033[1;1H";
        createLayout(layout_player_1);
        createLayout(layout_player_2);
        createLayout(temp_layout);
        fillLayout(layout_player_1, temp_layout);
        deleteLayout(temp_layout);
        createLayout(temp_layout);
        player = 2;
        fillLayout(layout_player_2, temp_layout);
        createLayout(layout_for_shooting_p1);
        createLayout(layout_for_shooting_p2);
        fillLayoutForShoot(layout_for_shooting_p1);
        fillLayoutForShoot(layout_for_shooting_p2);
        deleteLayout(temp_layout);
        twoPlayersShoot(layout_for_shooting_p1, layout_for_shooting_p2, layout_player_1, layout_player_2);
        break;
    default: cout << "\033[2J\033[1;1H";
        return 0;
    }
    return 0;
}

int main() {
    cout << "\033[2J\033[1;1H";//очистка консолі(чисто для красоти)
    srand(time(NULL));
    cout << "Це програма гри 'Морский бій'. \n";
    cout << "Доступно два режима: гра проти людині і проти комп'ютера. \n";
    cout << "Ціль гри потопити всі кораблі противника раніше за нього. \n";
    cout << "______________________________________________________________ \n";
    cout << "                                                                \n";
    cout << "Гра відбувається на полі 10х10 \n";
    cout << "Загалом є десять кораблів: \n";
    cout << "  1 корабель — ряд із 4 клітин \n";
    cout << "  2 кораблі — ряд із 3 клітин \n";
    cout << "  3 кораблі — ряд із 2 клітин \n";
    cout << "  4 кораблі — 1 клітина \n";
    menuIfSecondIsNotBot();
    cout << "Бувай!";
    return 0;
}