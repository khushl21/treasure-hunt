#include <time.h>
#include <windows.h>
#include <string.h>
#include <iostream>
using namespace std;

int monsters[20], treasure;

class playerDetails{
  string name;
  public:
    playerDetails(){
      cout << "Enter your name: ";
      getline(cin, name);
    }
    void won(){
      cout << "CONGRATS " << name << ", YOU FOUND THE TREASURE!!!!";
    }
};

int generateWorld(int rooms, int num){
  srand(time(0));
  int i, j;
  for(i = 0; i < num; i++){
    int same = 0;
    monsters[i] = 1 + (rand() % rooms);
    for(j = 0; j <= num; j++){
      if(monsters[i] == monsters[j]){
        same++;
      }
    }
    if(same > 1){
      i--;
    }
  }
  // for(i = 0; i < num; i++){
  //   cout << monsters[i] << endl;
  // }
  treasure = 1 + (rand() % rooms);
  for(i = 0; i < num; i++){
    if(treasure == monsters[i]){
      treasure = 1 + (rand() % rooms);
      i = 0;
    }
  }
  cout << "treasure" << treasure;
  return 0;
}

int monsterFight(){
  cout << "A monster attacked you from the shadows.";
  cout << "You have 3 chances to defeat the monster. Guess the number between 1-10: ";
  int monster = 1 + (rand()%10);
  int userValue;
  int i = 1;
  for(i = 1; i <= 3; i++){
    cin >> userValue;
    if (userValue > monster) {
      if(i == 3){
        return 0;
      }
      else{
        cout << "Go lower....\n";
        cout << "Guess the number: ";
      }
    }
    else if (userValue < monster) {
      if (i == 3){
        return 0;
      }
      else{
        cout << "Go higher....\n";
        cout << "Guess the number: ";
      }
    }
    else{
      cout << "You killed the monster. Nice.";
      return 1;
      break;
    }
  }

  return 1;
}

int main() {
  playerDetails p1;
  int difficulty, enemies;
  tryagain:
  cout << "------------------------------------\n";
  cout << "DIFFICULTIES\nEnter 1 for easy difficulty (has 50 rooms and 5 monsters)\nEnter 2 for medium difficulty (has 100 rooms and 10 monsters)\nEnter 3 for hard difficulty (has 100 rooms and 20 monsters)\nWhat difficulty do you want to play on: ";
  cin >> difficulty;
  switch (difficulty) {
    case 1:
      generateWorld(50, 5);
      enemies = 5;
      break;
    case 2:
      generateWorld(100, 10);
      enemies = 10;
      break;
    case 3:
      generateWorld(100, 20);
      enemies = 20;
      break;
    default:
      cout << "Wrong Input\n";
      goto tryagain;
  }
  cout << "Generating World.";
  Sleep(200);
  cout << ".";
  Sleep(200);
  cout << ".";
  Sleep(200);
  cout << ".";
  Sleep(200);
  cout << ".";
  Sleep(100);
  cout << "DONE";
  int roomsVisited[100];
  int alive = 1, choice, i, tries = 0;
  while(alive){
    int visited = 0;
    cout << "\n------------------------------------\n";
    cout << "Which room do you want to explore: ";
    cin >> choice;
    if(difficulty == 1 && choice > 50){
      cout << "This room does not exist";
      continue;
    }
    if((difficulty == 2 || difficulty == 3) && choice > 100){
      cout << "This room does not exist";
      continue;
    }
    for(i = 0; i < tries; i++){
      if(choice == roomsVisited[i]){
        cout << "You already visited this room. It is empty.";
        visited = 1;
      }
    }
    if(visited == 1){
      continue;
    }
    if(choice == treasure){
      p1.won();
      break;
    }
    else{
      int monsterFound = 0;
      for(i = 0; i < enemies; i++){
        if(choice == monsters[i]){
          alive = monsterFight();
          monsterFound = 1;
        }
      }
      if(monsterFound == 0){
        cout << "The room is empty.....";
      }
    }
    if(alive == 0){
      cout << "----------------------\n";
      cout << "THE MONSTER KILLED YOU\n----------------------\nBetter luck next time...";
    }
    roomsVisited[tries] = choice;
    tries++;
  }
  return 0;
}
