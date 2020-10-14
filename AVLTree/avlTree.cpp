#include<iostream>
#include<algorithm>

using namespace std;

class Node{
    public:
        int data;
        Node *leftChild;
        Node *rightChild;
        int height;
};

int max(int a, int b){
    return (a>b) ? a:b;
}

int height(Node *N){
    if(N==NULL)
        return 0;
    return N->height;
}


Node *newNode(int data){
    Node *node=new Node();
    node->data=data;
    node->leftChild=NULL;
    node->rightChild=NULL;
    node->height=1;
    return (node);
}

// Right Rotate the subtree
Node *rightRotate(Node *y){
    Node *x=y->leftChild;
    Node *T2=x->rightChild;

    // Perform Rotation
    x->rightChild=y;
    y->leftChild=T2;

    // Update Heights
    y->height=max(height(y->leftChild), height(y->rightChild)) + 1;
    x->height=max(height(x->leftChild), height(x->rightChild)) + 1;

    // Return new root
    return x;
}

// Left Rotate the subtree
Node *leftRotate(Node *x){

    Node *y=x->rightChild;
    Node *T2=x->leftChild;

    // Perform Rotation
    y->leftChild=x;
    x->rightChild=T2;

    // Update Heights
    x->height=max(height(x->leftChild), height(x->rightChild)) + 1;
    y->height=max(height(y->leftChild), height(y->rightChild)) + 1;

    return y;
}


// Get Balance Factor of node
int getBalance(Node *N){
    if(N==NULL)\
        return 0;
    return (height(N->leftChild) - height(N->rightChild)) ;
}

Node* insert(Node* node, int data){
    if(node == NULL)
        return (newNode(data));
    
    if(data<node->data)
        node->leftChild=insert(node->leftChild, data);
    else if(data>node->data)
        node->rightChild=insert(node->rightChild, data);
    else
        return node; // Equal keys don't exist in BST

    // Update height
    node->height=1 + max(height(node->leftChild), height(node->rightChild));

    // Get Balance Factor
    int balance = getBalance(node);


    // if this node is imbalanced, 4 possibilities arise

    if(balance>1 && data<node->leftChild->data)
        return rightRotate(node);

    if(balance<-1 && data>node->rightChild->data)
        return leftRotate(node);

    if(balance>1 && data>node->leftChild->data)
    {
        node->leftChild=leftRotate(node->leftChild);
        return rightRotate(node);
    }

    if(balance<-1 && data<node->rightChild->data)
    {
        node->rightChild=rightRotate(node->rightChild);
        return leftRotate(node);
    }

    // return unchnged node if "No rotation"
    return node;
}

Node* minValueNode(Node *node){
    Node* curr=node;

    //Loop down to find leftmost leaf
    while(curr->leftChild!=NULL)
        curr=curr->leftChild;
    return curr;
}

Node* del(Node* root, int data){
    if(root==NULL)
        return root;

    if(data<root->data)
        root->leftChild=del(root->leftChild, data);

    else if(data>root->data)
        root->rightChild=del(root->rightChild, data);
    
    // Given Node is found
    else{

        if( (root->leftChild==NULL) || (root->rightChild==NULL) )
        {
            Node* temp=root->leftChild?root->leftChild : root->rightChild;

            // No child
            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }
            else// One Child
            {
                *root=*temp;
            }
            free(temp);
        }
        else
        {
            Node* temp=minValueNode(root->rightChild);
            root->data=temp->data;
            root->rightChild=del(root->rightChild, temp->data);
        }
    }

    if(root==NULL)
        return root;
    
    // Update Height
    root->height=1 + max(height(root->leftChild), height(root->rightChild));

    int balance = getBalance(root);
    // Check for imbalance in the tree

    if(balance>1 && getBalance(root->leftChild)>=0)
        return rightRotate(root);

    if(balance>1 && getBalance(root->leftChild)<0)
    {
        root->leftChild=leftRotate(root->leftChild);
        return rightRotate(root);
    }

    if(balance<-1 && getBalance(root->rightChild)<=0)
        return leftRotate(root);
    
    if(balance<-1 && getBalance(root->rightChild)>0)
    {
        root->rightChild=rightRotate(root->rightChild);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node* root){
    if(root!=NULL){
        cout<<root->data<<" ";
        preOrder(root->leftChild);
        preOrder(root->rightChild);
    }
}


int main()
{
    Node* root=NULL;

    int n,val,e;
    cout<<"Enter number of nodes"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter value to be inserted"<<endl;
        cin>>val;
        root=insert(root,val);
    }

    cout<<"Preorder Traversal"<<endl;
    preOrder(root);
    cout<<"\n";

    cout<<"Enter node to be deleted"<<endl;
    cin>>e;
    root=del(root,e);

    cout<<"Preorder Traversal after deletion"<<endl;
    preOrder(root);

    return 0;
}


