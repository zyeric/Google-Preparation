#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

int N, V, H, A, B, C, D, E, F, M;
bool f[1234][1234];

void domain() {
  cin >> N >> V >> H >> A >> B >> C >> D >> E >> F >> M;
  memset(f, false, sizeof f);
  for (int i = 0; i < N; ++i) {
    f[V][H] = 0;
    int tmp_v = (A * V + B * H + C) % M;
    int tmp_h = (D * V + E * H + F) % M;
    V = tmp_v;
    H = tmp_h;
  }

  int ans = 0;
  for (int i = 0; i < M; ++i) {
    int sum = 0;
    for (int j = 0; j < M; ++j) {
      if (f[i][j]) { ++sum; }
    }
    if (sum >= 3) {
      ans += sum * (sum - 1) * (sum - 2) / 6;
    }
  }
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ": ";
    domain();
  }
  return 0;
}
