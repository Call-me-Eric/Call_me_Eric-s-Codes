#include <bits/stdc++.h>

using namespace std; 

const int MaxN = 255; 
const int MaxM = 35000; 

mt19937 myrand(time(0)); 

int n, r, g, b, m; 

int lim[3]; 

struct edge {
   int u, v; 
   int flg; 
} e[MaxM]; 

int t[MaxM]; 

int fa[MaxN]; 

int find(int x) {
   return (fa[x] == x) ? x : fa[x] = find(fa[x]); 
}

bool ans[MaxM]; 

bool check() {
   int cnt[3] = {0}; 
   memset(ans, 0, sizeof(ans)); 
   for (int i = 1; i <= n; ++i) fa[i] = i; 
   for (int i = 1; i <= m; ++i) {
      //if (cr > r || cg > g || cb > b) return 0; 
      int p = find(e[t[i]].u), q = find(e[t[i]].v); 
      if (p != q && cnt[e[t[i]].flg] < lim[e[t[i]].flg]) {
         ++cnt[e[t[i]].flg]; 
         fa[p] = q; 
         ans[t[i]] = 1; 
      }
   }
   //printf("%d %d %d\n", cr, cg, cb); 
   if (cnt[0] + cnt[1] + cnt[2] == n - 1) return 1; 
   else return 0; 
}

int main() {
   freopen("rgb.in", "r", stdin); 
   freopen("rgb.out", "w", stdout); 
   int start_time = clock(); 
   scanf("%d %d %d %d", &r, &g, &b, &m); 
   n = r + g + b + 1; 
   lim[0] = r, lim[1] = g, lim[2] = b; 
   for (int i = 1; i <= m; ++i) {
      scanf("%d %d", &e[i].u, &e[i].v); 
      char s[3]; 
      scanf("%s", s); 
      if (s[0] == 'r') e[i].flg = 0; 
      else if (s[0] == 'g') e[i].flg = 1; 
      else e[i].flg = 2; 
   }
   for (int i = 1; i <= m; ++i) t[i] = i; 
   while (clock() - start_time < 1800000) {
      shuffle(t + 1, t + m + 1, myrand); 
      if (check()) {
         puts("YES"); 
         for (int i = 1; i <= m; ++i) putchar(ans[i] + '0'); 
         puts(""); 
         return 0; 
      }
   }
   puts("NO"); 
   return 0; 
}
