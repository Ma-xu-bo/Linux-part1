#include<iostream>
#include<fstream>
using namespace std;
int main(){
  int count;
  char preChar;
  char currChar;
  ifstream inFile;

  inFile.open("myfile.dat");
  if (!inFile){
    cout<<"Can't open input file"<<endl;
    return 1;}
  count = 0;
  inFile.get(preChar);
  inFile.get(currChar);
  while (inFile)
    {
      if (currChar == '=' && preChar == '!')
	count++;
      preChar = currChar;
      inFile.get(currChar);
      
    }
  cout<<count<<"!= operation were found."<<endl;
  return 0;

}

