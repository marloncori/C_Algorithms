#include <stdio.h>
#include <conio.h>

int* getInput();
int  greater(int, int);
void swap(int*, int*);
void partition(int*, int, int); 
void quickSort(int*, int, int);
void showArray(int*, int);

int main(void){
   int* nums = getInput();

   int mode = 0;
   showArray(nums, mode);

   int n = sizeof(nums) / sizeof(nums[0]);
   quickSort(nums, nums[0], nums[n-1]);

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

int greater(int first, int second){
   if(first > second){
     return 1;
   }
  return -1;
}

void swap(int* first, int* second){
   int temp = first;
   first = second;
   second = temp;
}

void partition(int* arr, int beg, int end){
    int left, right, temp, loc, fla;
    loc = left = beg;
    right = end;
    flag = 0;
    while(flag != 1){
        while((arr[loc] <= arr[right]) && (loc != right)){
            right--;
            if(loc == right){
               flag = 1;
            }
            else if(greater(arr[loc], arr[right]){
                swap(&arr[loc], &arr[right]);
                loc = right;
            }
         }
         if(flag != 1){
            while(arr[loc] >= arr[left]) && (loc != left)){
                left++;
                if(loc == left){
                   flag = 1;
                }
                else if(greater(arr[left], arr[loc])){
                  swap(&arr[loc], &arr[left]);
                  loc = left;
                }
            }
         }
    }
   return loc;   
}

void quickSort(int* arr, int start, int end){
   int loc;
   if(start < end){
      loc = partition(arr, start, end);
      quickSort(arr, start, loc-1);
      quickSort(arr, loc+1, end);
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