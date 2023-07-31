#include <iostream>
#include <queue>
std::queue<int> myQueue;
using namespace std;

class Node{
    public:
    int val;
    Node* left;
    Node* right;
    
    Node(int v){
        val=v;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree{
    public:
    int idx = -1;
    Node* buildTree(int nodes[]){
        idx++;
        if(nodes[idx]==-1) return nullptr;
        Node* newnode = new Node(nodes[idx]);
        newnode->left = buildTree(nodes);
        newnode->right = buildTree(nodes);
        return newnode;
    }
};

int countNodes(Node* root){
    // if(root->left==nullptr && root->right==nullptr) return 1;
    // if(root->left==nullptr && root->right!=nullptr) return 1+countNodes(root->right);
    // if(root->left!=nullptr && root->right==nullptr) return 1+countNodes(root->left);
    // return countNodes(root->right)+countNodes(root->left)+1;
    if(root==nullptr)return 0;
    int left = countNodes(root->left);
    int right = countNodes(root->right);
    return 1+left+right;
// replace 1 with root->val in above line to get sum of all nodes.
}

int main()
{
    int nodes[]={1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    BinaryTree tree =  BinaryTree();
    Node* root = tree.buildTree(nodes);
    cout<<countNodes(root);

    return 0;
}