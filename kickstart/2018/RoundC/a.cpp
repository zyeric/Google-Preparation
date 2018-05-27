#include <cstdio>
#include <vector>
#include <set>
#include <queue>
using namespace std;

vector<vector<int>> e;
bool vis[1234];
int loops, loope;
set<int> loop;
int dis[1234];

void dfs(int u, int fu) {
  vis[u] = true;
  for (auto v : e[u]) {
    if (v == fu) { continue; }
    if (vis[v] == true) {
      loops = u;
      loope = v;
    } else {
      dfs(v, u);
    }
  }
}

bool dfs2(int u, int fu) {
  // printf("%d %d\n", u, fu);
  if (u == loope) {
    loop.insert(u);
    return true;
  }
  bool ret = false;
  for (auto v : e[u]) {
    if (v == fu) { continue; }
    if (u == loops && v == loope) { continue; }
    if (dfs2(v, u)) {
      loop.insert(u);
      ret = true;
    }
  }
  return ret;
}

void domain() {
  int n;
  scanf("%d", &n);
  e.resize(n);
  loop.clear();
  for (int i = 0; i < n; ++i) { e[i].clear(); }
  for (int i = 0; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u-1].push_back(v-1);
    e[v-1].push_back(u-1);
  }
  for (int i = 0; i < n; ++i) { vis[i] = false; }
  dfs(0, -1);
  // printf("%d %d\n", loops, loope);
  dfs2(loops, -1);
  queue<int> Q;
  for (int i = 0; i < n; ++i) {
    if (loop.count(i) > 0) {
      dis[i] = 0;
      if (e[i].size() > 2) {
        Q.push(i);
      }
    } else {
      dis[i] = 1234;
    }
  }
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int v : e[u]) {
      if (loop.count(v) > 0) { continue; }
      if (dis[v] <= dis[u]) { continue; }
      dis[v] = dis[u] + 1;
      Q.push(v);
    }
  }
  for (int i = 0; i < n; ++i) {
    printf(" %d", dis[i]);
  }
  printf("\n");
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    printf("Case #%d:", i);
    domain();
  }
  return 0;
}
