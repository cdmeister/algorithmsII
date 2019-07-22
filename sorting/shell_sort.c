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

void shell_sort(int list[], int size){


  // Gap size calculation
  // Pick a big size gap based on input size
  // Wikipedia: Papernov & Stasevich, 1965
  // Use 2^k+1 as your gap sequence
  // 1,3,5,9,17,33,...
  // SO: To perform a shellsort, you compute the gap sequence, sometimes
  // called the increment sequence, using i starting at 1 and incrementing it
  // until it's large enough to sensibly start sorting (Sedgewick suggests that
  // when you get the largest gap sequence less than N/3).

  // Then you shellsort starting with the largest gap down to 1.
  int n = size;
  int h = 1;
  int i =1;
  printf("h: %d\t",h);
  while (i< n/3){
    h = pow(2,i) + 1;
    printf("%d %d\t",h,i);
    i++;
  }
  if(h > n) i-=2; h = pow(2,i)+1;

  printf("h: %d i: %d \n", h,i);
  int j,k;
  while(h>=1){
    for(j = h; j<n;j++){
      for(k=j;k>=h;k-=h){

        // Find the most minimum item in list
        // if list[j] < list[min] aka ur current mimimum;
        if( list[k] < list[k-h])  exchange(list,k,k-h);
      }
    }
    print_array(list,size);

  if(h>3) h=pow(2,--i)+1;
  else if (h == 3) h = 1;
  else h = 0;
    printf("h is now %d\n",h);
  }


}


int main(void){

  int list[] = {9,5,12,6,3,8,15,1,4,2,7,10,11,13,16,0};
  int size = 16;
  print_array(list,size);
  shell_sort(list,size);

  print_array(list,size);
  return 0;
}
