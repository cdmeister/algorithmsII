#include "stdio.h"

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


void bubble_sort(int list[] ,int size){

  int i,j;
  for(i=0;i<size;i++){
    for(j=0;j<size-i-1;j++){
      printf("j: %d \n",j);
      if(list[j+1] < list [j]) exchange(list,j+1,j);
      else printf("did not swap %d %d\n",list[j+1],list[j]);
      print_array(list,size);
    }

  }
}


int main(void){

  int list[] = {9,5,12,6,3,8,15,1,4,2,7,10,11,13,14,0};
  int size = 16;
  print_array(list,size);
  bubble_sort(list,size);
  print_array(list,size);
  return 0;
}
