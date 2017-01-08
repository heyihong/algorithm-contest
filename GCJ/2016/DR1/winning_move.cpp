#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_map>
#include "winning_move.h"

using namespace std;

int main() {
  int n = GetNumPlayers();
  int nodes = NumberOfNodes();
  int my_id = MyNodeId();
  if (my_id == 0) {
    int l = 0;
    for (int i = 1; i != nodes; ++i) {
      PutInt(i, l);
      l += n / (nodes - i);
      PutInt(i, l - 1);
      Send(i);
      n -= n / (nodes - i);
    }
    long long res = 0;
    for (int i = 1; i != nodes; ++i) {
      Receive(i); 
      long long tmp = GetLL(i);
      if (tmp) {
        if (!res || res > tmp) {
          res = tmp;
        } 
      }
    }
    printf("%lld\n", res);
  } else {
    Receive(0); 
    int left = GetInt(0);
    int right = GetInt(0);
    //printf("%d %d\n", left, right);
    unordered_map<long long, int> um;
    for (int i = left; i <= right; ++i) {
      long long num = GetSubmission(i); 
      um[num] += 1;
    }
    vector<vector<pair<long long, int>>> numbers = vector<vector<pair<long long, int>>>(nodes - 1);
    hash<long long> ll_hash;
    for (auto p : um) {
      numbers[ll_hash(p.first) % (nodes - 1)].push_back(p);
    }
    for (int i = 1; i != nodes; ++i) {
      PutInt(i, numbers[i - 1].size());
      for (auto p : numbers[i - 1]) {
        //printf("Send to %d, %d %lld %d\n", i, my_id, p.first, p.second);
        PutLL(i, p.first);
        PutInt(i, p.second);
      }
      Send(i);
    }
    um.clear();
    for (int i = 1; i != nodes; ++i) {
      int from = Receive(-1);
      int total = GetInt(from);
      for (int j = 0; j != total; ++j) {
        long long num = GetLL(from);
        int cnt = GetInt(from);
        //printf("Receive from %d, %d %lld %d\n", from, my_id, num, cnt);
        um[num] += cnt; 
      }
    } 
    long long res = 0;
    for (auto p : um) {
      if (p.second == 1 && (!res || res > p.first)) {
        res = p.first;
      }
    }
    PutLL(0, res);
    Send(0);
  }
  return 0;
}