int find(int i, const std::vector<int>& parents){
    if(parents[i] == i){
        return i;
    }
    return find(parents[i], parents);
}
bool check_union(int i, int j, std::vector<int>& parents){
    int x = find(i, parents);
    int y = find(j, parents);
    
    if(x == y){
        return true;
    }
    int parent = min(x, y);
    int child = max(x, y);
    parents[child] = parent;
    return false;
}
std::string swapLexOrder(std::string str, std::vector<std::vector<int>> pairs) {
    using namespace std;
    int n = str.length();
    vector<int> parents(n, 0);
    for(int i =0;i < n; ++i){
        parents[i] = i;
    }
    
    for(const auto& e: pairs){
        
        check_union(e[0]-1, e[1]-1, parents);
        /*cout <<" => " << e[0]-1 << " " << e[1]-1 << endl;
        for(int i =0;i < n; ++i)
            cout << "--- " <<parents[i];
        cout <<endl;*/
    }
    map<int, vector<int>> m;
    for(int i =0;i < n; ++i){
        //if(i != parents[i]){
            m[find(i, parents)].push_back(i);
        //}
    }
    string ret(str);
    for(auto& e: m){
        if(e.second.size() == 1){
            continue;
        }
        vector<char> cc;
        for(int i: e.second){
            cc.push_back(str[i]);
            //cout << str[i] <<endl;
        }
        
        sort(cc.begin(), cc.end(), ::greater<char>());
        int k = 0;
        for(int i: e.second){
            //cout << "==" << cc[k] <<endl;
            ret[i] = cc[k++];
        }
    }
    return ret;
}
