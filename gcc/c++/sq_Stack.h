//sq_Stack.h
#include<iostream>
using namespace std;
template<class T>
class sq_Stack
{
private:
  int mm;
  int top;
  T * s;
public:
  sq_Stack(int);
  void prt_sq_Stack();
  int flag_sq_Stack();
  void ins_sq_Stack(T);
  T del_sq_Stack();
  T read_sq_Stack();
};
template<class T>
sq_Stack<T>::sq_Stack(int m)
{
  mm = m;
  s = new T[mm];
  top = 0;
  return;
}
template<class T>
void sq_Stack<T>::prt_sq_Stack()
{
  int i;
  cout<<"top="<<top<<endl;
  for (i=top; i>0; i--) cout<<s[i-1]<<endl;
  return;
}
template<class T>
int sq_Stack<T>::flag_sq_Stack()
{
  if (top==mm) return(-1);
  if (top==0) return(0);
  return(1);
}
template<class T>
void sq_Stack<T>::ins_sq_Stack(T x)
{
  if (top==mm)
    {
      cout<<"Stack overflow!"<<endl; return;
    }
  top = top + 1;
  s[top-1] = x;
  return;
}
template<class T>
T sq_Stack<T>::del_sq_Stack()
{
  T y;
  if (top==0)
    {
      cout<<"Stack underflow!"<<endl; return(0);
    }
  y = s[top-1];
  top = top - 1;
  return (y);
}
template<class T>
T sq_Stack<T>::read_sq_Stack()
{
  if (top==0)
    {
      cout<<"Stack empty!"<<endl; return(0);
      return (s[top-1]);
    }
}
