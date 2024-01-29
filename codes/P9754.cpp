#include<bits/stdc++.h>
using namespace std;
int n, r, struct_cnt;

map<string,int> struct_id;//结构体名称对应编号
vector<pair<string,string> > struct_members[110];//结构体成员(先类型在名称)
int struct_size[110];//结构体大小
string struct_name[110];//结构体类型名称

pair<int,int> addtype(string typ,int k = 0){
    struct_cnt++;struct_id[typ] = struct_cnt;struct_name[struct_cnt] = typ;
    if(!k){
        if(typ == "byte")struct_size[struct_cnt] = 1;
        if(typ == "short")struct_size[struct_cnt] = 2;
        if(typ == "int"  )struct_size[struct_cnt] = 4;
        if(typ == "long" )struct_size[struct_cnt] = 8;
        return make_pair(0,0);
    }
    int size = 0;
    for(int i = 1;i <= k;i++){
        string types, names;cin >> types >> names;
        struct_members[struct_cnt].push_back(make_pair(types,names));
        size = max(size,struct_size[struct_id[types]]);
    }
    struct_size[struct_cnt] = size * k;return make_pair(struct_size[struct_cnt],size);
}
vector<pair<int,int> > variable_range;//记录变量的左右区间
vector<int> variable_type;//记录变量类型编号
map<string,int> variable_id;int variable_cnt;//记录变量对应的编号
string variable_name[110];

string find_variable(int typ,int pos){
    if(struct_members[typ].empty()){
        if(pos > struct_size[typ]){return "ERR";}
        return "???";
    }
    int k = struct_size[typ] / struct_members[typ].size();
    for(int i = 0;i < struct_members[typ].size();i++){
        if(k * i <= pos && pos <= k * (i + 1)){
            string tmp = find_variable(struct_id[struct_members[typ][i].first],pos - k * i);
            if(tmp == "ERR")return tmp;
            else if(tmp == "???")return struct_members[typ][i].second;
            else return struct_members[typ][i].second + '.' + tmp;
        }
    }
}

int variable_pos(string names,int typ){
    // cout << "names = " << names << " typ = " << typ << '\n';
    if(names == "")return 0;
    string a = names, b = "";
    for(int i = 0;i < names.size();i++){
        if(names[i] == '.'){a.erase(a.begin());break;}
        a.erase(a.begin());b = b + names[i];
    }
    // cout << "a = " << a <<'\n';
    // if(a == "")return 0;
    int res = 0, k = struct_size[typ] / struct_members[typ].size();
    for(int i = 0;i < struct_members[typ].size();i++,res += k)
        if(b == struct_members[typ][i].second){
            // cout << "i = " << i << '\n';
            return variable_pos(a,struct_id[struct_members[typ][i].first]) + res;
        }
    return -114514;
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("struct.in","r",stdin);
    freopen("struct.out","w",stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    addtype("byte");addtype("short");addtype("int");addtype("long");
    while(n--){
        int opt;cin >> opt;
        switch(opt){
            case 1:{
                string names;int k;
                cin >> names >> k;
                pair<int,int> tmp = addtype(names,k);
                cout << tmp.first << ' ' << tmp.second << '\n';
                break;
            }
            case 2:{
                string names, typ;
                cin >> typ >> names;
                cout << r << '\n';
                variable_name[variable_cnt] = names;
                variable_id[names] = variable_cnt++;variable_type.push_back(struct_id[typ]);
                variable_range.push_back(make_pair(r,r + struct_size[struct_id[typ]] - 1));
                r += struct_size[struct_id[typ]];
                break;
            }
            case 3:{
                string names;cin >> names;string a = names, b = "";
                for(int i = 0;i < names.length();i++){
                    if(names[i] == '.'){a.erase(a.begin());cout << variable_pos(a,variable_type[variable_id[b]]) + variable_range[variable_id[b]].first << '\n';break;}
                    b = b + names[i]; a.erase(a.begin());
                }
                break;
            }
            case 4:{
                int l;string ans = "ERR";cin >> l;
                if(l <= r)
                for(int i = 0;i < variable_cnt;i++){
                    if(variable_range[i].first <= l && l <= variable_range[i].second){
                        ans = find_variable(variable_type[i],l - variable_range[i].first);
                        if(ans != "ERR"){ans = variable_name[i] + '.' + ans;}
                        break;
                    }
                }
                cout << ans << '\n';
                break;
            }
            default:break;
        }
    }

    return 0;
}