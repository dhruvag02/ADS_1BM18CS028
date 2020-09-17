#include<iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
};

typedef struct node *NODE;

NODE getnode(){
    NODE p;
    p=(NODE) malloc(sizeof(struct node));
    if(p!=NULL)
        return p;
    else
    {
        cout<<"Memory could not be allocated"<<endl;
        return NULL;
    }
}

NODE insert_frot(int data,NODE head){
    NODE p=getnode();
    p->data=data;
    p->next=head;
    head=p;
    return head;
}

void display(NODE head){
    NODE p=head;
    if(head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    while(p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
}

NODE reverseKList(NODE head, int k){
    NODE curr=head, prev=NULL,nextn=NULL;
    int count=0;
    while(curr!=NULL && count<k){
        nextn=curr->next;
        curr->next=prev;
        prev=curr;
        curr=nextn;
        count++;
    }
    if(nextn!=NULL)
        head->next=reverseKList(nextn,k);

    return prev;
}

int main(){
    int n,k,e;
    cout<<"Enter Values of n and k"<<endl;
    cin>>n;
    cin>>k;
    NODE head=NULL;
    for(int i=0;i<n;i++){
        cout<<"Enter data to be inserted"<<endl;
        cin>>e;
        head=insert_frot(e,head);
    }
    cout<<"Before"<<endl;
    display(head);
    head=reverseKList(head,k);
    cout<<"After"<<endl;
    display(head);
    return 0;
}