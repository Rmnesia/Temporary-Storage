#include<iostream>
#include<string>
#include<sstream>
using namespace std;

struct NumNode
{
  int data;
  int carry;
  NumNode *link;
  NumNode(){data = 0; carry = 0; link=NULL;}
};

class NumList{
private:
  NumNode *first;
  int num;
public:
  NumList(){num = 0; first = new NumNode;}
  NumList(int n){num = n; first = new NumNode;}
  string Factorial();
  string Format(NumNode *current);
};

string NumList::Factorial(){
  NumNode *current;
  current = first;
  current->data = 2;
  for(int i=3; i<=num; i++){
    current = first;
    while (1) {
      current->data = current->data * i + current->carry;
      current->carry = 0;
      if(current->data/1000 != 0){
        if(current->link == NULL) current->link = new NumNode;
        current->link->carry = current->data / 1000;
        current->data = current->data % 1000;
      }
      if(current->link == NULL)break;
      current = current->link;
    }
  }
  return Format(first);
}

string NumList::Format(NumNode *current){
  ostringstream stream;
  stream<<current->data;
  string temp;
  if(current->link == NULL)return stream.str();
  if(current->data < 10 )temp = "00"+stream.str();
  else if(current->data < 100)temp = "0"+stream.str();
  else temp = stream.str();
  return Format(current->link)+temp;
}

int main()
{
  int n;
  cout<<"Input a number:";
  cin>>n;
  NumList a(n);
  cout<<a.Factorial()<<endl;
  return 0;
}

