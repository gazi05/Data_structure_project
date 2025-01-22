#include <iostream>

using namespace std;

struct Node{
  int item ;
  Node* next;
};Node* front = nullptr;
  Node* rear = nullptr;

void enqueue(int val)
{
  Node* new_node = new Node();
  new_node->item = val;
  new_node->next = nullptr;
  if(front == nullptr)
  {
    front = rear = new_node;
  }
  else{
    rear->next = new_node ;
    rear = new_node;
  }
}
void deqeue()
{
  Node* current = front;
  if(front == nullptr)
  {
    cout << "the queue is empty " << endl;
  }
  else{
    front = front->next;
    cout << current->item << endl;
    delete current;
  }
}
int main()
{
  enqueue(50);
  enqueue(30);
  enqueue(20);
  enqueue(10);
  enqueue(5);
  deqeue();
  deqeue();
  deqeue();
  deqeue();
  deqeue();
  deqeue();
  deqeue();


}