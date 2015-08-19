#include <iostream>
#include <algorithm>

using namespace std;

class BearPlays {
public:
    int pileSize(int A, int B, int K);
};

inline int mul(int a, int b, int mod) {
    return (long long) a * b % mod;
}

int BearPlays :: pileSize(int A, int B, int K) {
   B += A;
   int p = 2;
   for (; K; K /= 2) {
       if (K % 2) {
           A = mul(A, p, B);
       }
       p = mul(p, p, B);
   }
   return min(A, B - A);
}
