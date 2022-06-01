#include <stdio.h>
#include <conio.h>
#define MAX_SIZE 100

int* getInput();
void merge(int*, int, int, int); 
void mergeSort(int*, int, int);
void showArray(int*, int);

int main(void){
   int* nums = getInput();

   int mode = 0;
   showArray(nums, mode);

   int n = sizeof(nums) / sizeof(nums[0]);
   mergeSort(nums, nums[0], nums[n-1]);

   mode = 1;
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

void merge(int* arr, int beg, int mid, int end){
   int i = beg, j = mid+1;
   int index = beg, temp[MAX_SIZE], k;
   while((i <= mid) && (j <= end)){
      if(arr[i] < arr[j]){
          temp[index] = arr[i];
          i++;
      }
      else {
          temp[index] = arr[j];
          j++;
      }
      index++; 
   }
   if(i > mid){
      while(j <= end){
          temp[index] = arr[j];
          j++;
          index++;
      }
   }
   else {
      while(i <= mid){
          temp[index] = arr[i];
          i++;
          index++;
      }
   }
   for(k = beg; k < index; k++){
      arr[k] = temp[k];
   }
}

void mergeSort(int* arr, int start, int end){
   int mid;
   if(start < end){
      mid = (start + end) / 2;
      mergeSort(arr, start, mid);
      mergeSort(arr, mid+1, end);
      merge(arr, start, mid, end);
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
