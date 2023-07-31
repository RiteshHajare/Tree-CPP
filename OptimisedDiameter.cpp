//Time complexity O(n)

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



class TreeInfo{
    public:
    int ht;
    int diam;
    
    TreeInfo(int h,int d){
        ht=h;
        diam=d;
    }
};

TreeInfo optimisedDiameter(Node* root){
    if(root==nullptr) return TreeInfo(0,0);
    
    TreeInfo left = optimisedDiameter(root->left);
    TreeInfo right= optimisedDiameter(root->right);
    
    int myHeight = max(left.ht,right.ht)+1;
    
    int leftDiam = left.diam;
    int rightDiam = right.diam;
    int rootDiam = left.ht+right.ht+1;
    
    int myDiam = max(max(leftDiam,rightDiam),rootDiam);
    
    return TreeInfo(myHeight,myDiam);

}

int main()
{
    int nodes[]={1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    BinaryTree tree =  BinaryTree();
    Node* root = tree.buildTree(nodes);
    cout<<optimisedDiameter(root).diam;

    return 0;
}