#include <message.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "rps.h"

using namespace std;

int compete(vector<int> ids) {
  int t = ids.size();
  //printf("%d\n", t);
  while (t > 1) {
    int new_t = 0;
    for (int i = 0; i != t; i += 2) {
      //printf("%d %d\n", ids[i], ids[i + 1]);
      char p1 = GetFavoriteMove(ids[i]);
      char p2 = GetFavoriteMove(ids[i + 1]);
      if (p1 == p2 || (p1 == 'R' && p2 == 'S')
        || (p1 == 'S' && p2 == 'P') || (p1 == 'P' && p2 == 'R')) {
        ids[new_t++] = ids[i];
      } else {
        ids[new_t++] = ids[i + 1];
      }
    }
    t = new_t;
  }
  return ids[0];
}

int main() {
  int n = GetN();
  int nodes = NumberOfNodes();
  int my_id = MyNodeId();
  vector<int> ids;
  if (my_id == 0) {
      // show in power of 2
      int num_tasks = 0;
      for (; (1 << num_tasks) < nodes && num_tasks < n; ++num_tasks);
      int l = 0;
      int task_size = 1 << (n - num_tasks);
      for (int i = 0; i != (1 << num_tasks); ++i) {
        int node = i % (nodes - 1) + 1;
        PutInt(node, l); 
        l += task_size;
        PutInt(node, l - 1);
        Send(node);
      }
      for (int i = 0; i != (1 << num_tasks); ++i) {
        int node = i % (nodes - 1) + 1;
        Receive(node); 
        ids.push_back(GetInt(node));
      }
      for (int i = 1; i != nodes; ++i) {
        PutInt(i, -1); 
        Send(i);
      }
      printf("%d\n", compete(ids));
  } else {
    while (true) {
      Receive(0);
      int left = GetInt(0); 
      if (left == -1) {
        break; 
      }
      int right = GetInt(0);
      ids.clear();
      for (int i = left; i <= right; ++i) {
        ids.push_back(i); 
      }
      int winner = compete(ids);
      //printf("%d %d %d\n", left, right, winner);
      PutInt(0, winner);
      Send(0);
    }
  }
  return 0;
}