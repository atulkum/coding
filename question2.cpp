#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <limits> 

using namespace std;

struct Node{
    int id,level,time,nChild;
    double exp,expParent;
    Node* parent;
    std::vector<Node*> children;
    
    Node(int _id, int _level, int _time, Node* _parent):
            id(_id),level(_level), time (_time), parent(_parent){}
    
    void calculateExpect(){
        nChild = children.size();
        exp = time;
        if(!children.empty()){
            double sum = 0;
            for(Node* node: children){
                sum += node->exp;
            }
            exp += sum/nChild;
        }
    }
    void calculateExpectWithParent(){
        if(parent == nullptr){
            expParent = exp;
        }else{
            nChild = nChild+1;
            double newParentExp = (parent->expParent - parent->time);
            newParentExp *= parent->nChild;
            newParentExp -= exp;
            if(parent->nChild > 1){
                newParentExp /= (parent->nChild-1);
            }
            newParentExp += parent->time;
            
            expParent = (exp - time)*children.size() + newParentExp;
            expParent /= nChild;
            expParent += time;
        }
    }
};
int relatedQuestions(int n, std::vector<int> timeToRead, std::vector<std::vector<int>> edges) {
    using namespace std;
    map<int, vector<int>> m;
    map<int, int> parent;
    int rootId = n-1;
    for(vector<int> e: edges){
        int from = e[0];
        int to = e[1];
        m[from].push_back(to);
        m[to].push_back(from);
        int minId = min(from, to);
        if( minId< rootId){
            rootId = minId;
        }
    }
    Node* root = new Node(rootId, 0, timeToRead[rootId], nullptr);
    queue<Node*> q;
    q.push(root);
    map<int, vector<Node*>> levelmap;
    set<int> visited;
    int level = -1;
    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        visited.insert(node->id);
        if(node->level > level){
            level = node->level;
        }
        levelmap[node->level].push_back(node);
        vector<int> children = m[node->id];
        for(int c : children){
            if(visited.count(c) ==0){
                Node* newNode = 
                    new Node(c, node->level +1, timeToRead[c], node);
                q.push(newNode);
                node->children.push_back(newNode);
            }
        }
    }
    
    for(int i = level; i >=0 ; --i){
        vector<Node*> levMap = levelmap[i];
        for(Node * node: levMap){
            node->calculateExpect();
        }
    }
    
    double minx = std::numeric_limits<double>::max();
    int mini = -1;
    for(int i = 0; i <= level ; ++i){
        vector<Node*> levMap = levelmap[i];
        for(Node * node: levMap){
            node->calculateExpectWithParent();
            if(node->expParent <minx ){
                minx = node->expParent;
                mini = node->id;
            }
        }
    }
    return mini;
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    std::vector<int> timeToRead(n);
    for(int i = 0 ; i < n; ++i){
        cin >> timeToRead[i];
    }
    std::vector<std::vector<int>> edges;
    for(int i = 0 ; i < n-1; ++i){
        std::vector<int> tmp(2);
        cin >> tmp[0] >> tmp[1];
        tmp[0]--; tmp[1]--;
        edges.push_back(tmp);
    }
    cout << relatedQuestions(n,timeToRead,  edges)+1 << endl;
    return 0;
}
