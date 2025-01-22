#include <iostream>
#define max_size 5
using namespace std;

int main()
{
  int array[max_size] = {5 , 3 , 4 , 2 , 1};
  int i = 0 , sorted = 0  ;
  while(i < max_size && sorted == 0)
  {
    sorted = 1 ;
    for (int j = 0 ; j < max_size-1; j++)
    {
      if(array[j] > array[j+1])
      {
        int temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp ;
        sorted = 0 ;
      }
    }i++;
  }
  for(int i = 0 ; i< max_size ; i++)
  {
    cout << array[i] << endl;
  }
}
