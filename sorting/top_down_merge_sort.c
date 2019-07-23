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

// Merge function to actually sort the array
// create auxilliary array to store value
// temporary
void merge(int list[], int lo,int mid,int hi){

  printf("%s %d %d %d\n",__FUNCTION__,lo,mid,hi);

  int left_num = mid - lo+1;
  int right_num = hi - mid;

  printf("left_num: %d\n",left_num);
  printf("right_num: %d\n",right_num);
  int left_aux[left_num];
  int right_aux[right_num];

  // Copy values into auxililary left and right array
  int i;
  for(i=0;i<left_num;i++) left_aux[i] = list[i+lo];
  for(i=0;i<right_num;i++) right_aux[i] = list[i+mid+1];
  print_array(left_aux,left_num);
  print_array(right_aux,right_num);


  int j = 0, k=0,f=lo;
  while(j<left_num && k<right_num){

    // compare values
    if(left_aux[j] < right_aux[k]) list[f] = left_aux[j++];
    else if(right_aux[k] < left_aux[j]) list[f] = right_aux[k++];
    f++;

  }

  // At this point one of the half still have values to backfill if the
  // number of item is odd.
  while(j<left_num) list[f++] = left_aux[j++];
  while(k<right_num) list[f++] = right_aux[k++];


}


void top_down_merge_sort(int list[], int lo,int hi){

  //Base case if low>=high signifies only one element
  printf("%s %d %d\n",__FUNCTION__,lo,hi);
  if (lo>=hi) return;
  // Calculate mid index
  int mid = lo + (hi - lo)/2;

  // Call mergesort on left half
  top_down_merge_sort(list,lo,mid);

  // Call mergesort on right half
  top_down_merge_sort(list,mid+1,hi);


  // merge
  merge(list,lo,mid,hi);
}


int main(void){

  int list[] = {9,5,12,6,3,8,15,1,4,2,7,10,11,13,14};
  int size = 15;
  print_array(list,size);
  top_down_merge_sort(list,0,size-1);
  print_array(list,size);
  return 0;
}
