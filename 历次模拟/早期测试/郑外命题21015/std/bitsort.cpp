#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        vector<int> a(n);
        for(int i=0;i<n;i++) scanf("%d",&a[i]);
        vector<vector<int> > v;
        v.push_back(a);
        bool succ=true;
        for(int i=29;i>=0;i--){
            vector<int> flag(v.size());
            int c1=0,c2=0;
            for(int j=0;j<v.size();j++){
                for(int k=0;k<v[j].size();k++){
                    if(v[j][k]&(1<<i)) {
                        flag[j]|=1;
                    }
                    else {
                        flag[j]|=2;
                    }
                }
            }
            int d0=0,d1=0;
             bool bg=false;
            if(v.size()==1||flag[0]==2||(flag[0]==3&&flag[1]==1)){
                //0在前
                vector<vector<int> > tmp;
                for(int j=0;j<v.size();j++){
                    if(flag[j]!=3){
                        if(flag[j]==2&&bg) succ=false;
                        tmp.push_back(v[j]);
                        if(flag[j]==1) bg=1;
                    }else{
                        vector<vector<int> > ttmp(2);
                        for(int k=0;k<v[j].size();k++){
                            if(v[j][k]&(1<<i)) ttmp[1].push_back(v[j][k]);
                            else ttmp[0].push_back(v[j][k]);
                        }
                        tmp.push_back(ttmp[0]);
                        tmp.push_back(ttmp[1]);
                        if(bg){
                            succ=false;
                        }
                        bg=1;
                    }
                }
                v=tmp;
            }else{
                //1在前
                vector<vector<int> > tmp;
                for(int j=0;j<v.size();j++){
                    if(flag[j]!=3){
                        if(flag[j]==1&&bg) succ=false;
                        tmp.push_back(v[j]);
                        if(flag[j]==2) bg=1;
                    }else{
                        vector<vector<int> > ttmp(2);
                        for(int k=0;k<v[j].size();k++){
                            if(v[j][k]&(1<<i)) ttmp[0].push_back(v[j][k]);
                            else ttmp[1].push_back(v[j][k]);
                        }
                        tmp.push_back(ttmp[0]);
                        tmp.push_back(ttmp[1]);
                        if(bg){
                            succ=false;
                        }
                        bg=1;
                    }
                }
                v=tmp;
            }
        }
        if(succ){
            for(int i=0;i<v.size();i++){
                for(int j=0;j<v[i].size();j++){
                    printf("%d ",v[i][j]);
                }
            }
            puts("");
        }else{
            puts("No Solution");
        }
    }
    return 0;
}