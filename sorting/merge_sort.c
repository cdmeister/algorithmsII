#include "stdio.h"
#include "math.h"


void print_array(int list[], int size){
	int k = 0;
	for(;k<size;k++) printf("%d\t", list[k]);
	printf("\n");

}

void exchange(int list[], int a, int min){
  printf("swapping %d %d\n",list[a],list[min]);
  int temp = list[a];
  list[a] = list[min];
  list[min] = temp;
  return;

}

void merge_sort(int list[], int low,int hi){



}


int main(void){

  int list[] = {9,5,12,6,3,8,15,1,4,2,7,10,11,13,16,0};
  int size = 16;
  print_array(list,size);
  merge_sort(list,lo,size-1);

  print_array(list,size);
  return 0;
}
