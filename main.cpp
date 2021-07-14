#include <iostream>
#include <time.h>
using namespace std;

//
//Потрібно зробити бота, вибір мови при запуску програми і оформити все поліпше
//

void XDistribution(string **temp_layout, int lenght, int x, int y, int rotate){
  switch(lenght){
    case 1:
      for(int i = x - 1; i <= x + 1; i++){
        for(int j = y - 1; j <= y + 1; j++){
          if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0){
            continue;
          }
          else{
            temp_layout[i][j] = " ○ "; 
          }
        }
      }
      break;
    case 2:
      if(rotate == 0){
        for(int i = x - 1; i <= x + 1; i++){
          for(int j = y - 1; j <= y + 2; j++){
            if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y + 1 && i == x)){
              continue;
            }
            else{
              temp_layout[i][j] = " ○ "; 
            }
          }
        }
      }
      else{
        for(int i = x - 1; i <= x + 2; i++){
          for(int j = y - 1; j <= y + 1; j++){
            if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y && i == x + 1)){
              continue;
            }
            else{
              temp_layout[i][j] = " ○ "; 
            }
          }
        }
      }
      break;
    case 3:
      if(rotate == 0){
        for(int i = x - 1; i <= x + 1; i++){
          for(int j = y - 2; j <= y + 2; j++){
            if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y + 1 && i == x) || (j == y - 1 && i == x)){
              continue;
            }
            else{
              temp_layout[i][j] = " ○ "; 
            }
          }
        }
      }
      else{
        for(int i = x - 2; i <= x + 2; i++){
          for(int j = y - 1; j <= y + 1; j++){
            if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y && i == x + 1) || (j == y && i == x - 1)){
              continue;
            }
            else{
              temp_layout[i][j] = " ○ "; 
            }
          }
        }
      }
      break;
    case 4:
      if(rotate == 0){
        for(int i = x - 1; i <= x + 1; i++){
          for(int j = y - 2; j <= y + 3; j++){
            if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y + 1 && i == x) || (j == y - 1 && i == x) || (j == y + 2 && i == x)){
              continue;
            }
            else{
              temp_layout[i][j] = " ○ "; 
            }
          }
        }
      }
      else{
        for(int i = x - 2; i <= x + 2; i++){
          for(int j = y - 1; j <= y + 1; j++){
            if(j < 0 || j > 9 || (j == y && i == x) || i > 9 || i < 0 || (j == y && i == x + 1) || (j == y && i == x - 1) || (j == y && i == x + 2)){
              continue;
            }
            else{
              temp_layout[i][j] = " ○ "; 
            }
          }
        }
      }
      break;
  }
}

void printLayout(string **layout, string **temp_layout){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      if(temp_layout[i][j] == " ○ " && layout[i][j] != " □ "  && layout[i][j] != " ▣ "){
        cout << temp_layout[i][j];
      }
      else{
        cout << layout[i][j];
      }
    }
    cout<<"\n";
  }
}

void shipDistribution(string **layout, string **temp_layout, int amount, int lenght, int x, int y, int rotate){
  char move = ' ';
  if(amount > 0){
    cout<<"Використовуйте WASD для переміщення корабля, R для його повороту, і любу іншу букву для розміщення: ";
    cin>>move;
    switch(lenght){
      case 1:
        switch(move){
          case 'w': 
            cout << "------------------------------\n";
            layout[x][y] = " . ";
            if(x != 0 && layout[x-1][y] != " □ "){
              x--;
            }
            layout[x][y] = " ▣ ";
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'a':
            cout<<"------------------------------\n";
            layout[x][y] = " . ";
            if(y != 0 && layout[x][y-1] != " □ "){
              y--;
            }
            layout[x][y] = " ▣ ";
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 's':
            cout<<"------------------------------\n";
            layout[x][y] = " . ";
            if(x != 9 && layout[x+1][y] != " □ "){
              x++;
            }
            layout[x][y] = " ▣ ";
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'd':
            cout<<"------------------------------\n";
            layout[x][y] = " . ";
            if(y != 9 && layout[x][y+1] != " □ "){
              y++;
            }
            layout[x][y] = " ▣ ";
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          default:
            cout<<"------------------------------\n";
            if(temp_layout[x][y] == " ○ "){
              cout << "\033[2J\033[1;1H";
              printLayout(layout, temp_layout);
              break;
            }
            layout[x][y] = " □ ";
            XDistribution(temp_layout, lenght, x, y, rotate);
            if(layout[4][4] != " □ "){
              x = 4;
              y = 4;
            }
            else{
              while(layout[x][y] == " □ "){
                x = rand() % 10;
                y = rand() % 10;
              }
            }
            amount--;
            if(amount > 0){
              layout[x][y] = " ▣ ";
              cout << "\033[2J\033[1;1H";
              printLayout(layout, temp_layout);
            }
            break;
        }
        break;
      case 2:
        switch(move){
          case 'w': 
            cout << "------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              if(x != 0 && layout[x-1][y] != " □ " && layout[x-1][y+1] != " □ "){
                x--;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              if(x != 0 && layout[x-1][y] != " □ "){
                x--;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'a':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              if(y != 0 && layout[x][y-1] != " □ "){
                y--;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              if(y != 0 && layout[x][y-1] != " □ " && layout[x+1][y-1] != " □ "){
                y--;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 's':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              if(x != 9 && layout[x+1][y] != " □ " && layout[x+1][y+1] != " □ "){
                x++;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              if(x != 8 && layout[x+2][y] != " □ "){
                x++;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'd':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              if(y != 8 && layout[x][y+2] != " □ "){
                y++;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              if(y != 9 && layout[x][y+1] != " □ " && layout[x+1][y+1] != " □ "){
                y++;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'r':
            cout<<"------------------------------\n";
            if(rotate == 1 && y != 9 && layout[x][y+1] != " □ "){
              rotate = 0;
              layout[x+1][y] = " . ";
              layout[x][y+1] = " ▣ ";
            }
            else if(rotate == 0 && x != 9 && layout[x+1][y] != " □ "){
              rotate = 1;
              layout[x][y+1] = " . ";
              layout[x+1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          default:
            cout<<"------------------------------\n";
            if(rotate == 0){
              if(temp_layout[x][y] == " ○ " || temp_layout[x][y+1] == " ○ "){
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
              }
            }
            else{
              if(temp_layout[x][y] == " ○ " || temp_layout[x+1][y] == " ○ "){
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
              }
            }
            if(rotate == 0){
              layout[x][y] = " □ ";
              layout[x][y+1] = " □ ";
            }
            else{
              layout[x][y] = " □ ";
              layout[x+1][y] = " □ ";
            }
            XDistribution(temp_layout, lenght, x, y, rotate);
            if(layout[4][4] != " □ " && layout[4][5] != " □ "){
              x = 4;
              y = 4;
            }
            else{
              while(y > 8 || layout[x][y] == " □ " || layout[x][y+1] == " □ "){
                x = rand() % 10;
                y = rand() % 10;
              }
            }
            amount--;
            if(amount > 0){
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              cout << "\033[2J\033[1;1H";
              printLayout(layout, temp_layout);
            }
            rotate = 0;
            break;
        }
        break;
      case 3:
        switch(move){
          case 'w': 
            cout << "------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y-1] = " . ";
              if(x != 0 && layout[x-1][y] != " □ " && layout[x-1][y+1] != " □ " && layout[x-1][y-1] != " □ "){
                x--;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x-1][y] = " . ";
              if(x != 1 && layout[x-2][y] != " □ "){
                x--;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'a':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y-1] = " . ";
              if(y != 1 && layout[x][y-2] != " □ "){
                y--;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x-1][y] = " . ";
              if(y != 0 && layout[x][y-1] != " □ " && layout[x+1][y-1] != " □ " && layout[x-1][y-1] != " □ "){
                y--;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 's':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y-1] = " . ";
              if(x != 9 && layout[x+1][y] != " □ " && layout[x+1][y+1] != " □ " && layout[x+1][y-1] != " □ "){
                x++;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x-1][y] = " . ";
              if(x != 8 && layout[x+2][y] != " □ "){
                x++;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'd':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y-1] = " . ";
              if(y != 8 && layout[x][y+2] != " □ "){
                y++;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x-1][y] = " . ";
              if(y != 9 && layout[x][y+1] != " □ " && layout[x+1][y+1] != " □ " && layout[x-1][y+1] != " □ "){
                y++;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'r':
            cout<<"------------------------------\n";
            if(rotate == 1 && y != 0 && y != 9 && layout[x][y+1] != " □ " && layout[x][y-1] != " □ "){
              rotate = 0;
              layout[x+1][y] = " . ";
              layout[x][y+1] = " ▣ ";
              layout[x-1][y] = " . ";
              layout[x][y-1] = " ▣ ";
            }
            else if(rotate == 0 && x != 0 && x != 9 && layout[x+1][y] != " □ " && layout[x-1][y] != " □ "){
              rotate = 1;
              layout[x][y+1] = " . ";
              layout[x+1][y] = " ▣ ";
              layout[x][y-1] = " . ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          default:
            cout<<"------------------------------\n";
            if(rotate == 0){
              if(temp_layout[x][y] == " ○ " || temp_layout[x][y+1] == " ○ " || temp_layout[x][y-1] == " ○ "){
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
              }
            }
            else{
              if(temp_layout[x][y] == " ○ " || temp_layout[x+1][y] == " ○ " || temp_layout[x-1][y] == " ○ "){
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
              }
            }
            if(rotate == 0){
              layout[x][y] = " □ ";
              layout[x][y+1] = " □ ";
              layout[x][y-1] = " □ ";
            }
            else{
              layout[x][y] = " □ ";
              layout[x+1][y] = " □ ";
              layout[x-1][y] = " □ ";
            }
            XDistribution(temp_layout, lenght, x, y, rotate);
            if(layout[4][4] != " □ " && layout[4][5] != " □ " && layout[4][3] != " □ "){
              x = 4;
              y = 4;
            }
            else{
              while(y > 8 || y == 0 || layout[x][y] == " □ " || layout[x][y+1] == " □ " || layout[x][y-1] == " □ "){
                x = rand() % 10;
                y = rand() % 10;
              }
            }
            amount--;
            if(amount > 0){
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y-1] = " ▣ ";
              cout << "\033[2J\033[1;1H";
              printLayout(layout, temp_layout);
            }
            rotate = 0;
            break;
        }
        break;
      case 4:
        switch(move){
          case 'w': 
            cout << "------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y+2] = " . ";
              layout[x][y-1] = " . ";
              if(x != 0 && layout[x-1][y] != " □ " && layout[x-1][y+1] != " □ " && layout[x-1][y-1] != " □ " && layout[x-1][y+2] != " □ "){
                x--;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y+2] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x+2][y] = " . ";
              layout[x-1][y] = " . ";
              if(x != 1 && layout[x-2][y] != " □ "){
                x--;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x+2][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'a':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y+2] = " . ";
              layout[x][y-1] = " . ";
              if(y != 1 && layout[x][y-2] != " □ "){
                y--;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y+2] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x+2][y] = " . ";
              layout[x-1][y] = " . ";
              if(y != 0 && layout[x][y-1] != " □ " && layout[x+1][y-1] != " □ " && layout[x-1][y-1] != " □ " && layout[x+2][y-1] != " □ "){
                y--;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x+2][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 's':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y+2] = " . ";
              layout[x][y-1] = " . ";
              if(x != 9 && layout[x+1][y] != " □ " && layout[x+1][y+1] != " □ " && layout[x+1][y-1] != " □ " && layout[x+1][y+2] != " □ "){
                x++;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y+2] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x+2][y] = " . ";
              layout[x-1][y] = " . ";
              if(x != 7 && layout[x+3][y] != " □ "){
                x++;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x+2][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'd':
            cout<<"------------------------------\n";
            if(rotate == 0){
              layout[x][y] = " . ";
              layout[x][y+1] = " . ";
              layout[x][y+2] = " . ";
              layout[x][y-1] = " . ";
              if(y != 7 && layout[x][y+3] != " □ "){
                y++;
              }
              layout[x][y] = " ▣ ";
              layout[x][y+1] = " ▣ ";
              layout[x][y+2] = " ▣ ";
              layout[x][y-1] = " ▣ ";
            }
            else{
              layout[x][y] = " . ";
              layout[x+1][y] = " . ";
              layout[x-1][y] = " . ";
              layout[x+2][y] = " . ";
              if(y != 9 && layout[x][y+1] != " □ " && layout[x+1][y+1] != " □ " && layout[x-1][y+1] != " □ " && layout[x+2][y+1] != " □ "){
                y++;
              }
              layout[x][y] = " ▣ ";
              layout[x+1][y] = " ▣ ";
              layout[x+2][y] = " ▣ ";
              layout[x-1][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          case 'r':
            cout<<"------------------------------\n";
            if(rotate == 1 && y < 8 && y != 0 && layout[x][y+1] != " □ " && layout[x][y-1] != " □ " && layout[x][y+2] != " □ "){
              rotate = 0;
              layout[x+1][y] = " . ";
              layout[x][y+1] = " ▣ ";
              layout[x-1][y] = " . ";
              layout[x][y-1] = " ▣ ";
              layout[x+2][y] = " . ";
              layout[x][y+2] = " ▣ ";
            }
            else if(rotate == 0 && x < 8 && x != 0 && layout[x+1][y] != " □ " && layout[x-1][y] != " □ " && layout[x+2][y] != " □ "){
              rotate = 1;
              layout[x][y+1] = " . ";
              layout[x+1][y] = " ▣ ";
              layout[x][y-1] = " . ";
              layout[x-1][y] = " ▣ ";
              layout[x][y+2] = " . ";
              layout[x+2][y] = " ▣ ";
            }
            cout << "\033[2J\033[1;1H";
            printLayout(layout, temp_layout);
            break;
          default:
            cout<<"------------------------------\n";
            if(rotate == 0){
              if(temp_layout[x][y] == " ○ " || temp_layout[x][y+1] == " ○ " || temp_layout[x][y-1] == " ○ " || temp_layout[x][y+2] == " ○ "){
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
              }
            }
            else{
              if(temp_layout[x][y] == " ○ " || temp_layout[x+1][y] == " ○ " || temp_layout[x-1][y] == " ○ " || temp_layout[x+1][y] == " ○ "){
                cout << "\033[2J\033[1;1H";
                printLayout(layout, temp_layout);
                break;
              }
            }
            if(rotate == 0){
              layout[x][y] = " □ ";
              layout[x][y+1] = " □ ";
              layout[x][y-1] = " □ ";
              layout[x][y+2] = " □ ";
            }
            else{
              layout[x][y] = " □ ";
              layout[x+1][y] = " □ ";
              layout[x-1][y] = " □ ";
              layout[x+2][y] = " □ ";
            }
            XDistribution(temp_layout, lenght, x, y, rotate);
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

void fillLayout(string **layout, string **temp_layout){
  int x = 4;
  int y = 4;
  int rotate = 0;
  int ship_1x1 = 4;
  int ship_1x2 = 3;
  int ship_1x3 = 2;
  int ship_1x4 = 1;
  int lenght_1x1 = 1;
  int lenght_1x2 = 2;
  int lenght_1x3 = 3;
  int lenght_1x4 = 4;
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      if(i == 4 && j == 4){
        layout[i][j] = " ▣ ";
        temp_layout[i][j] = " . ";
      }
      else{
        layout[i][j] = " . ";
        temp_layout[i][j] = " . ";
      }
    }
  }
  cout << "\033[2J\033[1;1H";
  printLayout(layout, temp_layout);
  shipDistribution(layout, temp_layout, ship_1x1, lenght_1x1, x, y, rotate);
  if(layout[4][4] != " □ " && layout[4][5] != " □ "){
    x = 4;
    y = 4;
  }
  else{
    while(y > 8 || layout[x][y] == " □ " || layout[x][y+1] == " □ "){
      x = rand() % 10;
      y = rand() % 10;
    }
  }
  layout[x][y] = " ▣ ";
  layout[x][y+1] = " ▣ ";
  cout << "\033[2J\033[1;1H";
  printLayout(layout, temp_layout);
  shipDistribution(layout, temp_layout, ship_1x2, lenght_1x2, x, y, rotate);
  if(layout[4][4] != " □ " && layout[4][5] != " □ " && layout[4][3] != " □ "){
    x = 4;
    y = 4;
  }
  else{
    while(y > 8 || y == 0 || layout[x][y] == " □ " || layout[x][y+1] == " □ " || layout[x][y-1] == " □ "){
      x = rand() % 10;
      y = rand() % 10;
    }
  }
  layout[x][y] = " ▣ ";
  layout[x][y+1] = " ▣ ";
  layout[x][y-1] = " ▣ ";
  cout << "\033[2J\033[1;1H";
  printLayout(layout, temp_layout);
  shipDistribution(layout, temp_layout, ship_1x3, lenght_1x3, x, y, rotate);
  if(layout[4][4] != " □ " && layout[4][5] != " □ " && layout[4][3] != " □ " && layout[4][6] != " □ "){
    x = 4;
    y = 4;
  }
  else{
    while(y > 7 || y == 0 || layout[x][y] == " □ " || layout[x][y+1] == " □ " || layout[x][y-1] == " □ " || layout[x][y+2] == " □ "){
      x = rand() % 10;
      y = rand() % 10;
    }
  }
  layout[x][y] = " ▣ ";
  layout[x][y+1] = " ▣ ";
  layout[x][y+2] = " ▣ ";
  layout[x][y-1] = " ▣ ";
  cout << "\033[2J\033[1;1H";
  printLayout(layout, temp_layout);
  shipDistribution(layout, temp_layout, ship_1x4, lenght_1x4, x, y, rotate);
}

void createLayout(string **&layout){
  layout = new string*[10];
  for(int l = 0; l < 10; l++){
    layout[l]= new string[10];
  }
}

void deleteLayout(string **&layout){
  for(int i = 0; i < 10; i++){
    delete[] layout[i];
  }
  delete[] layout;
}

int menuIfSeconIsNotBot(){
  string **layout_player_1;
  string **layout_player_2;
  string **temp_layout;
  int play_or_exit = 0;
  cout << "Введіть 1 щоб почати гру; 0 щоб вийти: ";
  cin >> play_or_exit;
  switch(play_or_exit){
    case 1: cout << "\033[2J\033[1;1H";
            createLayout(layout_player_1);
            createLayout(layout_player_2);
            createLayout(temp_layout);
            fillLayout(layout_player_1, temp_layout);
            deleteLayout(temp_layout);
            createLayout(temp_layout);
            fillLayout(layout_player_2, temp_layout);            
            break;
    default: cout << "\033[2J\033[1;1H";
             return 0;
  }
  return 0;
}

int main(){
  cout << "\033[2J\033[1;1H";//очистка консолі(чисто для красоти)
  srand(time(NULL));
  cout<<"Це програма гри 'Морский бій'. \n";
  cout<<"Доступно два режима: гра проти людині і проти комп'ютера. \n";
  cout<<"Ціль гри потопити всі кораблі противника раніше за нього. \n";
  cout<<"______________________________________________________________ \n";
  cout<<"                                                                \n";
  cout<<"Гра відбувається на полі 10х10 \n";
  cout<<"Загалом є десять кораблів: \n";
  cout<<"  1 корабель — ряд із 4 клітин \n";
  cout<<"  2 кораблі — ряд із 3 клітин \n";
  cout<<"  3 кораблі — ряд із 2 клітин \n";
  cout<<"  4 кораблі — 1 клітина \n";
  menuIfSeconIsNotBot();
  cout<<"Бувай!";
  return 0;
}
