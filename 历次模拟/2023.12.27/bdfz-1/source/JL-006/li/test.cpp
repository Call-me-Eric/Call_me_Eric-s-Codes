#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> g(vector<pair<int,int>>v){
    vector<pair<int,int>>ans;
    for(int i=0;i<v.size();i++)
    for(int j=i+1;j<v.size();j++){
        if(v[i].first==v[j].first||v[i].first==v[j].second||v[i].second==v[j].first||v[i].second==v[j].second)ans.push_back({i+1,j+1});
    }
    return ans;
}
int main(){
    vector<pair<int,int>>tmp={{1,2},{2,3},{3,4},{4,1},{1,3}};
    for(int i=1;i<=10;i++){
        tmp=g(tmp);
        /*cerr<<"round="<<i<<endl;
        for(auto [x,y]:tmp){
            cerr<<x<<" "<<y<<endl;
        }*/
        cerr<<"size="<<tmp.size()<<endl;
    }
    return 0;
}