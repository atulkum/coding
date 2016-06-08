struct TreeNode{
    std::string topic;
    std::vector<TreeNode*> children;
    TreeNode(std::string _topic):topic(_topic){}
    
};

bool isPrefix(std::string  ques, std::string query){
    int i = 0;
    while(i < std::min(ques.size(), query.size()) 
          && ques[i] == query[i]){
        i++;
    }
    return i == query.size();
}
void countQuery(TreeNode* root, std::string q, 
                std::map<string, TreeNode*>& topic2question, 
                std::vector<int>& ret, int i){
    if(root == nullptr){
        return;
    }
    if(isPrefix(topic2question[root->topic], q)){
        ret[i]++;
    }
    for(TreeNode* child:root->children){
        countQuery(child, q, topic2question, ret, i);
    }
}
TreeNode* findTopic(TreeNode* root, std::string& topic){
    if(root == nullptr){
        return nullptr;
    }
    
    for(TreeNode* child:root->children){
        if(child->topic == topic){
            return child;
        }else{
            return findTopic(child, topic);
        }
    }
    return nullptr;
}
std::vector<int> ontology(std::string treeRepr, std::vector<std::string> questions, std::vector<std::string> queries) 
{
    using namespace std;
    
    string token = "";
    int i = 0;
    
    TreeNode* root = new TreeNode("*");
    for(char c: treeRepr){
        
    }
    //build tree
    root.children = buildTree(treeRepr, i);
    
    map<string, TreeNode*> topic2question;
    for(string ques: questions){
        size_t pos = ques.find(":");
        string topic = ques.substr(0, pos);
        string q = ques.substr(pos+2);
        topic2question[topic] = q;
    }
    vector<int>  ret(queries.size(), 0);
    int i = 0; 
    for(string query: queries){
        size_t pos = query.find(" ");
        string topic = ques.substr(0, pos);
        string q = ques.substr(pos+1);
        TreeNode* topicNode = findTopic(root, topic);
        countQuery(topicNode, q, topic2question, ret,i);
        i++;
    }
    return ret;
}
