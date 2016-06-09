#include <map>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>
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

/*std::vector<TreeNode*> buildTree(std::vector<std::string> topics, int& i){
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
}*/
TreeNode* buildTree(std::string treeRepr){
    std::vector<std::string> topics;
    std::stringstream ss(treeRepr);
    std::copy(std::istream_iterator<std::string>(ss),
        std::istream_iterator<std::string>(),
        std::back_inserter(topics));

    std::vector<TreeNode*> stack;
    int i = 0;
    for(int i =0; i <= topics.size(); ++i){
        if(topics[i] == ")"){
                std::vector<TreeNode*> children;
                assert(stack.empty() == false);
                while(stack.back()->topic != "("){
                        children.push_back(stack.back());
                        stack.pop_back();
                }
                stack.pop_back();
                children.swap(stack.back()->children);
        }else if(!topics[i].empty()){
                TreeNode* node = new TreeNode(topics[i]);
                stack.push_back(node);
        }
    }
    assert(stack.size() == 1);
    return stack[0];
}


std::vector<int> ontology(std::string treeRepr, std::vector<std::string> questions, std::vector<std::string> queries) 
{
    using namespace std;
    /*vector<string> topics;
    stringstream ss(treeRepr);
    copy(istream_iterator<string>(ss),
        istream_iterator<string>(),
        back_inserter(topics));
    
    TreeNode* root = new TreeNode(topics[0]);
    int i = 1;
    root->children = buildTree(topics, i);
    */

    TreeNode* root =  buildTree(treeRepr);

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

int main(){
    std::string treestr = "n ( nnnZ ( x ( nnxnn ( xnhnnnz nnnnn ) nnnZZn ) nnnnZnn ( nnnxn ( xn ( nennx ( nnnxnnn ) ) ) nnn ( nn ( nnnnnnn ( znnnnnnx ) ) ) ) nnnnZz ) nnnx nnnnx nnnn )";
    std::vector<std::string> questions({"nennx: nnnnn", 
 "nnnnZz: nnnn", 
 "nnnnZz: nnnnnnnnn", 
 "nnnnZz: nznn", 
 "nnnZ: nnZn", 
 "nnnnZnn: nZn", 
 "nnnnZz: nnnnnn", 
 "nnnxnnn: nnnnn", 
 "znnnnnnx: nnnnxnnnn", 
 "x: nn", 
 "nnnxn: nxnnnnn", 
 "nnnnZz: nnnnxnn", 
 "xn: nnnnnnnnn", 
 "nnn: nnnnnn", 
 "nnnn: nn", 
 "nnn: nnnZnnzn", 
 "nnnn: xn", 
 "nnxnn: nnnnxnnn", 
 "nennx: nnnnZnnn", 
 "xnhnnnz: nn"});
    std::vector<std::string> queries({"nnnZ n"});
	auto ret = ontology(treestr, questions, queries);
	std::cout << ret[0] << std::endl;
}

