#include "stdio.h"

void print_array(int list[], int size){
	int k = 0;
	for(;k<size;k++) printf("%d\t", list[k]);
	printf("\n");

}


void exchange(int list[], int a, int min){

  int temp = list[a];
  list[a] = list[min];
  list[min] = temp;
  return;

}

void insertion_sort(int list[], int size){

  int i,j;
  for(i=1;i<size;i++){


    for(j=i;j>0;j--){

      // the number ripples down to its spot
      if( list[j] < list[j-1]) exchange(list,j-1,j);
      print_array(list,size);
    }

  }


}


int main(void){

  int list[] = {9,5,6,3,8,0,1,4,2,7};
  int size = 10;
  print_array(list,size);
  insertion_sort(list,10);

  print_array(list,size);
  return 0;
}
