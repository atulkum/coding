#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <iostream>

struct AhoCorasick{
    std::map<int, std::map<char, int>> fsa;
    std::map<int, int> link;
    std::map<int, std::set<int>> out;
    int curr_state_id = 1;

    void insert_word(const std::string& w, int idx){
        int state = 0;
        for(char c: w){
            if(fsa.count(state) == 0 || fsa[state].count(c) == 0){
                fsa[state][c] = curr_state_id++;
            }
            state = fsa[state][c];
        }
        out[state].insert(idx);
    }

    void fix_failure_link(){
        std::queue<int> q;
        std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for(char c: alphabet){
            if(fsa[0].count(c) == 0){
                //create self loop for char which are not
                //present in path from root
                fsa[0][c] = 0;
            }else{
                q.push(fsa[0][c]);
                link[fsa[0][c]] = 0;
            }
        }
        while(!q.empty()){
            int state = q.front();
            q.pop();
            for(const auto& e:fsa[state]){
                char c = e.first;
                int next_state = e.second;
                q.push(next_state);

                int f = link[state];
                while(f!= 0 && fsa[f].count(c) == 0){
                    f = link[f];
                }
                if(fsa[f].count(c) > 0){
                    f = fsa[f][c];
                }
                link[next_state] = f;
                
                if(out.count(f) > 0){
                    auto &out_failure = out[f];
                    out[next_state].insert(out_failure.begin(), out_failure.end());
                }
            }
        }
    }
    std::vector<int> search(const std::string& s){
        std::vector<int> ret;
        int f = 0;
        for(int i =0; i < s.length(); ++i){
            char c = s[i];
            while(f != 0 && fsa[f].count(c) == 0){
                f = link[f];
            }
            f = fsa[f][c];
            if(out.count(f) > 0){
                ret.insert(ret.end(), out[f].begin(), out[f].end());
            }
        }
        return ret;
    }
    std::string search_longest(const std::string& w,
                              std::vector<std::string> parts){
        int len = 0;
        int end_id = -1;
        std::string part = ""; 
        int f = 0;
        for(int i =0; i < w.length(); ++i){
            char c = w[i];
            while(f != 0 && fsa[f].count(c) == 0){
                f = link[f];
            }
            f = fsa[f][c];
            if(out.count(f) > 0){
                for(auto a :out[f]){
                    if(parts[a].length() > len){
                        len = parts[a].length();
                        end_id = i;
                        part = parts[a];
                    }
                }
            }
        }
        if(len > 0){
            std::string start = w.substr(0, end_id - len+1);
            std::string end = w.substr(end_id+1);
            
            return start + "[" + part + "]" + end;
        }else{
            return w;
        }
        
    }
};

int main()
{
    using namespace std;
    vector<string> parts =  {"aaaaa", 
         "Aaaa", 
          "E", 
           "z", 
            "Zzzzz"}; //{"he", "she", "hers", "his"};
    string text =  "Aaaaaaaaa"; //"ahishers";
    AhoCorasick fsa;
    for(int i =0; i < parts.size(); ++i){
        fsa.insert_word(parts[i], i);         
    }
    fsa.fix_failure_link();
 
    auto ret = fsa.search(text);
    for(int a:ret)
            cout << parts[a] <<endl;
 
    return 0;
}


