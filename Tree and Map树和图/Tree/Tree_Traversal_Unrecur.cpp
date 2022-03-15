#include<vector>
#include<stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (nullptr != root) {
            stack<TreeNode*> s;
            s.push(root);
            while (!s.empty()) {
                TreeNode* cur = s.top();
                s.pop();
                res.push_back(cur->val);
                if (cur->right != nullptr) {
                    s.push(cur->right);
                }
                if (cur->left != nullptr) {
                    s.push(cur->left);
                }
            }
        }
        return res;
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root != nullptr) {
            stack<TreeNode*> s1;
            stack<TreeNode*> s2;
            s1.push(root);
            while (!s1.empty()) {
                TreeNode* cur = s1.top();
                s2.push(cur);
                s1.pop();
                if (cur->left != nullptr) {
                    s1.push(cur->left);
                }
                if (cur->right != nullptr) {
                    s1.push(cur->right);
                }
            }
            while (!s2.empty()) {
                res.push_back(s2.top()->val);
                s2.pop();
            }
        }
        return res;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root != nullptr) {
            stack<TreeNode*> s1;
            TreeNode* cur = root;
            while (!s1.empty() || cur != nullptr) {
                if (cur) {
                    s1.push(cur);
                    cur = cur->left;
                }
                else {
                    cur = s1.top();
                    s1.pop();
                    res.push_back(cur->val);
                    cur = cur->right;
                }
            }
        }
        return res;
    }
};