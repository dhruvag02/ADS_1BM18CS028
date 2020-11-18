#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

enum Color {RED, BLACK};

struct Node
{
    int data;
    bool color;
    Node* leftChild; 
    Node* rightChild; 
    Node* parent;

    //Constructor
    Node(int data)
    {
        this->data=data;
        leftChild=rightChild=parent=NULL;
        this->color=RED;
    }
};

class RBTree
{
    private:
        Node* root;
    protected:
        void rotateLeft(Node *&, Node *&);
        void rotateRight(Node *&, Node *&);
        void fixViolation(Node *&, Node *&);
    public:
        RBTree()
        {root=NULL;}
        void insert(const int &n);
        void inOrder();
        void levelOrder();
};

// Function to do inorder traversal
void inOrderHelper(Node* root)
{
    if(root==NULL)
        return;
    
    inOrderHelper(root->leftChild);
    cout<<root->data<<" ";
    inOrderHelper(root->rightChild);
}


Node* BSTInsert(Node* root, Node* pt)
{
    if(root==NULL)
        return pt;
    
    if(pt->data < root->data)
    {
        root->leftChild = BSTInsert(root->leftChild, pt);
        root->leftChild->parent=root;
    }

    else if (pt->data > root->data)
    {
        root->rightChild = BSTInsert(root->rightChild, pt);
        root->leftChild->parent=root;
    }

    return root;
}

void levelOrderHelper(Node* root)
{
    if(root==NULL)
        return;
    std::queue<Node *> q;
    q.push(root);

    while(!q.empty())
    {
        Node* temp = q.front();
        cout<<temp->data<<" ";
        q.pop();

        if(temp->leftChild != NULL)
            q.push(temp->leftChild);
        if(temp->rightChild != NULL)
            q.push(temp->rightChild);
    }
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
    Node* pt_right = pt->rightChild;
    pt->rightChild = pt_right->leftChild;

    if(pt->rightChild != NULL)
        pt->rightChild->parent=pt;

    pt_right->parent=pt->parent;

    if(pt->parent==NULL)
        root=pt_right;
    
    else if(pt == pt->parent->leftChild)
    {
        pt->parent->leftChild = pt_right;
    }

    else
    {
        pt->parent->rightChild=pt_right;
    }

    pt_right->leftChild=pt;
    pt->parent=pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
    Node* pt_left = pt->leftChild;
    pt->leftChild = pt_left->rightChild;

    if(pt->leftChild != NULL)
        pt->leftChild->parent=pt;

    pt_left->parent=pt->parent;

    if(pt->parent==NULL)
        root=pt_left;
    
    else if(pt == pt->parent->leftChild)
    {
        pt->parent->leftChild = pt_left;
    }

    else
    {
        pt->parent->rightChild=pt_left;
    }

    pt_left->rightChild=pt;
    pt->parent=pt_left;
}

void RBTree::fixViolation(Node *&root, Node *&pt)
{
    Node* parent_pt=NULL;
    Node* grand_parent_pt=NULL;

    while((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
    {
        parent_pt=pt->parent;
        grand_parent_pt=pt->parent->parent;

        // Case A, Parent of pt is left child of grand parent of pt
        if(parent_pt==grand_parent_pt->leftChild)
        {
            Node* unlce_pt=grand_parent_pt->rightChild;

            //Case 1, Uncle of pt is also red
            if(unlce_pt != NULL && unlce_pt->color == RED)
            {
                grand_parent_pt->color=RED;
                parent_pt->color=BLACK;
                unlce_pt->color=BLACK;
                pt=grand_parent_pt;
            }

            else
            {
                //Case 2, pt is right child of prent, left rotation is required
                if(pt==parent_pt->rightChild)
                {
                    rotateLeft(root, parent_pt);
                    pt=parent_pt;
                    parent_pt=pt->parent;
                }                
                
                //Case 3, pt is left child of prent, right rotation is required
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt=parent_pt;
            }
        }

        //Case B, Parent of pt is right child of grand parent of pt
        else
        {
            Node* unlce_pt = grand_parent_pt->leftChild;
            
            //Case 1, Uncle of pt is also red
            if(unlce_pt != NULL && unlce_pt->color == RED)
            {
                grand_parent_pt->color=RED;
                parent_pt->color=BLACK;
                unlce_pt->color=BLACK;
                pt=grand_parent_pt;
            }

            else
            {
                //Case 2, pt is left child of prent, right rotation is required
                if(pt==parent_pt->leftChild)
                {
                    rotateRight(root, parent_pt);
                    pt=parent_pt;
                    parent_pt=pt->parent;
                }                
                
                //Case 3, pt is right child of prent, left rotation is required
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt=parent_pt;
            }
        }
    } 
    root->color=BLACK;
}

void RBTree::insert(const int &data)
{
    Node* pt=new Node(data);
    
    //DO a normal BST insert
    root=BSTInsert(root,pt);

    fixViolation(root, pt);
}

void RBTree::inOrder()
{
    inOrderHelper(root);
}

void RBTree::levelOrder()
{
    levelOrderHelper(root);
}


int main()
{
    RBTree tree;
    int n;
    int val;

    cout<<"Enter number of elements to be inserted"<<endl;
    cin>>n;
    
    cout<<"Enter elements to be inserted"<<endl;
    for(int i=0; i<n; i++)
    {
        cin>>val;
        tree.insert(val);
    }

    cout<<"Inorder Traversal of created tree"<<endl;
    tree.inOrder();

    cout<<"\nLevel Order Traversal of created tree"<<endl;
    tree.levelOrder();

    return 0;
}

