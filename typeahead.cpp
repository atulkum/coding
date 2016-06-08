struct TrieNode{
    char c;
    std::map<char, TrieNode*> children;
    bool isEnd;
    TrieNode(char _c):c(_c){}
};
struct Trie{
    TrieNode* root = new TrieNode('*');
    double score;
    int ts;
    std::string user;
    std::string text;
    
    Trie(std::string _user, double _score, std::string _text, int _ts)
        :user(_user),score(_score), ts(_ts),text(_text){
        addText(_text);
    }
    
    bool queryResult(std::string text){
        using namespace std;
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        vector<string> tokens;
        stringstream ss(text);
        copy(istream_iterator<string>(ss),
            istream_iterator<string>(),
            back_inserter(tokens));
        //cout << "======" << this->text << endl;
        for(string s: tokens){
            if(!getPrefix(s)){
                return false;
            }
        }
        return true;
    }
    void addText(std::string text){
        using namespace std;
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        vector<string> tokens;
        stringstream ss(text);
        copy(istream_iterator<string>(ss),
            istream_iterator<string>(),
            back_inserter(tokens));
         //cout << "======" << this->text << endl;
        for(string s: tokens){
            add(s);
        }
        
    }
    void add(std::string str){
        using namespace std;
        TrieNode* curr = root;
        int i = 0;
        //cout << str << endl;
        while(str.length() > i){
            //cout << str[i] << endl;
            if(curr->children.count(str[i]) == 0){
                TrieNode* node = new TrieNode(str[i]);
                curr->children[str[i]] = node;
            }
            curr = curr->children[str[i]];
            i++;
        }
        curr->isEnd = true;
    }
    const bool getPrefix(const std::string& str){
        using namespace std;
        TrieNode* curr = root;
        int i = 0;
        //cout << str << endl;
        while(str.length() > i){
            //cout << str[i] << endl;
            if(curr->children.count(str[i]) == 0){
                return false;
            }
            curr = curr->children[str[i]];
            i++;
        }
        return true;
    }
};
std::vector<std::vector<std::string>> typeaheadSearch(std::vector<std::vector<std::string>> queries) {
    std::vector<std::vector<std::string>> ret;
    using namespace std;
    int ts = 0;
    map<string, Trie*> database;
    for(const vector<string>& q: queries){
        if(q[0] == "ADD"){
            Trie* node = new Trie(q[2], stod(q[3]),q[4], ts++);
            database[q[2]] = node;
        }else if(q[0] == "DEL"){
            delete database[q[1]];
            database.erase(q[1]);
        }else if(q[0] == "QUERY"){
            int num = stoi(q[1]);
            vector<string> ret1;
            if(num > 0 && !q[2].empty()){
                string query = q[2];
                vector<Trie*> result;
                for(const auto& dbrow:database){
                    if(dbrow.second->queryResult(query)){
                        result.push_back(dbrow.second);
                    }
                }
                sort(result.begin(), result.end(), [](Trie* a, Trie* b){
                    if(a->score == b->score) {
                        return a->ts > b->ts;
                    }else{
                        return a->score > b->score;
                    }
                });
                
                for(Trie* t: result){
                    ret1.push_back(t->user);
                    if(--num == 0){
                        break;
                    }
                }
            }
            ret.push_back(ret1);
        }                      
    }    
    return ret;
}
