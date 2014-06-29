#include "rng.h"
#include <stdlib.h>

void shuffle(int * arr, int length)
{
 int i,j,temp;
 
 for (i=0;i<length;i++)
  {
  j=genrand_int_n(length-i)+i;
  temp=arr[i];
  arr[i]=arr[j];
  arr[j]=temp;
  }
 return;
}






/*Fills arr with random selection of numbers from 0 to y-1*/
void pull_x_out_of_y(int * arr, int x, int y)
{
 int * temparr;
 int i,j;
 temparr=(int*)malloc(y*sizeof(int));
 for (i=0;i<y;i++)
  temparr[i]=i;
 for (i=0;i<x;i++)
  {
   j=genrand_int_n(y-i)+i;   
   arr[i]=temparr[j];
   temparr[j]=temparr[i];
  }
 
 free(temparr);
 return;
}

/*int main()
{
 int test_arr[10];
 int i;
 init_genrand(888);
 pull_x_out_of_y(test_arr,10,20);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
 printf("\n");
 pull_x_out_of_y(test_arr,10,20);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
 printf("\n");
 pull_x_out_of_y(test_arr,10,20);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
 printf("\n");
 pull_x_out_of_y(test_arr,10,20);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
 printf("\n");*/
 /*for (i=0;i<10;i++)
  test_arr[i]=i;
 shuffle(test_arr,10);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
  printf("\n");
  shuffle(test_arr,10);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
  printf("\n");
  shuffle(test_arr,10);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
  printf("\n");
  shuffle(test_arr,10);
 for (i=0;i<10;i++)
  printf("%d ",test_arr[i]);;
  printf("\n");*/
 /*return 0;
}*/