#include <message.h>
#include <stdio.h>
#include <vector>
#include "again.h"

using namespace std;

#define MASTER_NODE 0
#define SENDING_DONE -1
#define LARGE_PRIME 1000000007

int main() {
  int num_nodes = NumberOfNodes();
  int n = GetN();
  if (MyNodeId() == MASTER_NODE) {
    vector<int> psa;
    vector<int> psb;
    long long sumA = 0;
    long long sumB = 0;
    for (int i = 0; i < num_nodes; ++i) {
      int node = i % (num_nodes - 1) + 1;
      PutInt(node, i);
      Send(node);
    }
    for (int i = 0; i < num_nodes; ++i) {
      int node = i % (num_nodes - 1) + 1;
      Receive(node);
      psa.push_back(GetInt(node));
      psb.push_back(GetInt(node));
      sumA = (sumA + psa.back()) % LARGE_PRIME;
      sumB = (sumB + psb.back()) % LARGE_PRIME;
    }
    for (int i = 1; i < num_nodes; ++i) {
      PutInt(i, SENDING_DONE);
      Send(i);       
    }
    long long result = sumA * sumB % LARGE_PRIME;
    for (int i = 0; i != num_nodes; ++i) {
      result = (result - (long long)psa[i] * psb[(num_nodes - i) % num_nodes]) % LARGE_PRIME;
    }
    if (result < 0) {
      result += LARGE_PRIME;
    }
    printf("%lld\n", result);
    return 0;
  } else {
    while (true) {
      Receive(MASTER_NODE);
      int start = GetInt(MASTER_NODE);
      if (start == SENDING_DONE) {
        break;
      }
      int part_sum_a = 0;
      int part_sum_b = 0;
      for (int i = start; i < n; i += num_nodes) {
          part_sum_a = (part_sum_a + GetA(i)) % LARGE_PRIME;
          part_sum_b = (part_sum_b + GetB(i)) % LARGE_PRIME;
      }
      PutInt(MASTER_NODE, part_sum_a);
      PutInt(MASTER_NODE, part_sum_b);
      Send(MASTER_NODE);
    }
  }
  return 0;
}