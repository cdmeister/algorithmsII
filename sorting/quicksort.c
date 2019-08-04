#include "stdio.h"
#include "math.h"

// https://stackoverflow.com/questions/28068986/quicksort-pivot-position-after-one-partition

int num_swaps1 =0;
int num_swaps2 =0;

void print_array(int list[], int size){
	int k = 0;
	for(;k<size;k++) printf("%d\t", list[k]);
	printf("\n");

}

void exchange(int list[], int a, int b,int * num_counter){
  printf("swapping %d %d\n",list[a],list[b]);
  int temp = list[a];
  list[a] = list[b];
  list[b] = temp;
  ++(*num_counter);
  return;

}

int partition3way(int list[], int left, int right){

  int pivotIndex= left +(right - left)/2;
  int pivot = list[pivotIndex];
  printf("pivot: %d pivotIndex: %d left: %d right: %d\n",pivot,pivotIndex,left,right);
  int i = left, lt=left,gt=right;
  while(i <= gt){
    int temp = list[i];
    printf("temp: %d\n",temp);
    if(temp < pivot){
      printf("temp: %d\ti: %d\tless than\n",temp,i);
      exchange(list,i,lt,&num_swaps2);
      print_array(list,16);
      lt++;
      i++;
    }
    else if(pivot == temp){
      printf("temp: %d\ti: %d\tequal than\n",temp,i);
      i++;
    }
    else if(temp > pivot){
      printf("temp: %d\ti: %d\tgreater than\n",temp,i);
      exchange(list,i,gt,&num_swaps2);
     print_array(list,16);
      --gt;
    }
    printf("lt: %d\ti: %d\tgt:%d\n",lt,i,gt);
  }
  return lt;
}


void quicksort3way(int list[],int left,int right){

  if(left < right){
    int pivot = partition3way(list,left,right);
    quicksort3way(list,left,pivot);
    quicksort3way(list,pivot+1,right);
  }

}


int partition(int list[], int left, int right){

  int pivotIndex= left +(right - left)/2;
  int pivot = list[pivotIndex];
  printf("pivot: %d pivotIndex: %d left: %d right: %d\n",pivot,pivotIndex,left,right);
  int i = left, j=right;
  while(1){

    while(list[i] < pivot){
      i++;
    }

    while(list[j] > pivot){
      j--;
    }
    if (i>=j){printf("i: %d j: %d break\n",i,j); break;}

    exchange(list,i,j,&num_swaps1);
    print_array(list,16);
    j--;
    i++;
  }
  return j;
}


void quicksort(int list[],int left,int right){

  if(left < right){
    int pivot = partition(list,left,right);
    quicksort(list,left,pivot);
    quicksort(list,pivot+1,right);
  }

}

int main(void){

  printf("First Quicksort\n");
  int list[] = {9,5,12,6,3,8,15,1,4,2,7,10,11,13,14,0};
  int size = 16;
  print_array(list,size);
  quicksort(list,0,size-1);
  print_array(list,size);
  printf("Second Quicksort\n");
  int list2[] = {9,5,12,6,3,8,15,1,4,2,7,10,11,13,14,0};
  print_array(list2,size);
  quicksort3way(list2,0,size-1);
  print_array(list2,size);

  printf("Num swaps for quicksort: %d\n",num_swaps1);
  printf("Num swaps for quicksort3way: %d\n",num_swaps2);
  return 0;
}
