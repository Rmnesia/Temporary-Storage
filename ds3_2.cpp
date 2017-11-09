#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int Size = 100;

struct User {
  string name;
  string phone;
  string address;
  User *link;
};

class HashTable {
private:
  User **htn;
  User **htp;
  User *FindByName(string n);
  User *FindByPhone(string n);
public:
  HashTable(){ htn = new User*[Size]; htp = new User*[Size];}
  bool Insert(string _name, string _phone, string _address);
  void ShowByName(string n);
  void ShowByPhone(string n);
};

User *HashTable::FindByName(string n){
  int h = 0;
  for(int i=0; i<n.length(); i++) h += n[i] % 10;
  User *p = htn[h];
  while(p != NULL && p->name != n) p = p->link;
  return p;
}

User *HashTable::FindByPhone(string n){
  int h = 0;
  for(int i=0; i<n.length(); i++) h += n[i] % 10;
  User *p = htp[h];
  while(p != NULL && p->phone != n) p = p->link;
  return p;
}

bool HashTable::Insert(string _name, string _phone, string _address){
  int h = 0;
  for(int i=0; i<_phone.length(); i++) h += _phone[i] % 10;
  User *temp = htp[h];
  if(!temp){
    h = 0;
    for(int i=0; i<_name.length(); i++) h += _name[i] % 10;
    User *pn = htn[h];
    while(pn != NULL && pn->name != _name) pn = pn->link;
    pn = new User();
    pn->name = _name;
    pn->phone = _phone;
    pn->address = _address;
    htn[h] = pn;
    h = 0;
    for(int i=0; i<_phone.length(); i++) h += _phone[i] % 10;
    User *pp = htp[h];
    while(pp != NULL && pp->phone != _phone) pp = pp->link;
    pp = new User();
    pp->name = _name;
    pp->phone = _phone;
    pp->address = _address;
    htp[h] = pp;
    return true;
  }
  return false;
}

void HashTable::ShowByName(string n){
  User *p = FindByName(n);
  if(p == NULL){
    cout<<"Can't find "<<n<<endl;
    return;
  }
  cout<<p->name<<' '<<p->phone<<' '<<p->address<<endl;
}

void HashTable::ShowByPhone(string n){
  User *p = FindByPhone(n);
  if(p == NULL){
    cout<<"Can't find "<<n<<endl;
    return;
  }
  cout<<p->name<<' '<<p->phone<<' '<<p->address<<endl;
}

int main(){
  ifstream file ("test");
  HashTable Table;
  string _name, _phone, _address;
  while (!file.eof()) {
    file>>_name>>_phone>>_address;
    Table.Insert(_name, _phone, _address);
  }
  file.close();
  while(1){
    cout<<'\n'<<'\n';
    cout<<"********************************"<<endl;
    cout<<"%        Telephone System      %"<<endl;
    cout<<"********************************"<<endl;
    cout<<endl;
    cout<<"         What do you want       "<<endl;
    cout<<endl;
    cout<<"1. Find an user by name"<<endl;
    cout<<"2. Find an user by phone number"<<endl;
    cout<<"3. Insert an user"<<endl;
    cout<<"4. Show All the Users"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<'\n'<<'\n'<<'\n'<<'\n'<<'\n';
    int choice;
    cin>>choice;
    switch (choice){
      case 1:{
        cout<<"Input a name"<<endl;
        string n;
        cin>>n;
        cout<<endl;
        Table.ShowByName(n);
        break;
      }
      case 2:{
        cout<<"Input a phone number"<<endl;
        string n;
        cin>>n;
        cout<<endl;
        Table.ShowByPhone(n);
        break;
      }
      case 3:{
        ofstream file ("test", ios::app);
        cout<<"Input a name: ";
        cin>>_name;
        cout<<"Input a phone number: ";
        cin>>_phone;
        bool IsNum = true;
        for(int i=0; i<_phone.length(); i++)
          if(_phone[i]<'0' || _phone[i]>'9')IsNum = false;
        if(!IsNum){
          cout<<"Please enter the number"<<endl;
          break;
        }
        cout<<"Input an address: ";
        cin>>_address;
        if(Table.Insert(_name, _phone, _address)){
          cout<<"Insert Succeed"<<endl;
          file<<_name<<' '<<_phone<<' '<<_address<<endl;
        }
        else cout<<"The Phone Number Already exists"<<endl;
        file.close();
        break;
      }
      case 4:{
        ifstream file("test");
        string s;
        cout<<"Name "<<"Phone Number "<<"Address"<<endl;
        while(getline(file, s))
          cout<<s<<endl;
        file.close();
        break;
      }
      case 5:{
        return 0;
      }
    }
  }
  return 0;
}
