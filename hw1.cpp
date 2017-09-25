#include<iostream>
using namespace std;

int main() {
  float x; cin >> x;
  cout <<hex<< (int&)x << endl;
  return 0;
}
