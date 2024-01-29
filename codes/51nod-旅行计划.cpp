#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
using namespace std;
int n, k, L, t;
const int N = 50000 + 10;
vector<vector<int>> tree,tmp,res;
int dep[N],f[N];
int main(){
    tree.resize(N);
    tmp.resize(N);
    res.resize(N);
    scanf("%d%d",&n,&k);
    int t = 0;
    for(int i = 1;i < n;i++){
        scanf("%d",&t);
        tree[i].push_back(t);
        tree[t].push_back(i);
    }
    vector<int> st;
    st.push_back(k);
    f[k] = k;
    dep[k] = 0;
    while(!st.empty()){
        t = st.back();
        st.pop_back();
        for(int i = 0;i < tree[t].size();i++){
            if(tree[t][i] != f[t]){
                f[tree[t][i]] = t;
                dep[tree[t][i]] = dep[t] + 1;
                st.push_back(tree[t][i]);
            }
        }
    }
    for(int i = 0;i < n;i++){
        if(tree[i].size() == 1){
            res[dep[i]].push_back(i);
        }
    }
    for(int i = n - 1;i > 0;i--){
        for(int j = 0;j < res[i].size();j++){
            int len = 0;
            int tmp = res[i][j];
            for(;dep[tmp] != 0;++len){
                dep[tmp] = 0;
                tmp = f[tmp];
            }
            dep[res[i][j]] = len;
        }
        res[i].clear();
    }
    for(int i = 0;i < n;i++){
        if(tree[i].size() == 1){
            res[dep[i]].push_back(i);
        }
    }
    printf("%d\n",k);
    for(int i = n - 1;i > 0;i--){
        for(int j = 0;j < res[i].size();j++){
            printf("%d\n",res[i][j]);
        }
    }
    return 0;
}