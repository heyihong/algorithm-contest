#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "crates.h"

using namespace std;

const int MOD(1000000007);

long long CountTargetSum(int n, long long total_sum, int left) {
    long long aver = total_sum / n;
    long long target_sum;
    if (aver * n + left <= total_sum) {
      target_sum = (aver + 1) * left;
    } else {
      target_sum = total_sum - aver * (n - left); 
    }
    return target_sum;
}

int main() {
  int n = GetNumStacks();
  int nodes = NumberOfNodes();
  int my_id = MyNodeId();
  if (my_id == 0) {
    vector<int> sp;
    int remain = n;
    sp.push_back(0);
    for (int i = 1; i != nodes; ++i) {
      int block = remain / (nodes - i);
      sp.push_back(block); 
      remain -= block;
    }
    for (int i = 1; i != sp.size(); ++i) {
      sp[i] += sp[i - 1];
    }
    // Count sum of all heights
    for (int i = 1; i != nodes; ++i) {
      PutInt(i, sp[i - 1]);  
      PutInt(i, sp[i] - 1);
      Send(i);
    } 
    long long total_sum = 0;     
    vector<long long> sum_of_blocks;
    for (int i = 1; i != nodes; ++i) {
      Receive(i);
      sum_of_blocks.push_back(total_sum);
      total_sum += GetLL(i);
    }
    for (int i = 1; i != nodes; ++i) {
      PutLL(i, sum_of_blocks[i - 1]); 
      PutLL(i, total_sum);
      Send(i);
    }  
    int ans = 0;
    for (int i = 1; i != nodes; ++i) {
      Receive(i);
      ans = (ans + GetInt(i)) % MOD;
    }
    printf("%d\n", ans);
  } else {
    Receive(0); 
    int left = GetInt(0);
    int right = GetInt(0);
    long long sum_block = 0;
    vector<int> heights;
    for (int i = left; i <= right; ++i) {
      int height = GetStackHeight(i + 1);
      sum_block += height;
      heights.push_back(height);
    }
    PutLL(0, sum_block);
    Send(0);
    Receive(0); 
    long long prev_sum = GetLL(0);
    long long total_sum = GetLL(0);
    int result = 0;
    for (int i = 0; i != heights.size(); ++i) {
      long long target_sum = CountTargetSum(n, total_sum, left + i + 1);
      prev_sum += heights[i];
      //printf("%lld %lld\n", prev_sum, target_sum);
      long long inc = target_sum > prev_sum ? target_sum - prev_sum : prev_sum - target_sum;
      result = (result + inc) % MOD;
    }
    PutInt(0, result);
    Send(0);
  }
  return 0;
}