#include <iostream>
using namespace std;

typedef long long ll;

ll mod = 1000000007;

ll a[1234567];
ll sum[1234567];
ll ssum[1234567];

ll powmod(ll a, ll b, ll c) {
  ll ret = 1;
  while (b) {
    if (b & 1) {
      ret = ret * a % c;
    }
    a = a * a % c;
    b >>= 1;
  }
  return ret;
}

void domain() {
  ll n, k, x1, y1, c, d, e1, e2, f;
  cin >> n >> k >> x1 >> y1 >> c >> d >> e1 >> e2 >> f;
  for (int i = 1; i <= n; ++i) {
    a[i] = (x1 + y1) % f;
    ll xx = (c * x1 + d * y1 + e1) % f;
    ll yy = (d * x1 + c * y1 + e2) % f;
    x1 = xx;
    y1 = yy;
  }
  for (int i = 1; i <= n; ++i) {
    if (i == 1) {
      sum[i] = k;
      continue;
    }
    sum[i] = i;
    ll u = (powmod(i, k, mod) - 1 + mod) % mod;
    ll v = powmod(i - 1, mod - 2, mod);
    sum[i] = sum[i] * u % mod;
    sum[i] = sum[i] * v % mod;
  }

  ll ans = 0;
  ll presum = 0;
  for (ll i = 1; i <= n; ++i) {
    presum = presum + sum[i];
    presum %= mod;
    ll tmp = a[i] * presum % mod;
    tmp = tmp * (n - i + 1) % mod;
    ans += tmp;
  }
  ans %= mod;
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
