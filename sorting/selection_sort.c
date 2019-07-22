#include "stdio.h"


void exchange(int list[], int a, int min){

  int temp = list[a];
  list[a] = list[min];
  list[min] = temp;
  return;

}

void selection_sort(int list[], int size){

  int i,j;
  for(i=0;i<size;i++){

    int min = i;

    for(j=i+1;j<size;j++){

      // Find the most minimum item in list
      // if list[j] < list[min] aka ur current mimimum;
      if( list[j] < list[min]) min = j;
    }
    exchange(list,i,min);

  }


}


void print_array(int list[], int size){
	int k = 0;
	for(;k<size;k++) printf("%d\t", list[k]);
	printf("\n");

}

int main(void){

  int list[] = {9,5,6,3,8,0,1,4,2,7};
  int size = 10;
  print_array(list,size);
  selection_sort(list,10);

  print_array(list,size);
  return 0;
}
