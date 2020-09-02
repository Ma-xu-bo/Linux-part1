#include<iostream>
using namespace std;
const float FREEZE_PT = 32.0;
const float BOIL_PT = 212.0;
int main()
{
  float avg;
  cout<<" Water freeze is "<<FREEZE_PT<<endl;
  cout<<" Water boil is "<<BOIL_PT<<endl;
  avg = FREEZE_PT + BOIL_PT;
  avg = avg / 2.0;
  cout<<"Water avg  is "<<avg<<endl;
  return 0;
}
