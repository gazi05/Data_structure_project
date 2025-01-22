#include <iostream>
#define max_size 5 
using namespace std;

int main(){
 int arr[max_size] = { 1 , 2 , 3 , 4 , 5};
  int low = 0 ;
  int high = max_size - 1;
  int target = 77;
  int found = 0;
  while(found == 0 && low <= high)
  {
    int mid = (low + high) / 2;
    if(target == arr[mid]){
      found = 1;
    }
    else if(arr[mid] > target)
    {
      high = mid - 1;
    }
    else 
      low = mid + 1; 
  }
  if(found)
  {
    cout << "found";
  }
  else cout << "not found";
}