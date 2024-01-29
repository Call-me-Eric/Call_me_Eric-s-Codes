#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
void gen1(int n) {
  ofstream fout("rgb.in");
  map<pair<int, int>, int> mp;
  int m = n - 1 + (rnd() % (n * (n - 1) / 2 - (n - 1) + 1));
  // m = n * (n - 1) / 2;
  int r = rnd() % n, g = rnd() % (n - r), b = n - r - g - 1;
  fout << r << " " << g << " " << b << " " << m << "\n";
  for (int i = 2; i <= n; ++i) {
    int u = rnd() % (i - 1) + 1;
    vector<char> vec{'r', 'g', 'b'};
    mp[{u, i}] = 1;
    fout << u << " " << i << " " << vec[rnd() % 3] << "\n";
  }
  for (int i = 1; i <= m - (n - 1); i++) {
    int u = rnd() % n + 1, v = rnd() % n + 1;
    if (u > v) swap(u, v);
    while (v == u || mp.find({u, v}) != mp.end()) {
      u = rnd() % n + 1;
      v = rnd() % n + 1;
      if (u > v) swap(u, v);
    }
    mp[{u, v}] = 1;
    vector<char> vec{'r', 'g', 'b'};
    fout << u << " " << v << " " << vec[rnd() % 3] << "\n";
  }
  fout.close();
}

const int N = 250 + 5;
const int M = 250 * 250 + 5;

int r, g, b, m, n;
int d[N];
struct Edge {
  int u, v;
  char c;
} e[M];

bool check() {
  ifstream fin("rgb.in"), fout("rgb.out");
  fin >> r >> g >> b >> m, n = r + g + b + 1;
  fill_n(d, n + 5, 0);
  for (int i = 1; i <= m; ++i) {
    fin >> e[i].u >> e[i].v >> e[i].c;
    while (e[i].c == ' ') fin >> e[i].c;
  }
  string st;
  fout >> st;
  if (st == "NO") {
    fin.close(), fout.close();
    return 0;
  }
  fout >> st;
  int cnt = 0;
  for (int i = 1; i <= m; ++i) {
    if (st[i - 1] == '0') continue;
    cnt++;
    d[e[i].u]++, d[e[i].v]++;
    char c = e[i].c;
    if (c == 'r') {
      r--;
    }
    if (c == 'g') {
      g--;
    }
    if (c == 'b') {
      b--;
    }
  }
  int fl = 0;
  for (int i = 1; i <= n; ++i) if (!d[i]) {
    if (n != 1) {
      cerr << "no " << i << "\n";
      fl = 1;
    }
  }
  if (r == 0 && g == 0 && b == 0) {
  } else {
    fl = 1;
    cerr << "no rgb\n";
  }
  fin.close(), fout.close();
  return fl;
}

int main() {
  // cout << check() << "\n";
  // return 0;
  int cnt = 0;
  while (++cnt) {
    // gen1(rnd() % 5 + 1);
    gen1(rnd() % 250 + 1);
    system("./rgb");
    if (check()) {
      cout << "WA\n";
      return 0;
    }
    cout << "AC " << cnt << "\n"; 
  }
  return 0;
}