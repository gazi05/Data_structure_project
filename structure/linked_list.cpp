#include <iostream>

using namespace std;

struct Node
{
  int item;
  Node *next;
}; Node* head = nullptr;

Node* insert()
{
  Node *current = nullptr;
  for(int i = 1; i <= 5; i++)
  {
    if(current == nullptr)
    {
      current = new Node();
      head = current;
    }
    else
    {
      current->next = new Node();
      current = current->next;
    }
    current->item = 2 * i - 1;
  }
  return head;
}

void print()
{
  Node* p = head;
  while(p != nullptr)
  {
    cout << p->item << endl;
    p = p->next;
  }
}

int main()
{
  insert();
  print();
}