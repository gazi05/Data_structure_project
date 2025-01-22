#include <iostream>

using namespace std;
struct tree
{
  int data;
  tree* left;
  tree* right;
}; tree* root = nullptr;

tree* insert(tree* root ,int val){
  if(root == nullptr){
    root = new tree();
    root->data = val;
    root->left = root->right = nullptr;
  }
  else if(val <= root->data)
    root->left = insert(root-> left , val);
  else
    root->right = insert(root->right , val);
  
  return root;
}

int main()
{
 
  insert(root , 5);
  insert(root , 7);
  cout << root->data << endl;
  cout << root->right->data;
}