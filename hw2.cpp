#include<iostream>
using namespace std;

int main() {
  int x, i, j; cin >> x;
  for (int y=x     ; y; y/=10) i=(i+y%10)%2;
  for (int y=i+x*10; y; y/=10) j=(j+y%10)%2;
  cout << x << i << ' ' << j << endl;
  return 0;
}
