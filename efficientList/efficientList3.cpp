#include<iostream>
#include<algorithm>
#include<inttypes.h>
using namespace std; 

class Node{
    
    public:
    int data;
    Node* npx;
};

Node* XOR(Node* a, Node* b){
    return (Node*) ((uintptr_t)(a) ^ (uintptr_t)(b));
}

Node* getnode(){
    Node* p=new Node();
    return p;
}

Node* insert_front(int data, Node **head){
    Node* p=getnode();
    Node* next;
    p->data=data;
    p->npx=XOR(NULL, *head);
    if(*head!=NULL){
        next=XOR(NULL, (*head)->npx);
        (*head)->npx=XOR(p,next);
    }
    *head=p;
    return *head;
}

Node* insert_end(int data, Node **head){
    Node* p=getnode();
    p->data=data;
    if(*head==NULL){
        p->npx=XOR(*head, NULL);
        *head=p;
    }
    Node* curr=*head;
    Node* prev=NULL;
    Node* next;
    while(curr!=NULL){
        next=XOR(prev,curr->npx);
        prev=curr;
        curr=next;
    } 
    p->npx=XOR(prev,NULL);
    Node* prevx=XOR(prev->npx,NULL);
    prev->npx=XOR(prevx,p);
    return *head;
}

Node* del_front(Node **head){
    Node* next;
    Node* nextn;
    Node* p;
    next=XOR((*head)->npx, NULL);
    nextn=XOR(next->npx, *head);
    (*head)->npx=NULL;
    p=*head;
    next->npx=XOR(NULL, nextn);
    *head=next;
    free(p);
    return *head;
}

Node* del_end(Node **head){
    if(*head==NULL){
        cout<<"List is empty"<<endl;
        return *head;
    }
    if((*head)->npx==NULL)
    {
        free(*head);
        return NULL;
    }
    Node* curr=*head;
    Node* prev=NULL;
    Node* next;
    while(curr!=NULL){
        next=XOR(prev, curr->npx);
        prev=curr;
        curr=next;
    }
    Node* prevx=XOR(prev->npx,NULL);
    Node* prevxx=XOR(prevx->npx,prev);
    prevx->npx=XOR(prevx,NULL);
    prev->npx=NULL;
    free(prev);
    return *head;
}

void display(Node **head){
    if (*head==NULL)
    {
        cout<<"List is empty"<<endl;
    }
    Node* p=*head;
    Node* prev=NULL; 
    Node* next;
    while (p!=NULL)
    {
        cout<<p->data<<endl;
        next=XOR(prev,p->npx);
        prev=p;
        p=next;
    }
}

int main(){
    Node* head=NULL;
    int n,val;
    cout<<"Enter number of values to be inserted"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter value to be inserted"<<endl;
        cin>>val;
        head=insert_end(val,&head);
    }
    cout<<"Values are displayed"<<endl;
    display(&head);
    head=del_front(&head);
    cout<<"Values after deletion at front are displayed"<<endl;
    display(&head);
    head=del_end(&head);
    cout<<"Values after deletion at end are displayed"<<endl;
    display(&head);
    return 0;
}


Enter number of values to be inserted
5
Enter value to be inserted
1
Enter value to be inserted
2
Enter value to be inserted
3
Enter value to be inserted
4
Enter value to be inserted
5
Values are displayed
1
2
3
Values after deletion at front are displayed
2
3
4
5
Values after deletion at end are displayed
2
3
4


Enter number of values to be inserted
10
Enter value to be inserted
1
Enter value to be inserted
2
Enter value to be inserted
3
Enter value to be inserted
4
Enter value to be inserted
5
Enter value to be inserted
6
Enter value to be inserted
7
Enter value to be inserted
8
Enter value to be inserted
9
Enter value to be inserted
10
Values are displayed
1
2
3
4
5
6
7
8
9
10
Values after deletion at front are displayed
2
3
4
5
6
7
8
9
10
Values after deletion at end are displayed
2
3
4
5
6
7
8
9
