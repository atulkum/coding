#include<iostream>
#include<queue>
#include<vector>
#include<set>
using namespace std;
bool augumentPath(std::vector<std::vector<int>>& network,
                  std::vector<int>& path, int s, int t){
    std::set<int> visited;
    std::queue<int> q;
    visited.insert(s);
    q.push(s);
    path[s] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(u == t){
            break;
        }
        
        for(int v = 0 ;v < network.size(); ++v){
            if(visited.count(v) == 0 && network[u][v] > 0){
                q.push(v);
                path[v] = u;
                visited.insert(v);
            }
        }
    }
    
    return visited.count(t) > 0;
}
int calculateResidual(std::vector<std::vector<int>>& network,
                  const std::vector<int>& path, 
                      int s, int t){
        std::cout << "22" << std::endl;
    int v = t;
    int bottleneck = INT_MAX;
    int i =0;
    while(v != s){
        int u = path[v];
        std::cout << v << "=>" << u << std::endl;
        bottleneck =std::min(bottleneck,network[u][v]); 
        v = u;
    }
        std::cout << "24" << std::endl;
    v = t;
    while(v != s){
        int u = path[v];
        network[u][v] -=  bottleneck;
        network[v][u] +=  bottleneck;
        v = u;
    }
        std::cout << "23" << std::endl;
    return bottleneck;
}
 
int dataRoute(int resource, int server, std::vector<std::vector<int>> network) {
    int n = network.size();
    int maxFlow = 0;
    std::vector<int> path(n, -1);
    
    while(augumentPath(network, path, resource, server)){
        //calculate residual graph
        maxFlow += calculateResidual(network, path, resource, server);
        
    }
    return maxFlow;
}
int main(){
	std::vector<std::vector<int>> p(6, std::vector<int>(6, 0));
	p[0][1] = 2;
	p[0][2] = 4;
	p[0][3] = 8;
	p[1][3] = 9;
	p[2][5] = 10;
	p[3][5] = 10;
	
	p[3][2] = 6;
	p[4][0] = 10;
	p[4][1] = 10;
	dataRoute(4,5, p);
	return 0;
}
