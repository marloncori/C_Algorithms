#include <stdio.h>
#include <conio.h>

int* getInput();
void swap(int* first, int* second);
int smallest(int* arr, int k, int n);
void selectionSort(int* arr);
void showArray(int* arr, int mode);

int main(void){
   int* nums = getInput();

   int mode = 0;
   showArray(nums, mode);

   mode = 1;
   selectionSort(nums);

   showArray(nums, mode);

 getch();
 return 0;
}

int* getInput(){
    int i, n;
    int* arr;
    clrscr();
    printf("\n Enter the number of elements in the array.\n");
    printf("\n\t Array size: ");
    scanf_s("%d\n", &n);
    printf("\n Now enter the elements of the array to be sorted.\n");
    for(i=0; i<n; i++){
        printf("\t %d. array member: ", (i+1));
        scanf_s("%d\n", &arr[i]);
    }
  return arr;
}

void swap(int* first, int* second){
   int temp = first;
   first = second;
   second = temp;
}

int smallest(int* arr, int k, int n){
   int i, pos = k;
   int small = arr[k];
   for(i = k+1; i < n; i++){
      if(arr[i] < small){
          small = arr[i];
          pos = i;
      }
   }
  return pos;
}

void selectionSort(int* arr){
   int k, pos;
   int size = sizeof(arr) / sizeof(arr[0]);
   for(k = 0; k < size, k++){
       pos = smallest(arr, k, size);
       swap(&arr[k], &arr[pos]);
   }
}

void showArray(int* arr, int mode){
   char* msg;
   int n = sizeof(arr) / sizeof(arr[0]);
   switch(mode){
     case 0: msg = "unsorted"; break;
     case 1: msg = "sorted"; break;
     default: break;  
   }
   printf("\n This is the %s array of numbers: \n {", msg);
   for(int i=0; i<n; i++){
      printf("%d ", arr[i]);
   }
   printf("}\n");
}