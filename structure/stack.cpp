#include <iostream>

using namespace std;

struct Node
{
  int item ;
  Node *next;
};Node *top = nullptr;

Node* push(int val)
{
  Node* new_node = new Node();
  new_node->item = val;
  new_node->next = top;
  top = new_node;
}
void pop()
{
  if(top == nullptr)
  {
    cout << "the stack is empty" << endl;
  }
  else{
    Node* current = top ;
    top = top->next ;
    cout << current->item << endl; 
    delete current;
  }
}
int main()
{
  push(50);
  push(20);
  push(10);
  push(5);
  push(1);
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();

}