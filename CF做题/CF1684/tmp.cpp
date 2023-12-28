#include<bits/stdc++.h>
using namespace std;
signed main(){
    vector<int>  vec;
    for(int i = 1;i <= 10;i++)vec.push_back(i);
    printf("%d\n",vec[lower_bound(vec.begin(),vec.end(),12) - vec.begin()]);
    return 0;
}