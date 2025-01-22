#include <iostream>
#define max_size 5
using namespace std;

void insertionSort(int arr[], int size)
{
 for(int i = 1; i< size ; i++)
 {
  int key = arr[i];
  int j = i - 1;
  while(j >= 0 && arr[j] > key)
  {
    arr[j+1] = arr[j];
    j--;
  }
  arr[j+1] = key;
 }
}

int main()
{
 int arr[max_size]= {5 , 3 , 4 ,2 ,1 };
 insertionSort(arr, max_size);
 for(int i = 0 ; i< max_size ; i++)
 {
  cout << arr[i] << endl;
 }
}