#include <iostream>
#define max_size 5
using namespace std;
struct Node
{
  int key;
  string val;
  Node* next;
};
Node* hash_table[max_size] = {nullptr};

int hash_function(int key)
{
  return key % max_size;
}

void insert(int key, string data)
{
  int index = hash_function(key);
  Node* newNode = new Node();
  newNode->key = key;
  newNode->val = data;
  newNode->next = nullptr;
  if(hash_table[index] == nullptr)
  {
    hash_table[index] = newNode;
  }
  else
  {
    Node* temp = hash_table[index];
    while(temp->next != nullptr)
    {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void print()
{
  for(int i = 0; i < max_size; i++)
  {
    Node* temp = hash_table[i];
    while(temp != nullptr)
    {
      cout << temp->val << endl;
      temp = temp->next;
    }
  }
}

int main()
{
  insert(202311259, "ghazi");
  insert(202311252, "noor");
  insert(202311257, "rayan");
  insert(202311253, "lujuin");
  insert(202311211, "maher");
  print();
}