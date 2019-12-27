//this code is for demonstration purposes only
//works with a very simple algorithm ... look for a blank square and fill it with an x
//also noticed the player mode  needs to be sent by the marking scheme
#include<bits/stdc++.h>
using namespace std;
void printBoard(vector<string>&arr){
  for(auto a : arr)for(auto b : a)cout<<b;
}
int main(int argc, char *argv[]) {
  //not putting checks
  string temp = argv[1];
  int boardsize = 0;
  for (auto a : temp){
    boardsize*=10;
    boardsize+= a-'0';
  }
  temp = argv[2];
  int towin = 0;
  for (auto a : temp){
    towin*=10;
    towin+=a-'0';
  }
  vector<string>boardrep(boardsize);
  temp = argv[3];
  for(int i = 0; i < boardsize; i++){
    for(int j = 0; j < boardsize; j++){
      boardrep[i].push_back(temp[i*boardsize + j]);
    }
  }
  char toput = argv[4][0];
  for(int i = 0; i < boardsize; i++){
    for(int j = 0; j < boardsize; j++){
      if(boardrep[i][j] == '0'){
        boardrep[i][j] = toput;
        printBoard(boardrep);
        return 0;
      }
    }
  }

  return 0;
}
