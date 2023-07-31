#include <iostream>

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

void levelOrder(Node* root){
    std::queue<Node*> q;
    q.push(root);
    q.push(nullptr);
    
    while(!q.empty()){
        Node* n = q.front();
        q.pop();
        
        if(n==nullptr){
            if (!q.empty()) q.push(nullptr);
            cout<<endl;
        }else{
            cout<<n->val<<" ";
            if(n->left!=nullptr){
            q.push(n->left);
            
        }
        if(n->right!=nullptr){
            q.push(n->right);
        }
        } 
        
    }
}

int main()
{
    int nodes[]={1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    BinaryTree tree =  BinaryTree();
    Node* root = tree.buildTree(nodes);
    //cout<<root->val;
    levelOrder(root);

    return 0;
}