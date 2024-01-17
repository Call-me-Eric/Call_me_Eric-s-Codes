#include <bits/stdc++.h>
using namespace std;

const int N = 1e8;

int m;
int v[N + 5], p[N + 5];

void init() {
  for (int i = 2; i <= N; ++i) {
    if (!v[i]) v[i] = i, p[++m] = i;
    for (int j = 1; j <= m && p[j] * i <= N; ++j) {
      v[p[j] * i] = p[j];
      if (i % p[j] == 0) break; 
    }
  }
}

bool check(int x) {
  int cnt = 0, c8 = 0, c9 = 0, c4 = 0, c6 = 0;
  int res = 0;
  // if (x % 10 != 9) return 0;
  vector<int> now;
  while (x) {
    int res = x % 10;
    if (res == 2 || res == 3 || res == 5 || res == 7) return 0;
    now.push_back(x % 10);
    x /= 10;
  }
  reverse(now.begin(), now.end());
  int fl = 0;
  int j1 = 0, j2 = 0,j3 = 0, j4 = 0, j5 = 0;
  for (auto x : now) {
    if (x == 1 && (cnt || c4 || c6 || c8 >= 2 || c9 >= 2)) return 0;
    if (x == 9 && fl) return 0;
    if (x == 9 && c8) return 0;
    if (x == 9 && cnt) return 0;
    if (c4 && (x == 0 || x == 4 || x == 9)) fl = 1;
    if (j1 < 2 && x == 9) j1++;
    if (j1 == 2 && x == 4) j1++;
    if (j1 == 3 && x == 9) j1++;

    if (j2 == 0 && x == 9) j2++;
    if (j2 == 1 && x == 6) j2++;
    if (j2 == 2 && x == 4) j2++;
    if (j2 == 3 && x == 9) j2++;

    if (j3 == 0 && x == 6) j3++;
    if (j3 == 1 && x == 4) j3++;
    if (j3 == 2 && x == 6) j3++;
    if (j3 == 3 && x == 9) j3++;

    if (j4 == 0 && x == 6) j4++;
    if (j4 == 1 && x == 9) j4++;
    if (j4 == 2 && x == 4) j4++;
    if (j4 == 3 && x == 9) j4++;

    if (j5 == 0 && x == 9) j5++;
    if (j5 == 1 && x == 0) j5++;
    if (j5 == 2 && x == 4) j5++;
    if (j5 == 3 && x == 9) j5++;

    c6 += (x == 6);
    c4 += (x == 4);
    c8 += (x == 8);
    c9 += (x == 9);
    cnt += (x == 1);
  }
  if (j1 == 4 || j2 == 4 || j3 == 4 || j4 == 4) return 0;
  if (j5 == 4) return 0;
  return cnt <= 1 && (c4 || c6);
}

int main() {
  init();
  for (int i = 1; i <= m; ++i) if (check(p[i])) {
    cout << p[i] << "\n";
  }
  return 0;
}