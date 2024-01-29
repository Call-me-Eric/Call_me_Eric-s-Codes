#include <bits/stdc++.h>
const int MOD = 998244353; 

void my_favorite_animal_is_fat_head_fish() {
  int n, ans = 0; 
  std::cin >> n; 
  std::vector<int> arr(n); 
  for (int i = 0; i < n; ++i) std::cin >> arr[i]; 
  for (int a = 0; a < n; ++a) for (int b = a; b < n; ++b)
    for (int c = b + 2; c < n; ++c) for (int d = c; d < n; ++d) {
      std::set<int> s; 
      for (int i = b + 1; i <= c - 1; ++i) s.insert(arr[i]); 
      if (s.size() != c - 1 - b) continue; 
      bool flag = 1; 
      for (int i = a; i <= b; ++i) if (s.count(arr[i])) { flag = 0; break; }
      for (int i = c; i <= d; ++i) if (s.count(arr[i])) { flag = 0; break; }
      if (flag) ans = (ans + 1) % MOD; 
    }
  std::cout << ans << "\n"; 
}