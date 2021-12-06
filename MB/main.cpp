#include <iostream>
#include <time.h>
#include "windows.h"
#include <Windows.h>
using namespace std;

int language;


class Player {
    string layout[10][10], temp_layout[10][10];
    int x, y, rotate;
    int lenght = 1;
    char move;
    int stage = 0;
    int side = 0;
    int h_or_v = 0;
    int temp, temp2;
public:
    int ship_amount = 10;
    string player;
    Player() {
        autoFill();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (layout[i][j] == " * ") {
                    layout[i][j] = " . ";
                }
            }
        }
        ship_amount = 10;
        cout << "\033[2J\033[1;1H";
    }

    Player(string playerT) : player{ playerT } {
    restart:
        lenght = 1;
        fillWithDots(layout);
        fillWithDots(temp_layout);
        while (ship_amount != 0) {
            x = 4;
            y = 4;
            rotate = 0;
            for (int i = 0; i < lenght; i++) {
                temp_layout[x][y + i] = " ^ ";
            }
        turn1:
            cout << "\033[2J\033[1;1H";
            distrPrint();
            if (language == 0) {
                cout << "Хід гравця " << player << "\n\nВикористовуйте WASD для переміщення корабля, R для його повороту, і любу іншу букву для розміщення(також можна скористатись авторозстановкою вписавши букву U): ";
            }
            else if (language == 1) {
                cout << player << "'s turn\n\nUse WASD to move the ship, R to turn it, and any other letter for placement (you can also use auto-layout by typing the letter U): ";
            }
            cin >> move;
            switch (move) {
            case 'w':
                if (x != 0) {
                    if (rotate == 0) {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x][y + i] = " . ";
                            temp_layout[x - 1][y + i] = " ^ ";
                        }
                    }
                    else {
                        temp_layout[x + lenght - 1][y] = " . ";
                        temp_layout[x - 1][y] = " ^ ";
                    }
                    x--;
                }
                goto turn1;
            case 'a':
                if (y != 0) {
                    if (rotate == 0) {
                        temp_layout[x][y + lenght - 1] = " . ";
                        temp_layout[x][y - 1] = " ^ ";
                    }
                    else {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x + i][y] = " . ";
                            temp_layout[x + i][y - 1] = " ^ ";
                        }
                    }
                    y--;
                }
                goto turn1;
            case 's':
                if (x != 9) {
                    if (rotate == 0) {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x][y + i] = " . ";
                            temp_layout[x + 1][y + i] = " ^ ";
                        }
                        x++;
                    }
                    else if ((lenght == 1 && x != 9) || (lenght == 2 && x < 8) || (lenght == 3 && x < 7) || (lenght == 4 && x != 6)) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + lenght][y] = " ^ ";
                        x++;
                    }
                }
                goto turn1;
            case 'd':
                if (y != 9) {
                    if (rotate == 1) {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x + i][y] = " . ";
                            temp_layout[x + i][y + 1] = " ^ ";
                        }
                        y++;
                    }
                    else if ((lenght == 1 && y != 9) || (lenght == 2 && y < 8) || (lenght == 3 && y < 7) || (lenght == 4 && y != 6)) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + lenght] = " ^ ";
                        y++;
                    }
                }
                goto turn1;
            case 'r':
                if (rotate == 1 && ((lenght == 1 && y != 9) || (lenght == 2 && y < 9) || (lenght == 3 && y < 8) || (lenght == 4 && y != 7))) {
                    rotate = 0;
                    for (int i = 0; i < lenght; i++) {
                        temp_layout[x + i][y] = " . ";
                        temp_layout[x][y + i] = " ^ ";
                    }
                }
                else if (rotate == 0 && ((lenght == 1 && x != 9) || (lenght == 2 && x < 9) || (lenght == 3 && x < 8) || (lenght == 4 && x != 7))) {
                    rotate = 1;
                    for (int i = 0; i < lenght; i++) {
                        temp_layout[x][y + i] = " . ";
                        temp_layout[x + i][y] = " ^ ";
                    }
                }
                goto turn1;
            case 'u':
                autoFill();
                distrPrint();
                break;
            default:
                if (rotate == 0) {
                    for (int i = 0; i < lenght; i++) {
                        if (layout[x][y + i] == " O " || layout[x][y + i] == " * ") {
                            goto turn1;
                        }
                    }
                    for (int i = 0; i < lenght; i++) {
                        layout[x][y + i] = " O ";
                        temp_layout[x][y + i] = " . ";
                    }
                }
                else {
                    for (int i = 0; i < lenght; i++) {
                        if (layout[x + i][y] == " O " || layout[x + i][y] == " * ") {
                            goto turn1;
                        }
                    }
                    for (int i = 0; i < lenght; i++) {
                        layout[x + i][y] = " O ";
                        temp_layout[x + i][y] = " . ";
                    }
                }
                XDistribution();
                ship_amount--;
                break;
            }
            if (ship_amount == 6 || ship_amount == 3 || ship_amount == 1) {
                lenght += 1;
            }
        }
        ship_amount = 10;
        cout << "\033[2J\033[1;1H";
        distrPrint();
        if (language == 0) {
            cout << "Введіть N для відміни, або любу іншу букву для підтвердження: ";
        }
        else if (language == 1) {
            cout << "Enter N to cancel, or any other letter to confirm: ";
        }
        cin >> move;
        cout << "\033[2J\033[1;1H";
        if (move == 'n') {
            goto restart;
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (layout[i][j] == " * ") {
                    layout[i][j] = " . ";
                }
            }
        }
    }

    void autoFill() {
        lenght = 4;
        ship_amount = 10;
        fillWithDots(layout);
        fillWithDots(temp_layout);
        while (ship_amount != 0) {
        turn2:
            rotate = rand() % 2;
            x = rand() % 10;
            y = rand() % 10;
            if (rotate == 0) {
                for (int i = y; i < y + lenght; i++) {
                    if (i < 10 && layout[x][i] == " . ") {
                        continue;
                    }
                    else {
                        goto turn2;
                    }
                }
            }
            else {
                for (int i = x; i < x + lenght; i++) {
                    if (i < 10 && layout[i][y] == " . ") {
                        continue;
                    }
                    else {
                        goto turn2;
                    }
                }
            }
            if (rotate == 0) {
                for (int i = 0; i < lenght; i++) {
                    layout[x][y + i] = " O ";
                }
            }
            else {
                for (int i = 0; i < lenght; i++) {
                    layout[x + i][y] = " O ";
                }
            }
            XDistribution();
            ship_amount--;
            cout << "\033[2J\033[1;1H";
            if (ship_amount == 9 || ship_amount == 7 || ship_amount == 4) {
                lenght -= 1;
            }
        }
    }

    void fillWithDots(string layoutT[10][10]) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                layoutT[i][j] = " . ";
            }
        }
    }

    void distrPrint() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (temp_layout[i][j] == " ^ " || layout[i][j] == " * ") {
                    cout << temp_layout[i][j];
                }
                else {
                    cout << layout[i][j];
                }
            }
            cout << endl;
        }
    }

    void XDistribution() {
        if (rotate == 0) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + lenght; j++) {
                    if (j >= 0 && j <= 9 && i <= 9 && i >= 0 && layout[i][j] != " O " && layout[i][j] != " X ") {
                        layout[i][j] = " * ";
                    }
                }
            }
        }
        else {
            for (int i = x - 1; i <= x + lenght; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (j >= 0 && j <= 9 && i <= 9 && i >= 0 && layout[i][j] != " O " && layout[i][j] != " X ") {
                        layout[i][j] = " * ";
                    }
                }
            }
        }
    }

    void shootPrint() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == x && j == y && ship_amount > 0) {
                    cout << " + ";
                }
                else if (layout[i][j] == " X " || layout[i][j] == " * ") {
                    cout << layout[i][j];
                }
                else {
                    cout << temp_layout[i][j];
                }
            }
            cout << endl;
        }
    }

    void hitCheck() {
        if ((y != 0 && (layout[x][y - 1] == " O " || layout[x][y - 1] == " X ")) || (y != 9 && (layout[x][y + 1] == " O " || layout[x][y + 1] == " X "))) {
            for (int i = y - 3; i < y + 3; i++) {
                if (i < 0 || i > 9) {
                    continue;
                }
                else if (i + 3 < 10 && layout[x][i] == " X " && layout[x][i + 1] == " X " && layout[x][i + 2] == " X " && layout[x][i + 3] == " X ") {
                    y = i;
                    rotate = 0;
                    lenght = 4;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > y - 3 && i + 2 < 10 && layout[x][i] == " X " && layout[x][i + 1] == " X " && layout[x][i + 2] == " X " && (i + 3 == 10 || layout[x][i + 3] != " O ") && (i - 1 == -1 || layout[x][i - 1] != " O ")) {
                    y = i;
                    rotate = 0;
                    lenght = 3;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > y - 2 && i + 1 < 10 && layout[x][i] == " X " && layout[x][i + 1] == " X " && (i + 2 == 10 || (layout[x][i + 2] != " O " && layout[x][i + 2] != " X ")) && (i - 1 == -1 || (layout[x][i - 1] != " O " && layout[x][i - 1] != " X "))) {
                    y = i;
                    rotate = 0;
                    lenght = 2;
                    XDistribution();
                    ship_amount--;
                    return;
                }
            }
        }
        else if ((x != 0 && (layout[x - 1][y] == " O " || layout[x - 1][y] == " X ")) || (x != 9 && (layout[x + 1][y] == " O " || layout[x + 1][y] == " X "))) {
            for (int i = x - 3; i < x + 3; i++) {
                if (i < 0 || i > 9) {
                    continue;
                }
                else if (i + 3 < 10 && layout[i][y] == " X " && layout[i + 1][y] == " X " && layout[i + 2][y] == " X " && layout[i + 3][y] == " X ") {
                    x = i;
                    rotate = 1;
                    lenght = 4;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > x - 3 && i + 2 < 10 && layout[i][y] == " X " && layout[i + 1][y] == " X " && layout[i + 2][y] == " X " && (i + 3 == 10 || layout[i + 3][y] != " O ") && (i - 1 == -1 || layout[i - 1][y] != " O ")) {
                    x = i;
                    rotate = 1;
                    lenght = 3;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > x - 2 && i + 1 < 10 && layout[i][y] == " X " && layout[i + 1][y] == " X " && (i + 2 == 10 || (layout[i + 2][y] != " O " && layout[i + 2][y] != " X ")) && (i - 1 == -1 || (layout[i - 1][y] != " O " && layout[i - 1][y] != " X "))) {
                    x = i;
                    rotate = 1;
                    lenght = 2;
                    XDistribution();
                    ship_amount--;
                    return;
                }
            }
        }
        else {
            lenght = 1;
            ship_amount--;
            XDistribution();
        }
    }

    void shoot(Player playerT) {
        x = 4;
        y = 4;
    metka:
        cout << "\033[2J\033[1;1H";
        shootPrint();
        if (language == 0) {
            cout << "Хід гравця " << playerT.player;
            cout << "\n\nВикористовуйте WASD для переміщення прицілу, та любу іншу літеру для пострілу: ";
        }
        else if (language == 1) {
            cout << playerT.player << "'s turn";
            cout << "\n\nUse WASD to move the sight, and any other letter to shoot: ";
        }
        cin >> move;
        switch (move) {
        case 'w':
            if (x != 0) {
                x--;
            }
            goto metka;
        case 'a':
            if (y != 0) {
                y--;
            }
            goto metka;
        case 's':
            if (x != 9) {
                x++;
            }
            goto metka;
        case 'd':
            if (y != 9) {
                y++;
            }
            goto metka;
        default:
            if (layout[x][y] == " X " || layout[x][y] == " * ") {
                goto metka;
            }
            else if (layout[x][y] == " . ") {
                cout << "\033[2J\033[1;1H";
                layout[x][y] = " * ";
                break;
            }
            else {
                layout[x][y] = " X ";
                hitCheck();
                if (ship_amount > 0) {
                    shoot(playerT);
                }
                else {
                    cout << "\033[2J\033[1;1H";
                    shootPrint();
                    if (language == 0) {
                        cout << "Переміг гравець " << playerT.player;
                    }
                    else if (language == 1) {
                        cout << "Player " << playerT.player << " won";
                    }
                }
            }
        }
    }

    void shootBot() {
        cout << "\033[2J\033[1;1H";
        if (language == 0) {
            cout << "Хід бота" << endl;
        }
        else if (language == 1) {
            cout << "Bot's turn" << endl;
        }
        temp = ship_amount;
        switch (stage) {
        case 0:
            x = rand() % 10;
            y = rand() % 10;
            while (layout[x][y] == " X " || layout[x][y] == " * ") {
                x = rand() % 10;
                y = rand() % 10;
            }
            if (layout[x][y] == " O ") {
                layout[x][y] = " X ";
                hitCheck();
                if (ship_amount > 0 && ship_amount == temp) {
                    shootPrint();
                    Sleep(4000);
                    stage++;
                    cout << "\033[2J\033[1;1H";
                }
                else if (ship_amount > 0) {
                    shootPrint();
                    Sleep(4000);
                    shootBot();
                }
                else {
                    cout << "\033[2J\033[1;1H";
                    shootPrint();
                    if (language == 0) {
                        cout << "Переміг Бот" << endl;
                    }
                    else if (language == 1) {
                        cout << "Bot won" << endl;
                    }
                    return;
                }
            }
            else {
                layout[x][y] = " * ";
                shootPrint();
                Sleep(4000);
                break;
            }
        case 1:
        stage2:
            side = rand() % 4 + 1;
            if (side == 1) {
                if (y == 0 || layout[x][y - 1] == " * " || layout[x][y - 1] == " X ") {
                    goto stage2;
                }
                y--;
            }
            else if (side == 2) {
                if (x == 0 || layout[x - 1][y] == " * " || layout[x - 1][y] == " X ") {
                    goto stage2;
                }
                x--;
            }
            else if (side == 3) {
                if (y == 9 || layout[x][y + 1] == " * " || layout[x][y + 1] == " X ") {
                    goto stage2;
                }
                y++;
            }
            else if (side == 4) {
                if (x == 9 || layout[x + 1][y] == " * " || layout[x + 1][y] == " X ") {
                    goto stage2;
                }
                x++;
            }
            shootPrint();
            Sleep(4000);
            if (layout[x][y] == " . ") {
                layout[x][y] = " * ";
                if (side == 1) {
                    y++;
                }
                else if (side == 2) {
                    x++;
                }
                else if (side == 3) {
                    y--;
                }
                else if (side == 4) {
                    x--;
                }
                break;
            }
            else {
                layout[x][y] = " X ";
                hitCheck();
                if (ship_amount > 0 && ship_amount == temp) {
                    stage++;
                    if (side == 1 || side == 3) {
                        h_or_v = 0;
                    }
                    else if (side == 2 || side == 4) {
                        h_or_v = 1;
                    }
                    side = rand() % 2 + 1;
                    cout << "\033[2J\033[1;1H";
                }
                else if (ship_amount > 0) {
                    stage = 0;
                    shootBot();
                }
                else {
                    cout << "\033[2J\033[1;1H";
                    shootPrint();
                    if (language == 0) {
                        cout << "Переміг Бот" << endl;
                    }
                    else if (language == 1) {
                        cout << "Bot won" << endl;
                    }
                    return;
                }
            }
        case 2:
        stage3:
            if (h_or_v == 0) {
                if (side == 1) {
                    for (int i = y; i >= y - 3; i--) {
                        if (i < 0 || layout[x][i] == " * ") {
                            side = 2;
                            goto stage3;
                        }
                        else if (layout[x][i] == " X ") {
                            continue;
                        }
                        else if (layout[x][i] == " O ") {
                            temp2 = y;
                            y = i;
                            shootPrint();
                            y = temp2;
                            Sleep(4000);
                            layout[x][i] = " X ";
                            hitCheck();
                            if (ship_amount > 0 && ship_amount == temp) {
                                cout << "\033[2J\033[1;1H";
                            }
                            else if (ship_amount > 0) {
                                stage = 0;
                                shootBot();
                            }
                            else {
                                cout << "\033[2J\033[1;1H";
                                shootPrint();
                                if (language == 0) {
                                    cout << "Переміг Бот" << endl;
                                }
                                else if (language == 1) {
                                    cout << "Bot won" << endl;
                                }
                                return;
                            }
                        }
                        else {
                            layout[x][i] = " * ";
                            break;
                        }
                    }
                }
                if (side == 2) {
                    for (int i = y; i <= y + 3; i++) {
                        if (i > 9 || layout[x][i] == " * ") {
                            side = 1;
                            goto stage3;
                        }
                        else if (layout[x][i] == " X ") {
                            continue;
                        }
                        else if (layout[x][i] == " O ") {
                            temp2 = y;
                            y = i;
                            shootPrint();
                            y = temp2;
                            Sleep(4000);
                            layout[x][i] = " X ";
                            hitCheck();
                            if (ship_amount > 0 && ship_amount == temp) {
                                cout << "\033[2J\033[1;1H";
                            }
                            else if (ship_amount > 0) {
                                stage = 0;
                                shootBot();
                            }
                            else {
                                cout << "\033[2J\033[1;1H";
                                shootPrint();
                                if (language == 0) {
                                    cout << "Переміг Бот" << endl;
                                }
                                else if (language == 1) {
                                    cout << "Bot won" << endl;
                                }
                                return;
                            }
                        }
                        else {
                            layout[x][i] = " * ";
                            break;
                        }
                    }
                }
            }
            if (h_or_v == 1) {
                if (side == 1) {
                    for (int i = x; i >= x - 3; i--) {
                        if (i < 0 || layout[i][y] == " * ") {
                            side = 2;
                            goto stage3;
                        }
                        else if (layout[i][y] == " X ") {
                            continue;
                        }
                        else if (layout[i][y] == " O ") {
                            temp2 = x;
                            x = i;
                            shootPrint();
                            x = temp2;
                            Sleep(4000);
                            layout[i][y] = " X ";
                            hitCheck();
                            if (ship_amount > 0 && ship_amount == temp) {
                                cout << "\033[2J\033[1;1H";
                            }
                            else if (ship_amount > 0) {
                                stage = 0;
                                shootBot();
                            }
                            else {
                                cout << "\033[2J\033[1;1H";
                                shootPrint();
                                if (language == 0) {
                                    cout << "Переміг Бот" << endl;
                                }
                                else if (language == 1) {
                                    cout << "Bot won" << endl;
                                }
                                return;
                            }
                        }
                        else {
                            layout[i][y] = " * ";
                            break;
                        }
                    }
                }
                if (side == 2) {
                    for (int i = x; i <= x + 3; i++) {
                        if (i < 0 || layout[i][y] == " * ") {
                            side = 1;
                            goto stage3;
                        }
                        else if (layout[i][y] == " X ") {
                            continue;
                        }
                        else if (layout[i][y] == " O ") {
                            temp2 = x;
                            x = i;
                            shootPrint();
                            x = temp2;
                            Sleep(4000);
                            layout[i][y] = " X ";
                            hitCheck();
                            if (ship_amount > 0 && ship_amount == temp) {
                                cout << "\033[2J\033[1;1H";
                            }
                            else if (ship_amount > 0) {
                                stage = 0;
                                shootBot();
                            }
                            else {
                                cout << "\033[2J\033[1;1H";
                                shootPrint();
                                if (language == 0) {
                                    cout << "Переміг Бот" << endl;
                                }
                                else if (language == 1) {
                                    cout << "Bot won" << endl;
                                }
                                return;
                            }
                        }
                        else {
                            layout[i][y] = " * ";
                            break;
                        }
                    }
                }
            }
        }
    }
};

void twoPlayerGame() {
    string name;
    if (language == 0) {
        cout << "Гравець 1, введіть своє імя: ";
    }
    else if (language == 1) {
        cout << "Player 1, enter your name : ";
    }
    cin >> name;
    cout << "\033[2J\033[1;1H";
    Player player1(name);
    if (language == 0) {
        cout << "Гравець 2, введіть своє імя: ";
    }
    else if (language == 1) {
        cout << "Player 2, enter your name : ";
    }
    cin >> name;
    cout << "\033[2J\033[1;1H";
    Player player2(name);
here:
    if (player1.ship_amount > 0) {
        player2.shoot(player1);
    }
    else {
        return;
    }
    if (player2.ship_amount > 0) {
        player1.shoot(player2);
        goto here;
    }
    else {
        return;
    }
}

void onePlayerGame() {
    string name;
    if (language == 0) {
        cout << "Гравець 1, введіть своє імя: ";
    }
    else if (language == 1) {
        cout << "Player 1, enter your name: ";
    }
    cin >> name;
    cout << "\033[2J\033[1;1H";
    Player player1(name);
    Player bot;
here2:
    if (player1.ship_amount > 0) {
        bot.shoot(player1);
    }
    else {
        return;
    }
    if (bot.ship_amount > 0) {
        player1.shootBot();
        goto here2;
    }
    else {
        return;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "\033[2J\033[1;1H";//очистка консолі(чисто для красоти)
    srand(time(NULL));
    cout << "Choice language(0 - UA; 1 - EN): ";
    cin >> language;
    cout << "\033[2J\033[1;1H";
    if (language == 0) {
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
    }
    else if (language == 1) {
        cout << "This is a program of the game 'Sea Battle'. \n";
        cout << "Two modes are available: game against the person and against the computer. \n";
        cout << "The object of the game is to sink all enemy ships before him. \n";
        cout << "______________________________________________________________ \n";
        cout << "                                                                \n";
        cout << "The game takes place on a 10x10 field \n";
        cout << "There are a total of ten ships: \n";
        cout << "  1 ship - a row of 4 cells \n";
        cout << "  2 ships - a row of 3 cells \n";
        cout << "  3 ships - a row of 2 cells \n";
        cout << "  4 ships - 1 cell \n";
    }
    int play_or_exit = 0;
    if (language == 0) {
        cout << "Введіть 1 щоб почати гру; 0 щоб вийти: ";
    }
    else if (language == 1) {
        cout << "Enter 1 to start the game; 0 to exit: ";
    }
    cin >> play_or_exit;
    cout << "\033[2J\033[1;1H";
    if (play_or_exit == 1) {
        if (language == 0) {
            cout << "Граємо з ботом чи з іншим гравцем?" << endl;
            cout << "1 - з ботом, 2 - з іншим гравцем: ";
        }
        else if (language == 1) {
            cout << "Are we playing with a bot or another player?" << endl;
            cout << "1 - with a bot, 2 - with another player : ";
        }
        cin >> play_or_exit;
        if (play_or_exit == 1) {
            onePlayerGame();
        }
        else {
            twoPlayerGame();
        }
    }
    if (language == 0) {
        cout << "Бувай!";
    }
    else if (language == 1) {
        cout << "Good luck!";
    }
    return 0;
}