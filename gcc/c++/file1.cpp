#include<iostream>
using namespace std;
void wrt(int n)
{
  if(n!=0)
    {
      wrt(n-1); cout<<n<<endl;
      return;
    }
}
int main()
{
  wrt(10);
  return 0;
}
