#include<linked_Queue.h>
int main()
{
  linked_Queue<int>q;
  q.ins_linked_Queue(50);
  q.ins_linked_Queue(60);
  q.ins_linked_Queue(70);
  q.ins_linked_Queue(80);
  q.ins_linked_Queue(90);
  q.ins_linked_Queue(100);
  cout<<"输出带队列中的元素："<<endl;
  q.prt_linked_Queue();
  if (q.flag_linked_Queue())
    cout<<"输出退队元素："<<q.del_linked_Queue()<<endl;
  if (q.flag_linked_Queue())
    cout<<"输出退队元素："<<q.del_linked_Queue()<<endl;
  if (q.flag_linked_Queue())
    cout<<"输出退队元素："<<q.del_linked_Queue()<<endl;
  cout<<"再次输出带队列中的元素："<<endl;
  q.prt_linked_Queue();
  return 0;
}
