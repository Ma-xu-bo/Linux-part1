#include<sq_Stack.h>
int main()
{
  sq_Stack<int>s(10);
  s.ins_sq_Stack(50);
  s.ins_sq_Stack(60);
  s.ins_sq_Stack(70);
  s.ins_sq_Stack(80);
  s.ins_sq_Stack(90);
  s.ins_sq_Stack(100);
  cout<<"输出栈顶指针与栈中元素："<<endl;
  s.prt_sq_Stack();
  cout<<"输出栈顶元素："<<s.read_sq_Stack()<<endl;
  cout<<"输出退栈元素："<<endl;
  cout<<s.del_sq_Stack()<<endl;
  cout<<s.del_sq_Stack()<<endl;
  cout<<s.del_sq_Stack()<<endl;
  cout<<"再次输出栈顶指针与栈中元素："<<endl;
  s.prt_sq_Stack();
  return 0;
}
