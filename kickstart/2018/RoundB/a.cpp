#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

ll f[20][2][9];
int arr[20];

ll Calc(ll val) {
  memset(f, 0, sizeof f);
  memset(arr, 0, sizeof arr);

  for (int i = 19; i >= 0; --i) {
    arr[i] = val % 10;
    val /= 10;
  }

  f[0][1][0] = 1;
  for (int i = 0; i < 19; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 9; ++k) {
        if (f[i][j][k] == 0) { continue; }
        int max_val = j == 1 ? arr[i + 1] : 8;
        if (max_val == 9) { --max_val; }
        // cout << i << " " << j << " " << k << " " << max_val << endl;
        for (int x = 0; x <= max_val; ++x) {
          if (j == 1 && x == arr[i + 1]) {
            f[i + 1][1][(k + x) % 9] += f[i][j][k];
          } else {
            f[i + 1][0][(k + x) % 9] += f[i][j][k];
          }
        }
      }
    }
  }

  ll ret = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 1; j < 9; ++j) {
      ret += f[19][i][j];
    }
  }
  return ret;
}

void domain() {
  ll l, r;
  cin >> l >> r;
  ll ans = Calc(r);
  if (l > 1) { ans -= Calc(l - 1); }
  cout << ans << endl;
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
