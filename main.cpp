#include <iostream>
#include <time.h>
using namespace std;
struct layouts{
  string player_layout1[10][10];
  string player_layout2[10][10];
};
int ships1(string player_layout1[10][10], int x, int y, int ship1){
  char move = ' ';
  if(ship1>0){
  cout<<"Використовуйте WASD для переміщення корабля: ";
  cin>>move;
  switch(move){
    case 'w': 
      cout<<"------------------------------\n";
      player_layout1[x][y] = " . ";
      if(x != 0 && player_layout1[x-1][y] != " O "){
        x--;
      }
      player_layout1[x][y] = " O ";
      for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
          cout<<player_layout1[i][j];
        }
        cout<<endl;
      }
      break;
    case 'a':
      cout<<"------------------------------\n";
      player_layout1[x][y] = " . ";
      if(y != 0 && player_layout1[x][y-1] != " O "){
        y--;
      }
      player_layout1[x][y] = " O ";
      for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
          cout<<player_layout1[i][j];
        }
        cout<<endl;
      }
      break;
    case 's':
      cout<<"------------------------------\n";
      player_layout1[x][y] = " . ";
      if(x != 9 && player_layout1[x+1][y] != " O "){
        x++;
      }
      player_layout1[x][y] = " O ";
      for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
          cout<<player_layout1[i][j];
        }
        cout<<endl;
      }
      break;
    case 'd':
      cout<<"------------------------------\n";
      player_layout1[x][y] = " . ";
      if(y != 9 && player_layout1[x][y+1] != " O "){
        y++;
      }
      player_layout1[x][y] = " O ";
      for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
          cout<<player_layout1[i][j];
        }
        cout<<endl;
      }
      break;
    default:
      cout<<"------------------------------\n";
      if(player_layout1[4][4] != " O "){
        x = 4;
        y = 4;
      } else {
        x = 4;
        y = 4;
        while(player_layout1[x][y] == " O "){
          x = rand()%10;
          y = rand()%10;
        }
      }
        ship1--;
      if(ship1 > 0){
        player_layout1[x][y] = " O ";
      }
      for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
          cout<<player_layout1[i][j];
        }
        cout<<endl;
      }
      break;
  }  
  ships1(player_layout1, x, y, ship1);
  }
  return 0;
}
int game_layout_1(){
  string player_layout1[10][10];
  string player_layout2[10][10];
  int x = 4;
  int y = 4;
  int ship1 = 4;
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      if(i==x && j == y){
        player_layout1[i][j] = " O ";
        cout<< player_layout1[i][j];
      } else {
        player_layout1[i][j] = " . ";
        cout<< player_layout1[i][j];
      }
    }
    cout<<"\n";
  }
  ships1(player_layout1, x, y, ship1);
  return 0;
}
int menu(){
  int play_or_exit = 0;
  cout<<"Натисніть 1 щоб почати гру; 2 щоб вийти: ";
  cin>>play_or_exit;
  switch(play_or_exit){
    case 1: game_layout_1();
    default: return 0;
  }
  return 0;
}
int main(){
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
  menu();
  cout<<"Бувай!";
  return 0;
}
