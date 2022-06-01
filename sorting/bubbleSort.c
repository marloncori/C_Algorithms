#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int* getInput();
int is_greater(int first, int second);
void swap(int* first, int* second);
void bubbleSort(int* arr);
void showArray(int* arr, int mode);

int main(void){
   int* nums = getInput();

   int mode = 0;
   showArray(nums, mode);

   mode = 1;
   bubbleSort(nums);

   showArray(nums, mode);

 getch();
 return 0;
}

int* getInput(){
    int i, n;
    int* arr;
    printf("\n Enter the number of elements in the array.\n");
    printf("\n\t Array size: ");
    scanf("%d", &n);
    printf("\n Now enter the elements of the array to be sorted.\n");
    for(i=0; i<n; i++){
        printf("\t %d. array member: ", (i+1));
        scanf("%d", &arr[i]);
    }
  return arr;
}

int is_greater(int first, int second){
   if(first > second){
     return 1;
   }
   else {
     return -1;
   }
}

void swap(int* first, int* second){
   int temp = *first;
   *first = *second;
   *second = temp;
}

void bubbleSort(int* arr){
   int i, j;
   int size = sizeof(arr) / sizeof(arr[0]);
   for(i=0; i <size; i++){
      for(j=0; j<size-i-1; j++){
          if(is_greater(arr[j], arr[j+1])){
              swap(&arr[j], &arr[j+1]);
          }
      } 
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
   int i;
   printf("\n This is the %s array of numbers: \n {", msg);
   for(i=0; i<n; i++){
      printf("%d ", arr[i]);
   }
   printf("}\n");
}
