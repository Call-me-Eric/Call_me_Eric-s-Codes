#include<bits/stdc++.h>
using namespace std;
int n;
vector<pair<int,int> > f1(vector<pair<int,int> >a){
    for(int i=0;i<3;i++){
        a[i].second++;
        if(a[i].second==n) a[i].second=0;
    }
    return a;
}
vector<pair<int,int> > f2(vector<pair<int,int> >a){
    for(int i=0;i<3;i++){
        a[i].first++;
        if(a[i].first==n) a[i].first=0;
    }
    return a;
}
vector<pair<int,int> > f3(vector<pair<int,int> >a){
    for(int i=0;i<3;i++){
        swap(a[i].first,a[i].second);
    }
    return a;
}
vector<pair<int,int> > f4(vector<pair<int,int> >a){
    for(int i=0;i<3;i++){
        int tx=a[i].first;
        int ty=a[i].second;
        a[i].first=ty;
        a[i].second=n-tx-1;
    }
    return a;
}
vector<pair<int,int> > f5(vector<pair<int,int> >a){
    for(int i=0;i<3;i++){
        a[i].second=n-a[i].second-1;
    }
    return a;
}
vector<pair<int,int> > f6(vector<pair<int,int> >a){
    for(int i=0;i<3;i++){
        a[i].first=n-a[i].first-1;
    }
    return a;
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        cerr<<T<<endl;
        scanf("%d",&n);
        vector<pair<int,int> > v(3);
        v[0]=make_pair(0,0);
        v[1]=make_pair(0,1);
        v[2]=make_pair(1,0);
        vector<pair<int,int> > to(3);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int x;scanf("%d",&x);
                x--;
                if(i==0&&j==0){
                    to[0]=make_pair(x/n,x%n);
                }
                if(i==0&&j==1){
                    to[1]=make_pair(x/n,x%n);
                }
                if(i==1&&j==0){
                    to[2]=make_pair(x/n,x%n);
                }
            }
        }
        map<vector<pair<int,int> >,int> dis;
        queue<vector<pair<int,int> > >  q;
        dis[v]=0;
        q.push(v);
        while(!q.empty()){
            auto now=q.front();q.pop();
            int d=dis[now];
            if(dis.find(to)!=dis.end()){
                cout<<dis[to]<<endl;
                break;
            }
            auto now1=f1(now);
            if(dis.find(now1)==dis.end()){
                dis[now1]=d+1;q.push(now1);
            }

            now1=f2(now);
            if(dis.find(now1)==dis.end()) {
                dis[now1]=d+1;q.push(now1);
            }

            now1=f3(now);
            if(dis.find(now1)==dis.end()) {
                dis[now1]=d+1;q.push(now1);
            }
            
            now1=f4(now);
            if(dis.find(now1)==dis.end()) {
                dis[now1]=d+1;q.push(now1);
            }

            now1=f5(now);
            if(dis.find(now1)==dis.end()){
                dis[now1]=d+1;q.push(now1);
            }

            now1=f6(now);
            if(dis.find(now1)==dis.end()) {
                dis[now1]=d+1;q.push(now1);
            }
        }

    }
}