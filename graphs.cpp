class Graph{
public:
  std::set<int> curr;
  std::set<int> visited;
  std::vector<std::vector<int>> conn;

  Graph(std::vector<std::vector<int>>& a_conn){
    conn = a_conn;
  }
  bool dfs(int st){
    //std::cout << st << " st " << std::endl;
    curr.insert(st);
    bool ret = dfs_internal(st);
    curr.erase(st);
    return ret;
  }
  bool dfs_internal(int st){
    for(int c : conn[st]){
      if(curr.count(c) > 0){
        return true;
      }
      if(visited.count(c) == 0){
        curr.insert(c);
        bool ret = dfs_internal(c);
        curr.erase(c);
        if(ret) return true;
      } 
    }
    visited.insert(st);
    //std::cout << st << " f " << std::endl;
    return false;
  }
};
bool hasDeadlock(std::vector<std::vector<int>> connections) {
  Graph g(connections);
  for(int i = 0; i < connections.size(); ++i){
      if(g.visited.count(i) == 0){
        if(g.dfs(i)){
          return true;
        }
      }
  }
  return false;
}

class Graph{
public:
  std::map<int, int> disc;
  std::map<int, int> low;
  std::set<int> visited;
  std::map<int, int> parent;
  
  std::vector<std::vector<int>> conn;
  int ts;
  int ret;

  Graph(std::vector<std::vector<int>>& a_conn){
    conn = a_conn;
    ts = 0;
    ret = 0;
  }
  
  void dfs(int st){
    disc[st] = ts;
    low[st] = ts;
    ts++;
    visited.insert(st);
    for(int c = 0; c < conn.size(); ++c){
      if(conn[st][c] == 0) continue; 
      if(visited.count(c) == 0){
        parent[c] = st;
        dfs(c);
        if(low[c] > disc[st]){
          ret++;
        }
      }
      if(parent.count(st) == 0 || c != parent[st]){
        low[st] = std::min(low[st], low[c]);
      }
    }
    
  }
};


int singlePointOfFailure(std::vector<std::vector<int>> connections) {
  Graph g(connections);
  g.dfs(0);
  return g.ret;
}

