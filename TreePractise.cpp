#include <climits>
#include <iostream>
#include<queue>
#include <utility> 
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    
    Node(int v){
       data=v;
       left=nullptr;
       right=nullptr;
    }
};

Node* buildTree(Node* root,int val){
    if(root==nullptr){
        return new Node(val);
    }
    if(val<root->data){
        root->left = buildTree(root->left,val);
    }
    if(val>root->data){
        root->right = buildTree(root->right,val);
    }
    return root;
}

void preOrder(Node* root){
    if(root==nullptr)return;
    cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

Node* findSuccessor(Node* root){
    while(root->left!=nullptr){
        root=root->left;
    }    
    return root;
}

//O(h)
Node* deleteNode(Node* root,int val){
    if(root==nullptr)return nullptr;
    if(val < root->data){
        root->left = deleteNode(root->left,val);
    }
    else if(val>root->data){
        root->right = deleteNode(root->right,val);
    }else{
        if(root->left==nullptr && root->right==nullptr) return nullptr;
        if(root->left==nullptr)return root->right;
        if(root->right==nullptr) return root->left;
        Node* successor = findSuccessor(root->right);
        root->data=successor->data;
        root->right = deleteNode(root->right,successor->data);
    }
    
    return root;
}


class Pair{
    public:
    Node* node;
    Node* par;
    bool dir;
    
    Pair(Node* n,Node* p,bool d){
        node = n;
        par = p;
        dir = d;
    }
};
//partially working BFS maybe O(n)
void deleteNodeBFS(Node* root,int val){
    queue<Pair> q;
    q.push(Pair(root,nullptr,0));
    
    while(!q.empty()){
        Pair front = q.front();
        q.pop();
        
        if(root->data==val){
            
            Node* succ = findSuccessor(root->right);
            root->data = succ->data;
            if(root->right->left==nullptr && root->right->right==nullptr){
                root->right=nullptr;
                return;
            }
            
            deleteNodeBFS(root->right,succ->data);
            
        }
        
        
        if(front.node!=nullptr){
            if(front.node->data==val){
                if(front.node->left==nullptr && front.node->right==nullptr){
                    if(front.dir){
                        front.par->right = nullptr;
                    }else{
                        front.par->left = nullptr;
                    }
                }else if(front.node->left!=nullptr && front.node->right!=nullptr){
                    Node* successor = findSuccessor(front.node->right);
                    if(front.dir){
                        front.par->right->data = successor->data;
                    }else front.par->left->data = successor->data;
                    if(front.node->right->left==nullptr && front.node->right->right==nullptr) front.node->right=nullptr;
                    else deleteNodeBFS(front.node->right,successor->data);
                }else if(front.node->left==nullptr){
                    if(front.dir){
                        front.par->right = front.node->right;
                    }else front.par->left = front.node->right;
                }else if(front.node->right==nullptr){
                    if(front.dir){
                        front.par->right = front.node->left;
                    }else front.par->left = front.node->left;
                }
                
            }
            if(front.node->left!=nullptr){
                q.push(Pair(front.node->left,front.node,0));
            }
            if(front.node->right!=nullptr){
                q.push(Pair(front.node->right,front.node,1));
            }
        }
    }
}

int height(Node* root){
    // if(root== nullptr) return 0;
    
    // return 1+max(height(root->left),height(root->right));
    
    //OR
    
    if(!root) return 0;
    if(root->left==nullptr && root->right==nullptr)return 1;
    else if(root->left==nullptr) return height(root->right)+1;
    else if(root->right==nullptr) return height(root->left)+1;
    return max(height(root->left),height(root->right))+1;
}

int depth(Node* root,int val){
    if(root==nullptr)return -1;
    if(val == root->data) return 1;
    else if(val<root->data && depth(root->left,val)!=-1) return depth(root->left,val)+1;
    else if(val>root->data && depth(root->right,val)!=-1) return depth(root->right,val)+1;
    return -1;
}

int maxBreadth(Node* root){
    if(root == nullptr)return 0;
    queue<Node*> q;
    q.push(root);
    q.push(nullptr);
    int ans=1;
    int temp=0;
    while(!q.empty()){
        Node* curr = q.front();
        q.pop();
        
        if(curr == nullptr){
            ans=max(ans,temp);
            temp=0;
            if (!q.empty()) {
                q.push(nullptr); // Add a marker for the next level
            }
        }
        else{
            if(curr->left!=nullptr){
                temp++;
                q.push(curr->left);
            }
            if(curr->right!=nullptr){
                q.push(curr->right);
                temp++;
            }
        }
    }
    return ans;
}

//O(n^2)
int diam(Node* root){
    if(!root) return 0;
    
    int left = diam(root->left);
    int right = diam(root->right);
    
    int middle = height(root->left)+height(root->right);
    
    return max(max(left,right),middle)+1;
}

class Pair2{
    public:
    int ht;
    int diam;
    
    Pair2(int h,int d){
        ht=h;
        diam=d;
    }
};

// optimised with O(n)
Pair2 optmisedDiam(Node* root){
    if(!root){
        return Pair2(0,0);
    }
    Pair2 left = optmisedDiam(root->left);
    Pair2 right = optmisedDiam(root->right);
    
    int middle = left.ht+right.ht+1;
    
    int newHt = max(left.ht,right.ht)+1;
    int newDept = max(max(left.diam,right.diam),middle);
    
    return Pair2(newHt,newDept); 
}

class Pair3{
  public:
  int ct;
  int sum;
  
  Pair3(int c,int s){
      ct=c;
      sum=s;
  }
};

//O(n)
Pair3 sumOfNodesDFS(Node* root){
    if(!root) return Pair3(0,0);
    
    Pair3 left = sumOfNodesDFS(root->left);
    Pair3 right = sumOfNodesDFS(root->right);
    
    return Pair3(left.ct+right.ct+1,left.sum+right.sum+root->data);
}

//O(n)
int sumOfNodesBFS(Node* root){
    if(!root) return 0;
    
    queue<Node*> q;
    q.push(root);
    int ans=0;
    int count=1;
    while(!q.empty()){
        Node* curr = q.front();
        q.pop();
        
        ans+=curr->data;
        
        if(curr->left){
            q.push(curr->left);
            count++;
        }
        if(curr->right){
            q.push(curr->right);
            count++;
        }
    }
    cout<<"Count of nodes-> "<<count<<endl;
    return ans;
}

int leafSumDFS(Node* root){
    if(!root) return 0;
    
    if(!root->left && !root->right){
        return root->data;
    }
    
    return leafSumDFS(root->left)+leafSumDFS(root->right);
}

int leafSumBFS(Node* root){
  
    if(!root)return 0;
      int ans=0;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* curr = q.front();
        q.pop();
        if(!curr->left && !curr->right){
            ans+=curr->data;
        }
        if(curr->left){
            q.push(curr->left);
        }
        if(curr->right){
            q.push(curr->right);
        }
    }
    return ans;
}

int levelSum(Node* root,int level){
    if(!root)return 0;
    if(level>height(root)) return -1;
    if(level==1) {
        return root->data;
    }
    int left = levelSum(root->left,level-1);
    int right = levelSum(root->right,level-1);
    return left+right;
}

int levelSumBFS(Node* root,int level){
    if(!root)return -1;
    if(level>height(root)) return -1;
    queue<pair<Node*, int>> q;
    q.push(make_pair(root,level));
    int ans=0;
    while(!q.empty()){
        pair<Node*,int> curr = q.front();
        q.pop();
        if(curr.second<1)break;
        if(curr.second==1){
            ans+=curr.first->data;
        }
        if(curr.first->left!=nullptr){
            q.push(make_pair(curr.first->left,curr.second-1));
        }
        if(curr.first->right!=nullptr){
            q.push(make_pair(curr.first->right,curr.second-1));
        }
    }
    return ans;
}

void searchInRange(Node* root,int x,int y){
    if(!root) return;
    
    if(x>root->data){
        searchInRange(root->right,x,y);
    }else if(y<root->data){
        searchInRange(root->left,x,y);
    }else{
        cout<<root->data<<" ";
        if(root->left){
            searchInRange(root->left,x,y);
        }
        if(root->right){
            searchInRange(root->right,x,y);
        }
    }
}

int main()
{
    int nodes[]={5,3,4,2,1,9,10,11,7,8,6};
    Node* root=nullptr;
    for(auto it:nodes){
        root = buildTree(root,it);
    }
    preOrder(root);
    cout<<endl;
    // deleteNode(root,9);
    // deleteNodeBFS(root,2);
    // preOrder(root);
    // cout<<height(root);
    // cout<<depth(root,0);
    // cout<<maxBreadth(root);
    // cout<<diam(root);
    // cout<<optmisedDiam(root).diam;
//    Pair3 sumctDFS = sumOfNodesDFS(root);
//    cout<<sumctDFS.ct<<" "<<sumctDFS.sum;
    // cout<<sumOfNodesBFS(root);
    // cout<<leafSumDFS(root);
    // cout<<leafSumBFS(root);
    // cout<<levelSum(root,2);
    // cout<<levelSumBFS(root,2);
    // searchInRange(root,5,9);
    
    return 0;
}
