#include <cstdio>
#include <algorithm>

int l[20][20];
int n;
int ans;
bool vis[20];

void dfs(int cur, int cnt, int sum, int max_val) {
  for (int i = cur; i < n; ++i) {
    if (vis[i]) { continue; }
    for (int j = i + 1; j < n; ++j) {
      if (l[i][j] == 0) { continue; }
      if (vis[j]) { continue; }
      vis[i] = true;
      vis[j] = true;
      dfs(i + 1, cnt + 1, sum + l[i][j], std::max(max_val, l[i][j]));
      vis[i] = false;
      vis[j] = false;
    }
  }
  if (cnt >= 3 && max_val < (sum - max_val)) { ++ans; }
}

void domain() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &l[i][j]);
    }
  }
  ans = 0;
  for (int i = 0; i < n; ++i) { vis[i] = false; }
  dfs(0, 0, 0, 0);
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    printf("Case #%d: ", i);
    domain();
  }
  return 0;
}
