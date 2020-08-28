#include<linked_Stack.h>
int main()
{
  linked_Stack<int>s;
  s.ins_linked_Stack(50);
  s.ins_linked_Stack(60);
  s.ins_linked_Stack(70);
  s.ins_linked_Stack(80);
  s.ins_linked_Stack(90);
  s.ins_linked_Stack(100);
  cout<<"输出栈中的元素："<<endl;
  s.prt_linked_Stack();
  if (s.flag_linked_Stack())
    cout<<"栈顶元素："<<s.read_linked_Stack()<<endl;
  if (s.flag_linked_Stack())
    cout<<"退栈元素："<<s.del_linked_Stack()<<endl;
  if (s.flag_linked_Stack())
    cout<<"退栈元素："<<s.del_linked_Stack()<<endl;
  if (s.flag_linked_Stack())
    cout<<"退栈元素："<<s.del_linked_Stack()<<endl;
  cout<<"再次输出栈中的元素："<<endl;
  s.prt_linked_Stack();
  return 0;
}
