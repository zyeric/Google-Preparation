#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;

ll const max_p = 1000000000000000000;
ll f[101][1 << 15];
ll g[101][1 << 15];
int n, k;
ll p;
vector<vector<pair<int, int>>> cts;
int cnt[1 << 15][16];

string num2string(int val) {
  string ret = "";
  for (int i = 14; i >= 0; --i) {
    if (val & (1 << i)) { ret += "1"; }
    else { ret += "0"; }
  }
  return ret;
}

void domain() {
  memset(f, 0, sizeof f);
  memset(g, false, sizeof g);
  cts.clear();
  cin >> n >> k >> p;
  cts.resize(n + 1);
  for (int i = 0; i < k; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    cts[a].push_back({b, c});
  }
  f[n][0] = 1;
  for (int i = n; i >= 1; --i) {
    for (int j = 0; j < (1 << 15); ++j) {
      if (f[i][j] == 0) { continue; }
      for (int cur = 0; cur < 2; ++cur) {
        bool valid = true;
        for (auto& ct : cts[i]) {
          int sum = cur == 1 ? 1 : 0;
          sum += cnt[j][ct.first - i];
          if (sum != ct.second) {
            valid = false;
            break;
          }
        }
        if (valid) {
          int next_state = ((cur << 15) + j) >> 1;
          f[i - 1][next_state] += f[i][j];
          f[i - 1][next_state] = min(f[i - 1][next_state], max_p);
          if ((j & 1) == 0) {
            g[i - 1][next_state] = true;
          }
        }
      }
    }
  }
  string ret = "";
  int prev_state = -1;
  for (int i = 0; i < n; ++i) {
    if (i == 0) {
      ll sum = 0;
      for (int j = 0; j < (1 << 15); ++j) {
        if (sum + f[i][j] >= p) {
          if (j & (1 << 14)) { ret += "1"; }
          else { ret += "0"; }
          p -= sum;
          prev_state = j;
          break;
        } else {
          sum += f[i][j];
        }
      }
    } else {
      ll cur_state = (prev_state << 1) & ((1 << 15) - 1);
      if (!g[i - 1][prev_state]) { ++cur_state;}
      ll sum = 0;
      if (f[i][cur_state] < p) {
        sum += f[i][cur_state];
        ++cur_state;
      }
      if (cur_state & (1 << 14)) { ret += "1"; }
      else { ret += "0"; }
      prev_state = cur_state;
      p -= sum;
    }
  }
  cout << ret << endl;
}

int main() {
  for (int i = 0; i < (1 << 15); ++i) {
    cnt[i][0] = 0;
    for (int j = 14; j >= 0; --j) {
      cnt[i][14 - j + 1] = cnt[i][14 - j];
      if (i & (1 << j)) {
        ++cnt[i][14 - j + 1];
      }
    }
  }
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    printf("Case #%d: ", i);
    domain();
  }
  return 0;
}
