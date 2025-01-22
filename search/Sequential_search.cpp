#include <iostream>

using namespace std;

int main()
{
  int arr[5] = {1 , 2 ,3 , 4 , 5};
  int target = 7 ;
  bool found  = false;
  int i = 0 ;
  while (!found && i < 5)
  {
    if(target == arr[i])
    {
      found = true;
    }
    i++;
  }
  if(found)
  cout << "found";
  else 
  cout << "not found";

  
}