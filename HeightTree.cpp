//Time complexity O(n*n)
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

int height(Node* root){
    if(root==nullptr) return 0;
    int hLeft = height(root->left);
    int hRight = height(root->right);
    
    return max(hLeft,hRight)+1;
}

int main()
{
    int nodes[]={1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    BinaryTree tree =  BinaryTree();
    Node* root = tree.buildTree(nodes);
    cout<<height(root);

    return 0;
}