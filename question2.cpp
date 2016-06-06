struct Node{
    int id;
    int level;
    int t;
    Node* parent;
    double exp;
    double expParent;
    std::vector<Node*> children;
    Node(int _id, int _level, int _t, Node* _parent){
        id = _id;
        level = _level;
        t = _t;
        parent = _parent;
    }
    void calculateExpect(){
        exp = t;
        if(!children.empty()){
            double sum = 0;
            for(Node* node: children){
                sum += node->exp;
            }
            exp += sum/children.size();
        }
    }
    void calculateExpectWithParent(){
        using namespace std;
        if(parent == nullptr){
            expParent = exp;
        }else{
            double newParentExp = (parent->expParent - parent->t)*(parent->children.size()+1);
            newParentExp -= exp;
            if(parent->children.size() > 0){
                newParentExp /= parent->children.size();
            }
            newParentExp += parent->t;
            expParent = (exp - t)*children.size() + newParentExp;
            expParent /= (children.size()+1);
            expParent += t;
            
        }
    }
};
int relatedQuestions(int n, std::vector<int> t, std::vector<std::vector<int>> edges) {
    using namespace std;
    map<int, vector<int>> m;
    map<int, int> parent;
    for(vector<int> e: edges){
        m[e[0]].push_back(e[1]);
    }
    
    Node* root = new Node(0, 0, t[0], nullptr);
    queue<Node*> q;
    q.push(root);
    map<int, vector<Node*>> levelmap;
    int level = -1;
    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        if(node->level > level){
            level = node->level;
        }
        levelmap[node->level].push_back(node);
        vector<int> children = m[node->id];
        for(int c : children){
            Node* newNode = new Node(c, node->level +1, t[c], node);
            q.push(newNode);
            node->children.push_back(newNode);
        }
    }
    
    for(int i = level; i >=0 ; --i){
        vector<Node*> levMap = levelmap[i];
        
        for(Node * node: levMap){
            cout << node->id << " ";
            node->calculateExpect();
        }
        cout <<endl;
    }
    double minx = INT_MAX;
    int mini = -1;
    for(int i = 0; i <= level ; ++i){
        vector<Node*> levMap = levelmap[i];
        for(Node * node: levMap){
            node->calculateExpectWithParent();
            //cout << node->id << " " << node->expParent<< " "<< node->exp << endl;
            if(node->expParent <minx ){
                minx = node->expParent;
                mini = node->id;
            }
        }
    }
    return mini;
    
}
