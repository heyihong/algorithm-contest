#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include "oops.h"

using namespace std;

int main() {
  long long N = GetN();
  long long nodes = NumberOfNodes();
  long long my_id = MyNodeId();

  if (my_id == 0) {
    long long max_num = GetNumber(0);
    long long min_num = GetNumber(0);
    int l = 0;
    for (int node = 1; node < nodes; ++node) {
       Sender sender(node);
       sender.Put(l);
       l += N / (nodes - node);
       sender.Put(l - 1);
       sender.Send();
       N -= N / (nodes - node);
    }
    for (int node = 1; node < nodes; ++node) { 
      Receiver receiver(node);
      receiver.Receive();
      min_num = min(min_num, receiver.Get<long long>());
      max_num = max(max_num, receiver.Get<long long>());
     }
     printf("%lld\n", max_num - min_num);
  } else {
    Receiver receiver(0);
    receiver.Receive();
    int left = receiver.Get<int>();
    int right = receiver.Get<int>();
    //printf("%d %d\n", left, right);
    long long max_num = GetNumber(left);  
    long long min_num = max_num;
    for (int i = left + 1; i <= right; ++i) {
     max_num = max(max_num, GetNumber(i)); 
      min_num = min(min_num, GetNumber(i));
    }
    Sender sender(0);
    sender.Put(max_num);
    sender.Put(min_num);
    sender.Send();
  }
  return 0;
}