#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <sstream>
#include <iterator>
#include <string>
#include <set>

struct Utils{
    static int ts;
    static std::vector<std::string> getToekens(const std::string& fullText){
        std::string text(fullText);
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);
        std::vector<std::string> tokens;
        std::stringstream ss(text);
        std::copy(std::istream_iterator<std::string>(ss),
            std::istream_iterator<std::string>(),
            std::back_inserter(tokens));
        return tokens;
    }
    static std::string getTextFromToken(const std::vector<std::string> & tokens){
        std::ostringstream oss;
        std::copy(tokens.begin(), tokens.end(),
                  std::ostream_iterator<std::string>(oss, " "));
        return oss.str();
    }
};

int Utils::ts = 0;

class Trie{
private:
    struct TrieNode{
        char c;
        std::map<char, std::shared_ptr<TrieNode>> children;
        std::set<std::string> ids;
        TrieNode(char _c):c(_c){}
    };
    
    std::shared_ptr<TrieNode> root;
    
public:
    
    Trie(): root(std::make_shared<TrieNode>('*')){}

    std::set<std::string> queryResult(const std::string& text){
        std::set<std::string> allIds;
        bool isFirst = true;
        auto tokens = Utils::getToekens(text);
        for(const std::string& token: tokens){
            std::set<std::string> idsForToken = hasPrefix(token);
            if(idsForToken.empty()){
                return idsForToken;
            }
            if(isFirst){
                isFirst = false;
                allIds = idsForToken;
            }else{
                std::set<std::string> intersect;
                std::set_intersection(
                    allIds.begin(),allIds.end(),
                    idsForToken.begin(),idsForToken.end(),
                    std::inserter(intersect, intersect.end()));
                allIds.swap(intersect);
            }
        }
        return allIds;
    }
    void addText(const std::string& id, const std::string& text){
        auto tokens = Utils::getToekens(text);
        for(const std::string& token: tokens){
            addToken(id, token);
        }
    }
    void addToken(const std::string& id, const std::string& token){
        auto curr = root;
        for(int i = 0; token.length() > i; ++i){
            if(curr->children.count(token[i]) == 0){
                curr->children[token[i]] = std::make_shared<TrieNode>(token[i]);
            }
            curr = curr->children[token[i]];
            curr->ids.insert(id);
        }
    }
    const std::set<std::string> hasPrefix(const std::string& token){
        auto curr = root;
        for(int i = 0; token.length() > i; ++i){
            if(curr->children.count(token[i]) == 0){
                return std::set<std::string>();
            }
            curr = curr->children[token[i]];
        }
        return curr->ids;
    }
};

class TypeaheadSearch{
    private:
        struct UserInfo{
            double score;
            int timestamp;
            std::string id;
            std::string type;
            
            UserInfo(const std::string& _type, const std::string& _id, 
                 double _score, int _timestamp) :type(_type), id(_id), 
                                    score(_score), timestamp(_timestamp){}
        };
        std::map<std::string, std::shared_ptr<UserInfo>> userDb;
        std::shared_ptr<Trie> index;
    public:
        TypeaheadSearch(): index(std::make_shared<Trie>()){}
    
        void processAdd(const std::string& type, const std::string& id, double score, const std::string& text){
            userDb[id] = std::make_shared<UserInfo>(type, id, score, Utils::ts++);
            index->addText(id, text);
        }
        void processDelete(const std::string& id){
            userDb.erase(id);
        }
        std::vector<std::string> processSearch(int numResult, const std::string& query){
            std::map<std::string, double> typeBoostMap;
            return processBoostedSearch(typeBoostMap, numResult, query);
        }
        
        std::vector<std::string> processBoostedSearch(const std::map<std::string, double>& typeBoostMap,
                                              int numResult, const std::string& query){
            
            std::vector<std::string> queryResult;
            if(numResult > 0 && !query.empty()){
                std::vector<std::shared_ptr<UserInfo>> result;
                std::set<std::string> results = index->queryResult(query);
                for(const std::string& id:results){
                    if(userDb.count(id) > 0){
                        result.push_back(userDb[id]);
                    }
                }
                std::sort(result.begin(), result.end(), 
                          [&typeBoostMap](std::shared_ptr<UserInfo> a,  std::shared_ptr<UserInfo> b){
                    double ascore = a->score;
                    double bscore = b->score;
                    if(!typeBoostMap.empty()){
                        if(typeBoostMap.count(a->type) > 0){
                            ascore *= typeBoostMap.at(a->type);
                        }
                        if(typeBoostMap.count(b->type) > 0){
                            bscore *= typeBoostMap.at(b->type);
                        }
                    }
                    if(ascore == bscore) {
                        return a->timestamp > b->timestamp;
                    }else{
                        return ascore > bscore;
                    }
                });
                
                for(auto t: result){
                    queryResult.push_back(t->id);
                    if(--numResult == 0){
                        break;
                    }
                }
            }
            return queryResult;
        }
};


int main() {
    std::unique_ptr<TypeaheadSearch> typeAheadSearch(new TypeaheadSearch());
    int N;
    std::cin >> N;
    std::string line;
    std::getline(std::cin, line);
    while(N-- > 0){
        std::getline(std::cin, line);
        std::size_t pos = line.find(" ");
        std::string command = line.substr(0, pos);
        pos++;
        if(command == "ADD"){
            std::size_t pos1 = line.find(" ", pos);
            std::string type = line.substr(pos, pos1-pos);
            pos1++;
            std::size_t pos2 = line.find(" ", pos1);
            std::string id = line.substr(pos1, pos2-pos1);
            pos2++;
        
            std::size_t pos3 = line.find(" ", pos2);
            double score = std::stod(line.substr(pos2, pos3-pos2));
            pos3++;
            
            std::string text = line.substr(pos3);
            typeAheadSearch->processAdd(type, id, score, text);
        }else if(command == "DEL"){
            std::size_t pos1 = line.find(" ", pos);
            std::string id = line.substr(pos, pos1-pos);
            typeAheadSearch->processDelete(id);
        }else if(command == "QUERY"){
            std::size_t pos1 = line.find(" ", pos);
            int numResult = std::stoi(line.substr(pos, pos1-pos));
            pos1++;
            std::string query = line.substr(pos1);
            auto searchResult = typeAheadSearch->processSearch(numResult, query);
            std::cout << Utils::getTextFromToken(searchResult) << std::endl;
        }else if(command == "WQUERY"){
            std::size_t pos1 = line.find(" ", pos);
            int numResult = std::stoi(line.substr(pos, pos1-pos));
            pos1++;
            std::size_t pos2 = line.find(" ", pos1);
            int numBoost = std::stoi(line.substr(pos1, pos2-pos1));
            pos2++;
            std::map<std::string, double> typeBoostMap; 
            while(numBoost-- > 0){
                std::size_t pos3 = line.find(" ", pos2);
                std::string boost = line.substr(pos2, pos3-pos2);
                pos2 = pos3+1;
                
                std::size_t boostPos = boost.find(":");
                std::string boostType = boost.substr(0, boostPos);
                double boostScore = std::stod(boost.substr(boostPos+1));
                typeBoostMap[boostType] = boostScore;
            }
            std::string query = line.substr(pos2);
            auto searchResult = typeAheadSearch->processBoostedSearch(typeBoostMap, numResult, query);
            std::cout << Utils::getTextFromToken(searchResult) << std::endl;
        }                     
    }     
    return 0;
}
