#include<iostream>
#include<string>
using namespace std;

struct BinNode{
  char data;
  BinNode *leftChild, *rightChild;
};

class BinaryTree{
protected:
  BinNode *root;
  void inOrderPrint(BinNode *subTree);
  void preOrderPrint(BinNode *subTree);
  void postOrderPrint(BinNode *subTree);
  void print(BinNode *subTree, int n);
  BinNode *build(string pre, string in);
  friend ostream& operator<<(ostream& out, BinaryTree& Tree);
public:
  BinaryTree(){root = NULL;};
  void Create(string pre, string in);
  void Print(){print(root, 0);}
  void InOrderPrint(){inOrderPrint(root);}
  void PreOrderPrint(){preOrderPrint(root);}
  void PostOrderPrint(){postOrderPrint(root);}
};

void BinaryTree::inOrderPrint(BinNode *subTree){
  if(subTree != NULL){
    inOrderPrint(subTree->leftChild);
    cout<<subTree->data;
    inOrderPrint(subTree->rightChild);
  }
}

void BinaryTree::preOrderPrint(BinNode *subTree){
  if(subTree != NULL){
    cout<<subTree->data;
    preOrderPrint(subTree->leftChild);
    preOrderPrint(subTree->rightChild);
  }
}

void BinaryTree::postOrderPrint(BinNode *subTree){
  if(subTree != NULL){
    postOrderPrint(subTree->leftChild);
    postOrderPrint(subTree->rightChild);
    cout<<subTree->data;
  }
}

void BinaryTree::print(BinNode *subTree, int n){
  if (subTree == NULL) return;
  print(subTree->rightChild, n+1);
  for(int i=0; i<n; i++)cout<<"   ";
  cout<<"***"<<subTree->data<<endl;
  print(subTree->leftChild, n+1);
}

ostream& operator<<(ostream& out, BinaryTree& Tree){
  Tree.Print();
}

void BinaryTree::Create(string pre, string in){
  int pos = in.find(pre[0]);
  root = new BinNode;
  root->data = pre[0];
  if(pre.length()==1)return;
  root->leftChild = build(pre.substr(1, pos),
                          in.substr(0, pos));
  root->rightChild = build(pre.substr(pos+1,pre.length()-pos-1),
                           in.substr(pos+1, in.length()-pos-1));
}

BinNode *BinaryTree::build(string pre, string in){
  BinNode *temp;
  temp = new BinNode;
  if (pre.length() == 0)return NULL;
  if (pre.length() == 1){
    temp->data = pre[0];
    return temp;
  }
  int pos = in.find(pre[0]);
  temp->data = pre[0];
  temp->leftChild = build(pre.substr(1, pos),
                          in.substr(0, pos));
  temp->rightChild = build(pre.substr(pos+1, pre.length()-pos-1),
                           in.substr(pos+1, in.length()-pos-1));
  return temp;
}

int main(){
  string pre, in;
  cout << "please input the pre-order string"<<endl;
  cin >> pre;
  cout << "please input the in-order string"<<endl;
  cin >> in;
  BinaryTree tree;
  tree.Create(pre, in);
  cout<<endl;
  tree.PreOrderPrint();
  cout<<endl;
  tree.InOrderPrint();
  cout<<endl;
  tree.PostOrderPrint();
  cout<<endl;
  cout<<tree<<endl;
  return 0;
}
