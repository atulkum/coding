#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
#include <iterator>
#include <queue>

using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) 
      : val(x), left(nullptr), right(nullptr) {}
 
};
TreeNode* deserialize(string data) {
        vector<string> tokens;
        stringstream ss(data);
        copy(istream_iterator<string>(ss),
        istream_iterator<string>(),
        back_inserter(tokens));
     
        queue<TreeNode*> q;
        TreeNode* root = new TreeNode(stoi(tokens[0]));
        q.push(root);
        int i = 1;
        while(!q.empty() && i < tokens.size()){
            TreeNode* next = q.front(); q.pop();
            if(tokens[i] != "#"){
                next->left = new TreeNode(stoi(tokens[i]));
                q.push(next->left);
            }
            i++;
            if(i < tokens.size()){
                if( tokens[i] != "#"){
                    next->right = new TreeNode(stoi(tokens[i]));
                    q.push(next->right);
                }
                i++;
            }
        }
        return root;
}
vector<long> dp(TreeNode* root){
    vector<long> ret(2, 0);
    if(root  == nullptr){
        return ret;
    }
    vector<long> left = dp(root->left);
    vector<long> right = dp(root->right);
    ret[0] = max(left[0], left[1]) + max(right[0], right[1]);
    ret[1] = root->val + left[0] + right[0];
    return ret;
}

int main() {
    int M;
    cin >> M;
   
    string treeRepr;
    getline(cin, treeRepr);
    getline(cin, treeRepr);
    
    TreeNode* root = deserialize(treeRepr);
    vector<long> ret = dp(root);
    
    cout << max(ret[0], ret[1]) <<endl;
    return 0;
}
