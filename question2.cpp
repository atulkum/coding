struct Node{
    int id,level,t,nChild;
    double exp,expParent;
    Node* parent;
    std::vector<Node*> children;
    
    Node(int _id, int _level, int _t, Node* _parent){
        id = _id; level = _level;  t = _t; parent = _parent;
    }
    void calculateExpect(){
        nChild = children.size();
        exp = t;
        if(!children.empty()){
            double sum = 0;
            for(Node* node: children){
                sum += node->exp;
            }
            exp += sum/nChild;
        }
    }
    void calculateExpectWithParent(){
        using namespace std;
        if(parent == nullptr){
            expParent = exp;
        }else{
            double newParentExp = (parent->expParent - parent->t)*parent->nChild;
            newParentExp -= exp;
            if(parent->nChild > 1){
                newParentExp /= (parent->nChild-1);
            }
            newParentExp += parent->t;
            
            nChild = nChild+1;
            
            expParent = (exp - t)*children.size() + newParentExp;
            expParent /= nChild;
            expParent += t;
            
        }
    }
};
int relatedQuestions(int n, std::vector<int> t, std::vector<std::vector<int>> edges) {
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
    Node* root = new Node(rootId, 0, t[rootId], nullptr);
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
                    new Node(c, node->level +1, t[c], node);
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
