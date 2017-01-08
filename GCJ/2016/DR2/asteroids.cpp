#include <message.h>
#include <stdio.h>
#include <vector>
#include "asteroids.h"

#define MASTER_NODE 0
#define SENDING_DONE -1

using namespace std;

const int WIDTH(300);

int id;
int w;
int num_nodes;
long long dp[2][WIDTH * 3 + 10];
char ch[2][WIDTH * 3 + 10];

void GetSeg(int cur, int node, int l, int r) {
  if (node < 0 || node >= num_nodes) {
    return; 
  }
  Receive(node);
  for (int i = l; i < r; ++i) {
    dp[cur][i] = GetLL(node); 
  } 
}

void PutSeg(int cur, int node, int l, int r) {
  if (node < 0 || node >= num_nodes) {
    return;
  }
  for (int i = l; i < r; ++i) {
    PutLL(node, dp[cur][i]);
  }
  Send(node);
}

int main() {
  int height = GetHeight();
  int width = GetWidth();
  num_nodes = NumberOfNodes();
  id = MyNodeId();
  w = (width + num_nodes - 1) / num_nodes;
  long long result = -1;
  memset(dp[0], 0, sizeof(dp[0]));
  for (int i = 0; i < height; ++i) {
    int cur = i & 1;
    for (int j = (id - 1) * w; j < (id + 2) * w; ++j) {
      if (j >= 0 && j < width) {
        ch[cur][j - (id - 1) * w] = GetPosition(i, j); 
      } else {
        ch[cur][j - (id - 1) * w] = '#';
      }
    }
    if (i % w == 0) {
      PutSeg(i & 1, id - 1, w, 2 * w);
      PutSeg(i & 1, id + 1, w, 2 * w);
      GetSeg(i & 1, id - 1, 0, w);
      GetSeg(i & 1, id + 1, 2 * w, 3 * w);
    }
    memset(dp[cur ^ 1], -1, sizeof(dp[cur ^ 1]));
    for (int j = 0; j < 3 * w; ++j) {
      if (dp[cur][j] != -1 && ch[cur][j] != '#') {
        dp[cur][j] += ch[cur][j] - '0'; 
        dp[cur ^ 1][j] = max(dp[cur ^ 1][j], dp[cur][j]);
        if (j && ch[cur][j - 1] != '#') {
          dp[cur ^ 1][j - 1] = max(dp[cur ^ 1][j - 1], dp[cur][j] + ch[cur][j - 1] - '0'); 
        } 
        if (j + 1 < 3 * w && ch[cur][j + 1] != '#') {
          dp[cur ^ 1][j + 1] = max(dp[cur ^ 1][j + 1], dp[cur][j] + ch[cur][j + 1] - '0'); 
        }
      }
    }  
  }
  for (int i = 0; i < 3 * w; ++i) {
    result = max(result, dp[height & 1][i]); 
  }
  PutLL(MASTER_NODE, result);
  Send(MASTER_NODE);
  if (id == MASTER_NODE) {   
    long long result = -1;
    for (int i = 0; i != num_nodes; ++i) {
      Receive(i); 
      result = max(result, GetLL(i));
    }
    printf("%lld\n", result); 
  } 
  return 0;
}