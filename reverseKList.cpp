// Reverse every K nodes of a linked list

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


TEST 1

Enter data to be inserted
1 2 3 4 5
Enter data to be inserted
Enter data to be inserted
Enter data to be inserted
Enter data to be inserted
Before
5 4 3 2 1 After
4 5 2 3 1

Enter data to be inserted
5
Enter data to be inserted
4
Enter data to be inserted
3
Enter data to be inserted
2
Enter data to be inserted
1
Before
1 2 3 4 5 After
2 1 4 3 5

    
TEST 2

Enter Values of n and k
9
3
Enter data to be inserted
9
Enter data to be inserted
8
Enter data to be inserted
7
Enter data to be inserted
6
Enter data to be inserted
5
Enter data to be inserted
4
Enter data to be inserted
3
Enter data to be inserted
2
Enter data to be inserted
1
Before
1 2 3 4 5 6 7 8 9 After
3 2 1 6 5 4 9 8 7 
