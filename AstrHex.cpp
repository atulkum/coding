int d[6][2] ={{0, -1},{1,0}, {-1,1},{-1, 0},{1,-1},{0,1}}; 


struct Node{
    int x,y, dist, kdist;
    
    void setdistnace(std::vector<int>& cp){
        int xd = std::abs(cp[0] - x);
        int yd = std::abs(cp[1] - y);
        int z1 = -(x+y);
        int z2 = -(cp[0] + cp[1]);
        int zd= std::abs(z1-z2);
        //kdist = std::max(std::max(xd, yd), zd);
        kdist = zd + xd + yd;
    }
};
struct mycomp{
     bool operator()(const Node* n1, const Node* n2) const {
         return n1->kdist > n2->kdist;
     };
};

typedef std::priority_queue<Node*, std::vector<Node*>, mycomp> myq;
int processStep(myq& q, int k, 
    std::vector<int>& cp, std::vector<std::vector<int>>& imp){
    if(q.empty()){
        return -1;
    }
    Node* n =q.top();
    int x = n->x;
    int y = n->y;
    int nd = n->dist;
    std::cout << n->kdist << "====" <<std::endl;
    q.pop();
    delete n;
    
    if(x == cp[0] && y == cp[1]){
        return nd;
    }
    
    for(int i = 0 ; i< 6; ++i){
        Node* nn = new Node();
        nn->x = x + d[i][0];
        nn->y = y + d[i][1];
        nn->dist = nd + k;
        bool blocked = false;
        for(std::vector<int>& i:imp){
            if(nn->x == i[0] && nn->y == i[1]){
                blocked = true;
                break;
            }
        }
        if(!blocked){
            nn->setdistnace(cp);
            q.push(nn);
        }
    }
    return -1;
}
void init(std::vector<int>& start,  
          myq& q, std::vector<int>& cp){
    Node* st = new Node();
    st->x=start[0];
    st->y=start[1];
    st->dist = 0;
    st->setdistnace(cp);
    q.push(st);
}
bool farmingResources(std::vector<int> f, std::vector<int> e, std::vector<int> cp, std::vector<std::vector<int>> imp) {
   

    myq q1;
    int k1 = f[2];
   
    myq q2;
    int k2 = e[2];
    
    init(f, q1,cp);
    init(e, q2, cp);
    
    bool done1 = false;
    bool done2 = false;
    int fdist = 0;
    int edist = 0;
    int i = 0;
    while(true){
        if(!done1){
            fdist = processStep(q1, k1, cp, imp);
            if(fdist > 0){
                done1 = true;
            }
        }
        if(!done2){
            edist = processStep(q2, k2, cp, imp);
            if(edist > 0){
                done2 = true;
            }
        }
        if(done1 && fdist < edist){
            return true;
        }
        if(done2 && fdist >= edist){
            return false;
        }
        i++;
        //std::cout << i <<" never reached " << std::endl;
    }
    //std::cout << " never reached " << std::endl;
    return false;
}

