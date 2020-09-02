#include<iostream>
using namespace std;
int Squire(int n)
{
  return n * n;
}
int Cube(int n)
{
  return n * n *n;
}

int  main()
{
  std:: cout<<"The squire of 27 is "<<Squire(27)<<std::endl;
  std::cout<<"and the cube of 27 is "<<Cube(27)<<std::endl;
  
  return 0;
}

