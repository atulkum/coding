bool possible_util(std::vector<std::vector<int>> &adj, 
                   std::vector<int> color,
                   int m, int v){
    using namespace std;
    int n = adj.size();
    if(v == n) return true;
    for(int c = 1; c <= m; ++c){
        bool canColor = true;
        for(int j = 0; j < n; ++j){
            if(adj[v][j] ==1 && color[j] == c){
                canColor = false;
                break;
            }
        }
        if(canColor){
            color[v] = c;
            if(possible_util(adj, color, m, v+1)){
                return true;
            }
            color[v] = 0;
        }
    }
    return false;
}
bool possible(std::vector<std::vector<int>> &adj, int m){
    using namespace std;
    int n = adj.size();
    vector<int> color(n , 0);
    return possible_util(adj, color, m, 0);
}
int minimumNumberOfBreeds(std::vector<std::vector<int>> glades, std::vector<std::vector<int>> paths) {
    using namespace std;
    int n = glades.size();
    vector<vector<int>> adj(n,vector<int>(n, 0));
    for(auto p:paths){
        adj[p[0]][p[1]] = 1;
        adj[p[1]][p[0]] = 1;
    }
    int left = 1;
    int right = n;
    /*while(right > 0){
        if(possible(adj, right)) right--;
        else break;
    }
    return right+1;*/
    while(left < right){
        int mid = left + (right - left)/2;
        if(possible(adj, mid)){
            right = mid;
        }else{
            left = mid + 1;
        }
    }
    return left;
}
