#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <unordered_map>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iterator>
#include <unordered_set>

using namespace std;

int countQuery(std::string query, vector<int>& questions,vector<string>& questionId){
    unordered_set<int> ques;
    for(int i = 0; i <  query.size(); ++i){
        for(int j = 0 ; j < questions.size(); j++){
            if(i >= questionId[questions[j]].length() || questionId[questions[j]][i] != query[i]){
                ques.insert(j);
            }
        }
    }
    return questions.size() - ques.size();
}

void buildTree(vector<int>& treeTopics, 
                   unordered_map<int, vector<int>>& topic2question,
                   unordered_map<int, vector<int>>& topic2Allquestion){
    
    unordered_map<int, vector<int>> topic2children;
    std::vector<int> stack;
    bool processed = false;
    for(int i =0; i < treeTopics.size(); ++i){
        if(treeTopics[i] == -2){
		  processed = true;
          std::vector<int> children;
          while(stack.back() != -1){
                children.push_back(stack.back());
                stack.pop_back();
          }
          stack.pop_back();
		  for(int t: children){
            topic2children[stack.back()].push_back(t);
            topic2Allquestion[stack.back()].insert(topic2Allquestion[stack.back()].end(), 
                                                   topic2Allquestion[t].begin(),
                                                   topic2Allquestion[t].end());
		  }
        }else{
		      if(treeTopics[i] == -1 && processed){
                	stack.push_back(-5);
		      }
		      processed = false;
              vector<int> ques = topic2question[treeTopics[i]];
              topic2Allquestion[treeTopics[i]].insert(topic2Allquestion[treeTopics[i]].end(), 
                                                  ques.begin(), ques.end());
            
              stack.push_back(treeTopics[i]);
        }
    }
}

int main() {
    vector<int> treeTopics; 
    unordered_map<string, int> topic2Id;
    {
        int M;
        cin >> M;
   
        std::string treeRepr;
        getline(cin, treeRepr);
        getline(cin, treeRepr);
        
        std::vector<std::string> topics;
        std::stringstream ss(treeRepr);
        std::copy(std::istream_iterator<std::string>(ss),
            std::istream_iterator<std::string>(),
            std::back_inserter(topics));
        
        int i = 0;
        for(string t: topics){
            if(!t.empty() && t != "(" && t != ")"){
                topic2Id[t] = i;
                treeTopics.push_back(i);
                i++;
            }else if(t == "("){
                treeTopics.push_back(-1);
            }else if(t == ")"){
                treeTopics.push_back(-2);
            }
        }
    }
    vector<string> questionId;
    unordered_map<int, vector<int>> topic2Allquestion;
    {
        int N;
        cin >> N;
        string tmp;
        getline(cin, tmp);
        unordered_map<int, vector<int>> topic2question;
        string quesstr;
        for(int k = 0 ; k < N; ++k){
            getline(cin, quesstr);
            size_t pos = quesstr.find(":");
            string topic = quesstr.substr(0, pos);
            string ques = quesstr.substr(pos+2);
            questionId.push_back(ques);
            topic2question[topic2Id[topic]].push_back(k);
        }
        buildTree(treeTopics, topic2question, topic2Allquestion);
        treeTopics.clear();
    }
    int K;
    {
        cin >> K;
        string tmp;
        getline(cin, tmp);
    }
    string querystr;
    for(int i = 0 ; i < K; ++i){
        getline(cin, querystr);
        size_t pos = querystr.find(" ");
        string topic = querystr.substr(0, pos);
        string query = querystr.substr(pos+1);
        
        cout << countQuery(query, topic2Allquestion[topic2Id[topic]], questionId) << std::endl ;
    }
    return 0;
}
