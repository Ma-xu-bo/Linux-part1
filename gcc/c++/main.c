/*  main.c */
#include<stdio.h>
#include<add.h>
#include<sub.h>
int main(void)
{
  int a=10,b=12;
  float x=1.23, y=2.53;
  printf("int a+b IS:%d\n", add_int(a,b));
  printf("int a-b IS:%d\n", sub_int(a,b));
  printf("float a+b IS :%f\n", add_float(a,b));
  printf("float a-b IS :%f\n", sub_float(a,b));
  return 0;
  
}
