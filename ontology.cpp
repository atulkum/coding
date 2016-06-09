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
	//std::cout << root->topic << " " << query << " " << question <<std::endl;
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
    //std::cout << root->topic<< "===="  <<std::endl;
    for(TreeNode* child:root->children){
    	std::cout << " " << child->topic;
    } 
	std::cout <<std::endl;
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
TreeNode* buildTree1(std::string treeRepr){
    std::vector<std::string> topics;
    std::stringstream ss(treeRepr);
    std::copy(std::istream_iterator<std::string>(ss),
        std::istream_iterator<std::string>(),
        std::back_inserter(topics));

    std::vector<TreeNode*> stack;
    int i = 0;
    bool processed = false;
    for(int i =0; i <= topics.size(); ++i){
        if(topics[i] == ")"){
		processed = true;
                std::vector<TreeNode*> children;
                assert(stack.empty() == false);
                while(stack.back()->topic != "("){
                        children.push_back(stack.back());
                        stack.pop_back();
                }
                stack.pop_back();
		for(TreeNode* t: children){
                	stack.back()->children.push_back(t);
		}
        }else if(!topics[i].empty()){
		if(topics[i] == "(" && processed){
                	TreeNode* node = new TreeNode("*");
                	stack.push_back(node);
		}
		processed = false;
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
    vector<string> topics;
    stringstream ss(treeRepr);
    copy(istream_iterator<string>(ss),
        istream_iterator<string>(),
        back_inserter(topics));
    
    //TreeNode* root = new TreeNode(topics[0]);
    //int i = 1;
    //root->children = buildTree(topics, i);
    

    TreeNode* root =  buildTree1(treeRepr);

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
std::string treeRepr = "Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )";
std::vector<std::string> questions= {"Reptiles: Why are many reptiles green?", 
 "Birds: How do birds fly?", 
 "Eagles: How endangered are eagles?", 
 "Pigeons: Where in the world are pigeons most densely populated?", 
 "Eagles: Where do most eagles live?"};
std::vector<std::string> queries = {"Eagles How en", 
 "Birds Where", 
 "Reptiles Why do", 
 "Animals Wh"};
 	/*std::cout << "=========" << std::endl;
	for(int i : ontology(treeRepr, questions, queries)) std::cout << i << ", " ;
 	std::cout << "=========" << std::endl;
	*/
treeRepr= "A ( B ( C D E ) ( F G ( H I J ) ) )";
questions ={"A: ABC?", 
 "B: A?", 
 "C: A B C?", 
 "D: ?", 
 "E: Where is it?", 
 "F: How are you?", 
 "G: You you you?", 
 "H: You are not?", 
 "I: Where do you live?", 
 "J: Where did he live?"};
queries= {
/*"A A B C?",
 "A A", 
 "G You ", 
 "E W", 
 "B W", 
 "B Whe", 
 "A T", 
 "A t", 
 "C C", 
 "C CO",*/ 
 "G W"};
 	std::cout << "=========" << std::endl;
	for(int i : ontology(treeRepr, questions, queries)) std::cout << i << ", " ;
 	std::cout << "=========" << std::endl;
/*[1, 3, 2, 1, 1, 1, 0, 0, 0, 0, 2]*/
/*0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 2*/
/*
treeRepr= "A";
questions = {"A: WTF?", 
 "A: Oh, really?", 
 "A: Man, how did you do it?", 
 "A: Right?"};
queries= {"A W", 
 "A R", 
 "A R", 
 "A W", 
 "A Oh", 
 "A Man"};
 	std::cout << "=========" << std::endl;
	for(int i : ontology(treeRepr, questions, queries)) std::cout << i << ", " ;
 	std::cout << "=========" << std::endl;

treeRepr = "n ( nnnZ ( x ( nnxnn ( xnhnnnz nnnnn ) nnnZZn ) nnnnZnn ( nnnxn ( xn ( nennx ( nnnxnnn ) ) ) nnn ( nn ( nnnnnnn ( znnnnnnx ) ) ) ) nnnnZz ) nnnx nnnnx nnnn )";
questions = {"nennx: nnnnn", 
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
 "xnhnnnz: nn"};
queries = {"nn x", 
 "nnxnn n", 
 "nnnZZn n", 
 "xnhnnnz n", 
 "nnnZ n", 
 "nnnZZn n", 
 "nnnx n", 
 "nnnnZz n", 
 "nnnnx n", 
 "nnn n", 
 "nnn n", 
 "nnnn z", 
 "nnnZ n", 
 "nnnn n", 
 "nn x", 
 "nnnnnnn n", 
 "nnnnx n", 
 "x n", 
 "x n", 
 "znnnnnnx n", 
 "nnnxnnn x", 
 "znnnnnnx n", 
 "nnnZ n", 
 "xn Z", 
 "n n", 
 "nnnnZnn n", 
 "n n", 
 "nnnZZn Y", 
 "znnnnnnx n", 
 "nnnnx n", 
 "nnnn n", 
 "nn n", 
 "xnhnnnz Z", 
 "nnnnnnn x", 
 "nnnnn x", 
 "nnnZ n", 
 "nnxnn n", 
 "nnnnn x", 
 "nnnnnnn n", 
 "xnhnnnz n", 
 "nnnnn n", 
 "nennx n", 
 "x n", 
 "xn n", 
 "nnn n", 
 "znnnnnnx n", 
 "znnnnnnx n", 
 "nnnnn n", 
 "x n", 
 "nnnx n", 
 "nnnZZn n", 
 "nnnn n", 
 "x n", 
 "nnnxn n", 
 "nnnnZz n", 
 "n n", 
 "nnnnnnn n", 
 "nnnZZn n", 
 "n x", 
 "nnn n", 
 "nn x", 
 "nnnxn n", 
 "n n", 
 "nnnnnnn n", 
 "nnxnn n", 
 "x n", 
 "nnnZZn n", 
 "nnnnZnn n", 
 "nnnxnnn n", 
 "nnxnn n", 
 "nnnnZz n", 
 "nennx n", 
 "xn n", 
 "nennx x", 
 "nnnnn Z", 
 "nnnxn n", 
 "nnnnZnn n", 
 "nnnnnnn n", 
 "nnnnZz n", 
 "nnn n", 
 "nnnnnnn n", 
 "nnnnn n", 
 "nnnZ n", 
 "nnnnx n", 
 "xn n", 
 "nnnZ n", 
 "x n", 
 "nnnZZn n", 
 "nnnnx n", 
 "nnnnZnn n", 
 "xnhnnnz x", 
 "znnnnnnx n", 
 "nnnnn z", 
 "x x", 
 "nennx n", 
 "nnxnn x", 
 "xn n", 
 "n n", 
 "nnnZZn n", 
 "xn n", 
 "nnnx n", 
 "nennx n", 
 "nnnnx n", 
 "xnhnnnz n", 
 "xn n", 
 "nnnxn Z", 
 "n n", 
 "nnnnnnn n", 
 "nnnn n", 
 "nennx n", 
 "nnnnx n", 
 "nnn n", 
 "n i", 
 "nnnnZz n", 
 "nnnx n", 
 "n Z", 
 "n n", 
 "nnnnx z", 
 "xn n", 
 "nnnnx n", 
 "znnnnnnx n", 
 "nnnnZz x", 
 "znnnnnnx n", 
 "nnnn n", 
 "nnnZ n", 
 "xn n", 
 "nnnnn n", 
 "x n", 
 "x n", 
 "znnnnnnx n", 
 "nnnxnnn n", 
 "nnnnnnn n", 
 "nnnnx n", 
 "nn n", 
 "nnnZ n", 
 "znnnnnnx h", 
 "nnnxnnn x", 
 "xnhnnnz Z", 
 "nnnnn n", 
 "nnnZZn n", 
 "nnnnZnn n", 
 "nnnn n", 
 "nnnx n", 
 "nnnnx n", 
 "nn n", 
 "nnnZZn x", 
 "nnxnn n", 
 "nnxnn n", 
 "nnnxnnn z", 
 "nennx n", 
 "nnnZ n", 
 "nnnZZn n", 
 "nnnZZn n", 
 "nnnnn n", 
 "nennx n", 
 "xnhnnnz n", 
 "nnnx n", 
 "nnnnZnn n", 
 "nnn n", 
 "xnhnnnz n", 
 "nnnxn n", 
 "nn n", 
 "xnhnnnz n", 
 "nnnnn Z", 
 "nnnnn n", 
 "nnnnn n", 
 "xnhnnnz Z", 
 "nnn n", 
 "xn n", 
 "nnnnZnn n", 
 "nennx n", 
 "nnnnZz n", 
 "nnnnnnn n", 
 "nnxnn n", 
 "x n", 
 "xnhnnnz n", 
 "x n", 
 "nnnnn n", 
 "nnnZ n", 
 "nnnxn n", 
 "nnnnx n", 
 "nnnxn n", 
 "nnnnx n", 
 "nnnn n", 
 "nnnnZz n", 
 "nnnn n", 
 "x n", 
 "nnnnZnn n", 
 "nnnnn x", 
 "nnnnZnn n", 
 "nennx n", 
 "nnnnnnn n", 
 "nnnnZz Z", 
 "nnnn x", 
 "nnnxn n", 
 "nnnn n", 
 "xn n", 
 "nnnx n", 
 "nnxnn x", 
 "znnnnnnx n"};
 	std::cout << "=========" << std::endl;
	for(int i : ontology(treeRepr, questions, queries)) std::cout << i << ", " ;
 	std::cout << "=========" << std::endl;
*/
}

