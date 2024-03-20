#include "city.h"
#include <bits/stdc++.h>
using namespace std; 

std::vector<int> find_roads(int n, bool gold, std::vector<int> u, std::vector<int> v) {
    // When gold = 0, this cold can solve m <= MAXQ
    std::vector<int> r; 
    for (int i = 0; i < u.size(); ++i) {
        vector<int> t{i}; 
        if (count_common_roads(t) == 1) r.push_back(i); 
    }
    return r;
}