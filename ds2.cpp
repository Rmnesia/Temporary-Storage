#include<iostream>
using namespace std;

struct LinkNode{
  char data;
  LinkNode *link;
  LinkNode(char x, LinkNode *ptr){data = x, link = ptr;}
};

class Stack{
private:
  LinkNode *top;
public:
  Stack(){top = NULL;}
  bool IsEmpty()const{return (top==NULL)?true:false;}
  void Push(const char& x);
  bool Pop(char& x);
  bool getTop(char &x)const;
};

void Stack::Push(const char& x){
  top = new LinkNode(x, top);
}

bool Stack::Pop(char &x){
  if(IsEmpty()==true) return false;
  LinkNode *ptr = top;
  top = top->link;
  x = ptr->data;
  delete ptr;
  return true;
}

bool Stack::getTop(char &x)const {
  if(IsEmpty()==true) return false;
  x = top->data;
  return true;
}

int isp(char op){
  switch(op){
  case ';':return 0;
  case '(':return 1;
  case '*':
  case '/':return 5;
  case '+':
  case '-':return 3;
  case ')':return 6;
  }
}
int icp(char op){
  switch(op){
  case ';':return 0;
  case '(':return 6;
  case '*':
  case '/':return 4;
  case '+':
  case '-':return 2;
  case ')':return 1;
  }
}

void postfix(){
  Stack s;
  Stack pair;
  char ch=';', ch1, op, check, temp;
  s.Push(ch);
  cin.get(ch);
  while(s.IsEmpty()==false && ch != ';'){
    if(ch=='('){
      pair.Push(ch);
    }
    if(ch==')'){
      if (pair.IsEmpty()==true && temp != '0'){
        cerr<<"pair not matched";
        return;
      }
      pair.Pop(temp);
    }
    if((ch<=90 && ch>=65)||(ch<=122 && ch>=97)){
      if(check<=90 && check>=65){cerr<<"two number combined";return;};
      cout<<ch;
      check = ch;
      cin.get(ch);
    }
    else{
      s.getTop(ch1);
      if(isp(ch1) < icp(ch)){s.Push(ch); check=ch; cin.get(ch);}
      else if(isp(ch1) > icp(ch)){s.Pop(op); check=ch; cout<<op; temp='0';}
      else {
        s.Pop(op);
        check = ch;
        if(op=='(') cin.get(ch);
      }
    }
  }
  if(pair.IsEmpty()==false)cerr<<"pair not matched";
}

int main(){
  cout<<"input an expression"<<endl;
  postfix();
  cout<<endl;
  return 0;
}
