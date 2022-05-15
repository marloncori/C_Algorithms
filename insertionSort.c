#include <stdio.h>
#include <conio.h>

int* getInput();
void insertionSort(int* array);
void showArray(int* arr, int mode);

int main(void){
   int* nums = getInput();

   int mode = 0;
   showArray(nums, mode);

   mode = 1;
   insertionSort(nums);

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

void insertionSort(int* array){
   int i, j, temp;
   int size = sizeof(array) / sizeof(array[0]);
   for(i = 1; i < size, i++){
      temp = array[i];
       j = i -  1;
       while(temp < array[j] && (j >= 0)){
           array[j+1] = array[j];
           j--;
       }
       array[j+1] = temp;
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