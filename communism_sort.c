#include <stdio.h>

void print_arr(int arr[], int size){
   for (int i=0; i < size; i++){
    printf("%d\n", arr[i]);
  }
}

void communism_sort(int arr[], int size){
  long long total = 0;

  for (int i=0; i < size; i++){
    total += arr[i];
  }

  int avg = total / size;

  for (int i=0; i < size; i++){
    arr[i] = avg; 
  }
  print_arr(arr, size);
}

int main(){
  int arr[] = {1, 2, 1123, 312, 523, 121, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 6, 1231231, 12, 213, 121, 125, 1}; 
  int size = sizeof(arr) / sizeof(arr[0]);
  communism_sort(arr, size);
}
