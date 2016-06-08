struct TreeNode{
    std::string topic;
    std::vector<TreeNode*> children;
    TreeNode(std::string _topic):topic(_topic){}
};

bool isPrefix(std::string ques, std::string query){
    int i = 0;
    while(i < std::min(ques.size(), query.size()) 
          && ques[i] == query[i]){
        i++;
    }
    return i == query.size();
}
int countQuery(TreeNode* root, std::string query, 
                std::map<std::string, std::vector<std::string>>& topic2question){
    if(root == nullptr){
        return 0;
    }
    int ret = 0;
    for(std::string question: topic2question[root->topic]){
        std::cout <<root->topic<< " " <<question << " countQuery " << query <<std::endl ;
        if(isPrefix(question, query)){
            ret++;
        }
    }
    for(TreeNode* child:root->children){
        ret += countQuery(child, query, topic2question);
    }
    return ret;
}
TreeNode* findTopic(TreeNode* root, std::string& topic){
    if(root == nullptr){
        return nullptr;
    }
    if(root->topic == topic){
        return root;
    }
    
    for(TreeNode* child:root->children){
        TreeNode* ret = findTopic(child, topic);
        if(ret != nullptr){
            return ret;
        }
    }
    return nullptr;
}

std::vector<TreeNode*> buildTree(std::vector<std::string> topics, int& i){
    std::vector<TreeNode*> ret;
    if(i < topics.size() && topics[i] !="("){
        //something wrong
    }   
    i++;
    while(i < topics.size() && topics[i] != ")"){
        TreeNode* node = new TreeNode(topics[i]);
        if(i +1< topics.size() && topics[i+1] == "("){
            i++;
            node->children = buildTree(topics, i);
        }
        ret.push_back(node);
        i++;
    }
    i++;
    return ret;
}

std::vector<int> ontology(std::string treeRepr, std::vector<std::string> questions, std::vector<std::string> queries) 
{
    using namespace std;
    vector<string> topics;
    stringstream ss(treeRepr);
    copy(istream_iterator<string>(ss),
        istream_iterator<string>(),
        back_inserter(topics));
    
    
    TreeNode* root = new TreeNode(topics[0]);
    int i = 1;
    root->children = buildTree(topics, i);
    
    map<string, vector<string>> topic2question;
    for(string quesstr: questions){
        size_t pos = quesstr.find(":");
        string topic = quesstr.substr(0, pos);
        string ques = quesstr.substr(pos+2);
        topic2question[topic].push_back(ques);
    }
    vector<int> ret(queries.size(), 0);
    
    for(int k = 0; k < queries.size(); ++k){
        string querystr = queries[k];
        size_t pos = querystr.find(" ");
        string topic = querystr.substr(0, pos);
        string query = querystr.substr(pos+1);
        TreeNode* topicNode = findTopic(root, topic);
        ret[k] = countQuery(topicNode, query, topic2question);
    }
    return ret;
}
