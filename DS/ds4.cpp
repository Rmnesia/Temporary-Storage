#include<string>
#include<fstream>
#include<iostream>
#include<string>
#include<stdlib.h>

const int MAXROW = 256;
const int MAXCOL = 256;
#define max(x,y) (x)>(y)?(x):(y)
#define no 0
#define left 1
#define down 2
#define right 3
#define up 4

using namespace std;

struct Pos{
  int x;
  int y;
};

class GraphMat{
protected:
  char mat[MAXROW][MAXCOL];
  Pos begin;
  int row;
  int col;
  int blackcount;
  int maxblack;
  int getNeighbor(Pos curr, int neighbor);
  void DFS(Pos curr, bool visited[MAXROW][MAXCOL]);
public:
  GraphMat(int x, int y):row(x),col(y),blackcount(-1),maxblack(-1){}
  void AddRow(string rowstring, int rownum);
  int getValOfblack();
};

int GraphMat::getNeighbor(Pos curr, int neighbor){
  for(neighbor++; neighbor != 5; neighbor++){
    if(neighbor==left && curr.y!=0){
      if(mat[curr.x][curr.y-1]=='*')continue;
      return left;
    }
    if(neighbor==down && curr.x!=row-1){
      if(mat[curr.x+1][curr.y]=='*')continue;
      return down;
    }
    if(neighbor==right && curr.y!=col-1){
      if(mat[curr.x][curr.y+1]=='*')continue;
      return right;
    }
    if(neighbor==up && curr.x!=0){
      if(mat[curr.x-1][curr.y]=='*')continue;
      return up;
    }
  }
  return neighbor;
}

void GraphMat::AddRow(string rowstring, int rownum){
  for(int i=0; i<col; i++){
    if(rowstring[i]=='@'){
      begin.x=rownum;
      begin.y=i;
    }
    mat[rownum][i]= rowstring[i];
  }
}

int GraphMat::getValOfblack(){
  bool visited[MAXROW][MAXCOL];
  for(int i=0; i<row; i++)
    for(int j=0; j<col; j++)
      visited[i][j]=false;
  DFS(begin, visited);
  return maxblack;
}

void GraphMat::DFS(Pos curr, bool visited[MAXROW][MAXCOL]){
  ofstream out("cal",ios::app);
  out<<curr.x<<' '<<curr.y<<endl;
  blackcount++;
  maxblack = max(blackcount, maxblack);
  Pos temp;
  visited[curr.x][curr.y] = true;
  int w = getNeighbor(curr, no);
  while(w != 5){
    temp = curr;
    switch(w){
    case left:
      if(!visited[temp.x][temp.y-1]){
        temp.y--;
        DFS(temp, visited);
      }
      break;
    case down:
      if(!visited[temp.x+1][temp.y]){
        temp.x++;
        DFS(temp, visited);
      }
      break;
    case right:
      if(!visited[temp.x][temp.y+1]){
        temp.y++;
        DFS(temp, visited);
      }
      break;
    case up:
      if(!visited[temp.x-1][temp.y]){
        temp.x--;
        DFS(temp, visited);
      }
      break;
    }
    out<<curr.x<<' '<<curr.y<<endl;
    w = getNeighbor(curr, w);
  }
  out.close();
  blackcount--;
}

int main(){
  system("rm cal");
  ifstream in("test");
  string temp[MAXROW];
  int x=0,y=0;
  while(!in.eof()){
    in>>temp[x];
    y = temp[x].length();
    x++;
  }
  in.close();
  GraphMat Mat(x, y);
  for(int i=0; i<x; i++)
    Mat.AddRow(temp[i], i);
  cout<<Mat.getValOfblack()<<endl;
  system("python show.py");
  return 0;
}
