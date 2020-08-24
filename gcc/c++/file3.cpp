#include<iostream>
using namespace std;
int main(){
  int max;
  int a[10];
  int i;
  for(i=0;i<10;i++)
      cin>>a[i];
  cout<<a[i]<<endl;
  max=a[0];
  for (i=0;i<10;i++)
    if(max<a[i])
    max = a[i];
  return max;
}

  
  
	    
