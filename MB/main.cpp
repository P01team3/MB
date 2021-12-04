#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;


class Player {
    string layout[10][10], temp_layout[10][10];
    int x, y, rotate;
    int lenght = 1;
    char move;
    int stage = 1;
    int side = 0;
    int h_or_v = 0;
    int temp_x, temp_y;
public:
    int ship_amount = 10;
    string player;
    Player(string playerT) : player{ playerT } {
        fillWithDots(layout);
        fillWithDots(temp_layout);
        while (ship_amount != 0) {
            x = 4;
            y = 4;
            rotate = 0;
            for (int i = 0; i < lenght; i++) {
                temp_layout[x][y + i] = " ▣ ";
            }
        turn1:
            cout << "\033[2J\033[1;1H";
            distrPrint();
            cout << "Хід гравця " << player << "\n\nВикористовуйте WASD для переміщення корабля, R для його повороту, і любу іншу букву для розміщення(також можна скористатись авторозстановкою вписавши букву U): ";
            cin >> move;
            switch (move) {
            case 'w':
                if (x != 0) {
                    if (rotate == 0) {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x][y + i] = " . ";
                            temp_layout[x - 1][y + i] = " ▣ ";
                        }
                    }
                    else {
                        temp_layout[x + lenght - 1][y] = " . ";
                        temp_layout[x - 1][y] = " ▣ ";
                    }
                    x--;
                }
                goto turn1;
            case 'a':
                if (y != 0) {
                    if (rotate == 0) {
                        temp_layout[x][y + lenght - 1] = " . ";
                        temp_layout[x][y - 1] = " ▣ ";
                    }
                    else {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x + i][y] = " . ";
                            temp_layout[x + i][y - 1] = " ▣ ";
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
                            temp_layout[x + 1][y + i] = " ▣ ";
                        }
                        x++;
                    }
                    else if ((lenght == 1 && x != 9) || (lenght == 2 && x < 8) || (lenght == 3 && x < 7) || (lenght == 4 && x != 6)) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x + lenght][y] = " ▣ ";
                        x++;
                    }
                    y--;
                }
                goto turn1;
            case 'd':
                if (y != 9) {
                    if (rotate == 1) {
                        for (int i = 0; i < lenght; i++) {
                            temp_layout[x + i][y] = " . ";
                            temp_layout[x + i][y + 1] = " ▣ ";
                        }
                        y++;
                    }
                    else if ((lenght == 1 && y != 9) || (lenght == 2 && y < 8) || (lenght == 3 && y < 7) || (lenght == 4 && y != 6)) {
                        temp_layout[x][y] = " . ";
                        temp_layout[x][y + lenght] = " ▣ ";
                        y++;
                    }
                }
                goto turn1;
            case 'r':
                if (rotate == 1 && ((lenght == 1 && y != 9) || (lenght == 2 && y < 9) || (lenght == 3 && y < 8) || (lenght == 4 && y != 7))) {
                    rotate = 0;
                    for (int i = 0; i < lenght; i++) {
                        temp_layout[x + i][y] = " . ";
                        temp_layout[x][y + i] = " ▣ ";
                    }
                }
                else if (rotate == 0 && ((lenght == 1 && x != 9) || (lenght == 2 && x < 9) || (lenght == 3 && x < 8) || (lenght == 4 && x != 7))) {
                    rotate = 1;
                    for (int i = 0; i < lenght; i++) {
                        temp_layout[x][y + i] = " . ";
                        temp_layout[x + i][y] = " ▣ ";
                    }
                }
                goto turn1;
            case 'u':
            replacing:
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
                            layout[x][y + i] = " □ ";
                        }
                    }
                    else {
                        for (int i = 0; i < lenght; i++) {
                            layout[x + i][y] = " □ ";
                        }
                    }
                    XDistribution();
                    ship_amount--;
                    cout << "\033[2J\033[1;1H";
                    if (ship_amount == 9 || ship_amount == 7 || ship_amount == 4) {
                        lenght -= 1;
                    }
                }
                distrPrint();
                cout << "Введіть U для іншого варіанту ростановки, або любу іншу букву для вибору даної: ";
                cin >> move;
                if (move == 'u') {
                    goto replacing;
                }
                goto skip;
            default:
                if (rotate == 0) {
                    for (int i = 0; i < lenght; i++) {
                        if (layout[x][y + i] == " □ " || layout[x][y + i] == " ○ ") {
                            goto turn1;
                        }
                    }
                    for (int i = 0; i < lenght; i++) {
                        layout[x][y + i] = " □ ";
                        temp_layout[x][y + i] = " . ";
                    }
                }
                else {
                    for (int i = 0; i < lenght; i++) {
                        if (layout[x + i][y] == " □ " || layout[x + i][y] == " ○ ") {
                            goto turn1;
                        }
                    }
                    for (int i = 0; i < lenght; i++) {
                        layout[x + i][y] = " □ ";
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
    skip:
        ship_amount = 10;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (layout[i][j] == " ○ ") {
                    layout[i][j] = " . ";
                }
            }
        }
        cout << "\033[2J\033[1;1H";
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
                if (temp_layout[i][j] == " ▣ ") {
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
                    if (j >= 0 && j <= 9 && i <= 9 && i >= 0 && layout[i][j] != " □ " && layout[i][j] != " ⊠ ") {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        else {
            for (int i = x - 1; i <= x + lenght; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (j >= 0 && j <= 9 && i <= 9 && i >= 0 && layout[i][j] != " □ " && layout[i][j] != " ⊠ ") {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
    }

    void shootPrint() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == x && j == y && ship_amount > 0) {
                    cout << " X ";
                }
                else if (layout[i][j] == " ⊠ " || layout[i][j] == " ○ ") {
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
        if ((y != 0 && (layout[x][y - 1] == " □ " || layout[x][y - 1] == " ⊠ ")) || (y != 9 && (layout[x][y + 1] == " □ " || layout[x][y + 1] == " ⊠ "))) {
            for (int i = y - 3; i < y + 3; i++) {
                if (i < 0 || i > 9) {
                    continue;
                }
                else if (i + 3 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && layout[x][i + 3] == " ⊠ ") {
                    y = i;
                    rotate = 0;
                    lenght = 4;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > y - 3 && i + 2 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && (i + 3 == 10 || layout[x][i + 3] != " □ ") && (i - 1 == -1 || layout[x][i - 1] != " □ ")) {
                    y = i;
                    rotate = 0;
                    lenght = 3;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > y - 2 && i + 1 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && (i + 2 == 10 || (layout[x][i + 2] != " □ " && layout[x][i + 2] != " ⊠ ")) && (i - 1 == -1 || (layout[x][i - 1] != " □ " && layout[x][i - 1] != " ⊠ "))) {
                    y = i;
                    rotate = 0;
                    lenght = 2;
                    XDistribution();
                    ship_amount--;
                    return;
                }
            }
        }
        else if ((x != 0 && (layout[x - 1][y] == " □ " || layout[x - 1][y] == " ⊠ ")) || (x != 9 && (layout[x + 1][y] == " □ " || layout[x + 1][y] == " ⊠ "))) {
            for (int i = x - 3; i < x + 3; i++) {
                if (i < 0 || i > 9) {
                    continue;
                }
                else if (i + 3 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && layout[i + 3][y] == " ⊠ ") {
                    x = i;
                    rotate = 1;
                    lenght = 4;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > x - 3 && i + 2 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && (i + 3 == 10 || layout[i + 3][y] != " □ ") && (i - 1 == -1 || layout[i - 1][y] != " □ ")) {
                    x = i;
                    rotate = 1;
                    lenght = 3;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > x - 2 && i + 1 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && (i + 2 == 10 || (layout[i + 2][y] != " □ " && layout[i + 2][y] != " ⊠ ")) && (i - 1 == -1 || (layout[i - 1][y] != " □ " && layout[i - 1][y] != " ⊠ "))) {
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
        cout << "Хід гравця " << playerT.player;
        cout << "\n\nВикористовуйте WASD для переміщення прицілу, та любу іншу літеру для вистрілу: ";
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
            if (layout[x][y] == " ⊠ " || layout[x][y] == " ○ ") {
                goto metka;
            }
            else if (layout[x][y] == " . ") {
                layout[x][y] = " ○ ";
                break;
            }
            else {
                layout[x][y] = " ⊠ ";
                hitCheck();
                if (ship_amount > 0) {
                    shoot(playerT);
                }
                else {
                    cout << "\033[2J\033[1;1H";
                    shootPrint();
                    cout << "Переміг гравець " << playerT.player;
                }
            }
        }
    }

    void shootBot() {
        int temp = ship_amount;
    stage1:
        x = rand() % 10;
        y = rand() % 10;
        temp_x = x;
        temp_y = y;
        cout << "\033[2J\033[1;1H";
        cout << "Хід Бота\n";
        if (stage == 1) {
            if (layout[x][y] == " ⊠ " || layout[x][y] == " ○ ") {
                goto stage1;
            }
            else if (layout[x][y] == " . ") {
                layout[x][y] = " ○ ";
                shootPrint();
                sleep(4);
            }
            else {
                layout[x][y] = " ⊠ ";
                hitCheck();
                if (ship_amount > 0 && ship_amount == temp) {
                    shootPrint();
                    sleep(4);
                    stage++;
                    cout << endl << "--------------------------" << endl;
                }
                else if (ship_amount > 0) {
                    shootPrint();
                    sleep(4);
                    shootBot();
                }
                else {
                    cout << "\033[2J\033[1;1H";
                    shootPrint();
                    cout << "Переміг Бот";
                }
            }
        }
        if (stage == 2) {
        stage2:
            side = rand() % 4 + 1;
            if (side == 1) {
                if (x - 1 < 0 || (x - 1 >= 0 && layout[x - 1][y] == " ○ " && layout[x - 1][y] == " ⊠ ")) {
                    goto stage2;
                }
                x--;
                shootPrint();
                sleep(4);
                if (layout[x][y] == " . ") {
                    layout[x][y] = " ○ ";
                }
                else {
                    layout[x][y] = " ⊠ ";
                    hitCheck();
                    if (ship_amount > 0 && ship_amount == temp) {
                        stage++;
                        h_or_v = 1;
                        cout << endl << "--------------------------" << endl;
                    }
                    else if (ship_amount > 0) {
                        stage = 1;
                        shootBot();
                    }
                    else {
                        cout << "\033[2J\033[1;1H";
                        shootPrint();
                        cout << "Переміг Бот";
                    }
                }
            }
            else if (side == 2) {
                if (y + 1 > 9 && layout[x][y + 1] == " ○ " && layout[y + 1][y] == " ⊠ ") {
                    goto stage2;
                }
                y++;
                shootPrint();
                sleep(4);
                if (layout[x][y] == " . ") {
                    layout[x][y] = " ○ ";
                }
                else {
                    layout[x][y] = " ⊠ ";
                    hitCheck();
                    if (ship_amount > 0 && ship_amount == temp) {
                        stage++;
                        h_or_v = 0;
                        cout << endl << "--------------------------" << endl;
                    }
                    else if (ship_amount > 0) {
                        stage = 1;
                        shootBot();
                    }
                    else {
                        cout << "\033[2J\033[1;1H";
                        shootPrint();
                        cout << "Переміг Бот";
                    }
                }
            }
            else if (side == 3) {
                if (x + 1 > 9 && layout[x + 1][y] == " ○ " && layout[x + 1][y] == " ⊠ ") {
                    goto stage2;
                }
                x++;
                shootPrint();
                sleep(4);
                if (layout[x][y] == " . ") {
                    layout[x][y] = " ○ ";
                }
                else {
                    layout[x][y] = " ⊠ ";
                    hitCheck();
                    if (ship_amount > 0 && ship_amount == temp) {
                        stage++;
                        h_or_v = 1;
                        cout << endl << "--------------------------" << endl;
                    }
                    else if (ship_amount > 0) {
                        stage = 1;
                        shootBot();
                    }
                    else {
                        cout << "\033[2J\033[1;1H";
                        shootPrint();
                        cout << "Переміг Бот";
                    }
                }
            }
            else if (side == 4) {
                if (y - 1 < 0 && layout[y - 1][y] == " ○ " && layout[y - 1][y] == " ⊠ ") {
                    goto stage2;
                }
                y--;
                shootPrint();
                sleep(4);
                if (layout[x][y] == " . ") {
                    layout[x][y] = " ○ ";
                }
                else {
                    layout[x][y] = " ⊠ ";
                    hitCheck();
                    if (ship_amount > 0 && ship_amount == temp) {
                        stage++;
                        h_or_v = 0;
                        cout << endl << "--------------------------" << endl;
                    }
                    else if (ship_amount > 0) {
                        stage = 1;
                        shootBot();
                    }
                    else {
                        cout << "\033[2J\033[1;1H";
                        shootPrint();
                        cout << "Переміг Бот";
                    }
                }
            }
        } if (stage == 3) {
            side = rand() % 2 + 1;
        stage3:
            if (h_or_v == 0) {
                if (side == 1 && y - 1 >= 0) {
                    y--;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage3;
                    }
                    else if (layout[x][y] == " . ") {
                        shootPrint();
                        sleep(4);
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 2;
                        goto stage3;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0 && ship_amount == temp) {
                            stage++;
                            cout << endl << "--------------------------" << endl;
                        }
                        else if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else if (side == 2 && y + 1 <= 9) {
                    y++;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage3;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 1;
                        goto stage3;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0 && ship_amount == temp) {
                            stage++;
                            cout << endl << "--------------------------" << endl;
                        }
                        else if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else {
                    side = rand() % 2 + 1;
                    goto stage3;
                }
            }
            else if (h_or_v == 1) {
                if (side == 1 && x - 1 >= 0) {
                    x--;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage3;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 2;
                        goto stage3;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0 && ship_amount == temp) {
                            stage++;
                            cout << endl << "--------------------------" << endl;
                        }
                        else if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else if (side == 2 <= 9) {
                    x++;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage3;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 1;
                        goto stage3;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0 && ship_amount == temp) {
                            stage++;
                            cout << endl << "--------------------------" << endl;
                        }
                        else if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else {
                    side = rand() % 2 + 1;
                    goto stage3;
                }
            }
        }
        if (stage == 4) {
            side = rand() % 2 + 1;
        stage4:
            if (h_or_v == 0) {
                if (side == 1 && x - 1 >= 0) {
                    x--;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage4;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 2;
                        goto stage4;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else if (side == 2 && y + 1 <= 9) {
                    y++;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage4;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 1;
                        goto stage4;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else {
                    side = rand() % 2 + 1;
                    goto stage4;
                }
            }
            else if (h_or_v == 1) {
                if (side == 1 && x - 1 >= 0) {
                    x--;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage4;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 2;
                        goto stage4;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else if (side == 2 <= 9) {
                    x++;
                    if (layout[x][y] == " ⊠ ") {
                        goto stage4;
                    }
                    else if (layout[x][y] == " . ") {
                        layout[x][y] = " ○ ";
                    }
                    else if (layout[x][y] == " ○ ") {
                        side = 1;
                        goto stage4;
                    }
                    else {
                        layout[x][y] = " ⊠ ";
                        shootPrint();
                        sleep(4);
                        hitCheck();
                        if (ship_amount > 0) {
                            stage = 1;
                            shootBot();
                        }
                        else {
                            cout << "\033[2J\033[1;1H";
                            shootPrint();
                            cout << "Переміг Бот";
                        }
                    }
                }
                else {
                    side = rand() % 2 + 1;
                    goto stage4;
                }
            }
        }

    }
};

class Bot {
    string layout[10][10], temp_layout[10][10];
    int x, y, rotate;
    int lenght = 4;
    char move;

public:

    int ship_amount = 10;
    Bot() {
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
                    layout[x][y + i] = " □ ";
                }
            }
            else {
                for (int i = 0; i < lenght; i++) {
                    layout[x + i][y] = " □ ";
                }

            }
            XDistribution();
            ship_amount--;
            cout << "\033[2J\033[1;1H";
            distrPrint();
            if (ship_amount == 9 || ship_amount == 7 || ship_amount == 4) {
                lenght -= 1;
            }
        }
        ship_amount = 10;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (layout[i][j] == " ○ ") {
                    layout[i][j] = " . ";
                }
            }
        }
        cout << "\033[2J\033[1;1H";
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
                if (temp_layout[i][j] == " ▣ ") {
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
                    if (j >= 0 && j <= 9 && i <= 9 && i >= 0 && layout[i][j] != " □ " && layout[i][j] != " ⊠ ") {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
        else {
            for (int i = x - 1; i <= x + lenght; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (j >= 0 && j <= 9 && i <= 9 && i >= 0 && layout[i][j] != " □ " && layout[i][j] != " ⊠ ") {
                        layout[i][j] = " ○ ";
                    }
                }
            }
        }
    }

    void shootPrint() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == x && j == y && ship_amount > 0) {
                    cout << " X ";
                }
                else if (layout[i][j] == " ⊠ " || layout[i][j] == " ○ ") {
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
        if ((y != 0 && (layout[x][y - 1] == " □ " || layout[x][y - 1] == " ⊠ ")) || (y != 9 && (layout[x][y + 1] == " □ " || layout[x][y + 1] == " ⊠ "))) {
            for (int i = y - 3; i < y + 3; i++) {
                if (i < 0 || i > 9) {
                    continue;
                }
                else if (i + 3 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && layout[x][i + 3] == " ⊠ ") {
                    y = i;
                    rotate = 0;
                    lenght = 4;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > y - 3 && i + 2 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && layout[x][i + 2] == " ⊠ " && (i + 3 == 10 || layout[x][i + 3] != " □ ") && (i - 1 == -1 || layout[x][i - 1] != " □ ")) {
                    y = i;
                    rotate = 0;
                    lenght = 3;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > y - 2 && i + 1 < 10 && layout[x][i] == " ⊠ " && layout[x][i + 1] == " ⊠ " && (i + 2 == 10 || (layout[x][i + 2] != " □ " && layout[x][i + 2] != " ⊠ ")) && (i - 1 == -1 || (layout[x][i - 1] != " □ " && layout[x][i - 1] != " ⊠ "))) {
                    y = i;
                    rotate = 0;
                    lenght = 2;
                    XDistribution();
                    ship_amount--;
                    return;
                }
            }
        }
        else if ((x != 0 && (layout[x - 1][y] == " □ " || layout[x - 1][y] == " ⊠ ")) || (x != 9 && (layout[x + 1][y] == " □ " || layout[x + 1][y] == " ⊠ "))) {
            for (int i = x - 3; i < x + 3; i++) {
                if (i < 0 || i > 9) {
                    continue;
                }
                else if (i + 3 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && layout[i + 3][y] == " ⊠ ") {
                    x = i;
                    rotate = 1;
                    lenght = 4;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > x - 3 && i + 2 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && layout[i + 2][y] == " ⊠ " && (i + 3 == 10 || layout[i + 3][y] != " □ ") && (i - 1 == -1 || layout[i - 1][y] != " □ ")) {
                    x = i;
                    rotate = 1;
                    lenght = 3;
                    XDistribution();
                    ship_amount--;
                    return;
                }
                else if (i > x - 2 && i + 1 < 10 && layout[i][y] == " ⊠ " && layout[i + 1][y] == " ⊠ " && (i + 2 == 10 || (layout[i + 2][y] != " □ " && layout[i + 2][y] != " ⊠ ")) && (i - 1 == -1 || (layout[i - 1][y] != " □ " && layout[i - 1][y] != " ⊠ "))) {
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
        cout << "Хід гравця " << playerT.player;
        cout << "\n\nВикористовуйте WASD для переміщення прицілу, та любу іншу літеру для вистрілу: ";
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
            if (layout[x][y] == " ⊠ " || layout[x][y] == " ○ ") {
                goto metka;
            }
            else if (layout[x][y] == " . ") {
                layout[x][y] = " ○ ";
                break;
            }
            else {
                layout[x][y] = " ⊠ ";
                hitCheck();
                if (ship_amount > 0) {
                    shoot(playerT);
                }
                else {
                    cout << "\033[2J\033[1;1H";
                    shootPrint();
                    cout << "Переміг гравець " << playerT.player;
                }
            }
        }
    }
};


void twoPlayerGame() {
    string name;
    cout << "Гравець 1, введіть своє імя: ";
    cin >> name;
    cout << "\033[2J\033[1;1H";
    Player player1(name);
    cout << "Гравець 2, введіть своє імя: ";
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
    cout << "Гравець 1, введіть своє імя: ";
    cin >> name;
    cout << "\033[2J\033[1;1H";
    Player player1(name);
    Bot bot;
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
    int play_or_exit = 0;
    cout << "Введіть 1 щоб почати гру; 0 щоб вийти: ";
    cin >> play_or_exit;
    cout << "\033[2J\033[1;1H";
    if (play_or_exit == 1) {
        cout << "Граємо з ботом чи з іншим гравцем?" << endl;
        cout << "1 - з ботом, 2 - з іншим гравцем: ";
        cin >> play_or_exit;
        if (play_or_exit == 1) {
            onePlayerGame();
        }
        else {
            twoPlayerGame();
        }
    }
    cout << "Бувай!";
    return 0;
}