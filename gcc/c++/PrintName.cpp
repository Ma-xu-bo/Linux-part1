#include<iostream>
#include<string>
using namespace std;
const string FIRST = "Herman";
const string LAST = "Smith";
const string MIDDLE = "G";

int  main()
{
  string firstlast;
  string lastfirst;
  firstlast = FIRST + " "+LAST;
  cout<<" Name in first-last format is "<<firstlast<<endl;
  lastfirst = LAST + ", "+ FIRST;
  cout<<" Name in lastfirst format is ";
  cout<<lastfirst<<MIDDLE<<" ."<<endl;
  return 0;
}
