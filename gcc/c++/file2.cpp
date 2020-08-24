#include<iostream>
using namespace std;
  int a;
int i;
int wrt(int n)
{
  if (n==1)
    a=1;
  else
    for(i=0;i<n;i++)
      a=wrt(n-1) * n;
  return a;
  }
int main()
{
  int n;
  cin>>n;
  wrt(n);
  cout<<"wrt(n)"<< a <<endl;
}
