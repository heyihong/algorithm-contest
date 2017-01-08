#include <message.h>
#include <stdio.h>
#include <vector>
#include "lisp_plus_plus.h"

#define MASTER_NODE 0
#define SENDING_DONE -1
#define LARGE_PRIME 1000000007

using namespace std;

int main() {
  int num_nodes = NumberOfNodes();
  int length = GetLength();
  if (MyNodeId() == MASTER_NODE) {   
    int n = length;
    int l = 0;
    for (int i = 1; i < num_nodes; ++i) {
        PutInt(i, l);
        l += n / (num_nodes - i);
        n -= n / (num_nodes - i);
        PutInt(i, l);
        Send(i);
    }
    vector<int> sum;
    sum.push_back(0);
    for (int i = 1; i < num_nodes; ++i) {
      Receive(i);
      sum.push_back(GetInt(i));
      sum[i] += sum[i - 1];
    }
    for (int i = 1; i < num_nodes; ++i) {
      PutInt(i, sum[i - 1]);
      Send(i);
    }
    int result = -1;
    bool has_negative = false;
    for (int i = 1; i < num_nodes; ++i) {
      Receive(i);
      int negative_pos = GetInt(i);
      //printf("%d %d\n", zero_pos, negative);
      if (!has_negative && negative_pos != -1) {
        result = negative_pos - 1;
        has_negative = true;
      }
    }
    if (result == -1 && sum[num_nodes - 1] != 0) {
      result = length; 
    }
    printf("%d\n", result);
    return 0;
  } else {
    Receive(MASTER_NODE);  
    int left = GetInt(MASTER_NODE);
    int right = GetInt(MASTER_NODE);
    int sum = 0;
    for (int i = left; i < right; ++i) {
        char ch = GetCharacter(i);
        if (ch == '(') {
          ++sum;
        } else {
          --sum; 
        }
    }
    PutInt(MASTER_NODE, sum);
    Send(MASTER_NODE);
    Receive(MASTER_NODE);
    sum = GetInt(MASTER_NODE);
    int negative_pos = -1;
    //printf("%d %d %d\n", sum, left, right);
    for (int i = left; i < right; ++i) {
      char ch = GetCharacter(i);
      //printf("%c\n", ch);
      if (ch == '(') {
        ++sum;
      } else {
        --sum;
      }
      if (sum < 0) {
        negative_pos = i + 1;
        break;
      }
    }
    PutInt(MASTER_NODE, negative_pos);
    Send(MASTER_NODE);
    return 0;
  }
}