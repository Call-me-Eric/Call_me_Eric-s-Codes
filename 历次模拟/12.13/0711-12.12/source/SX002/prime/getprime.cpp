#include<bits/stdc++.h>
using namespace std;
vector<int> pri;
bitset<1000000009> l;
int main(){
    freopen("pri.txt","w",stdout);
    for(int i=2;i<=1e7;++i){
        if(l[i]==0){
            printf("%d\n",i);
            pri.push_back(i);
        }
        for(int j=0;j<pri.size();++j){
            if(1ll*i*pri[j]>1e7) break;
            l[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
}