#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Disjointset{
    vector<int> rank, parent;
    int n;
    public:
        Disjointset(int n){
            rank.resize(n);
            parent.resize(n);
            this->n=n;
            makeSet();
        }
    
    void makeSet(){
        for(int i=0;i<n;i++)
            parent[i]=i;
    }

    int find(int x){
        if(parent[x]!=x)
            return find(parent[x]);
        return parent[x];
    }

    void Union(int x,int y){
        int xRoot=find(x);
        int yRoot=find(y);

        if(xRoot==yRoot)
            return;
        
        if(rank[xRoot]<rank[yRoot])
            parent[xRoot]=yRoot;
        else if (rank[yRoot]<rank[xRoot])
            parent[yRoot]=xRoot;
        else{
            parent[yRoot]=xRoot;
            rank[xRoot]=rank[xRoot]+1;
        }
    }
};

int countIslands(vector<vector<int>>a,int size){
    // Square Matrix
    int n=size; // Rows
    int m=size; // Columns
    //cout<<"Values of n and m: "<<n<<m<<endl;

    Disjointset *dus = new Disjointset(n*m);

    for(int j=0;j<n;j++){
        for(int k=0;k<m;k++){

            if(a[j][k]==0)
                continue;
            
            if(j+1 < n && a[j+1][k]== 1){
                dus->Union(j* (m) + k,(j+1) * (m) + k);
            }

            if(j-1 >= 0 && a[j-1][k]== 1){
                dus->Union(j* (m) + k,(j-1) * (m) + k);
            }

            if(k+1 < m && a[j][k+1]==1){
                dus->Union(j* (m) + k,j * (m) + k+1);
            }

            if(k-1 >= 0 && a[j][k-1]==1){
                dus->Union(j* (m) + k,j * (m) + k-1);
            }

            if(j+1 < n && k+1 < m && a[j+1][k+1]==1){
                dus->Union(j* (m) + k,(j+1) * (m) + k+1);
            }

            if(j+1 < n && k-1 >= 0 && a[j+1][k-1]==1){
                dus->Union(j* m + k,(j+1) * (m) + k-1);
            }

            if(j-1 >= 0 && k+1 < m && a[j-1][k+1]==1){
                dus->Union(j* m + k,(j-1) * (m) + k+1);
            }

            if(j-1 >= 0 && k-1 >= 0 && a[j-1][k-1]==1){
                dus->Union(j* m + k,(j-1) * (m) + k-1);
            }
        }
    }
// End of for
int *c = new int[n * m]; 
    int numberOfIslands = 0; 
    for (int j = 0; j < n; j++) 
    { 
        for (int k = 0; k < m; k++) 
        { 
            if (a[j][k] == 1) 
            { 
                int x = dus->find(j * m + k); 
  
                // If frequency of set is 0, 
                // increment numberOfIslands 
                if (c[x] == 0) 
                { 
                    numberOfIslands++; 
                    c[x]++; 
                } 
  
                else
                    c[x]++; 
            } 
        } 
    } 
    return numberOfIslands; 

}

int main(){

    int n,val;
    cout<<"Enter dimansion of matrix"<<endl;
    cin>>n;
    vector<vector<int>>a(n, vector<int>(n));

    cout<<"Enter Values"<<endl;
    for(int i=0;i<n;i++){
        cout<<"Enter in row: "<<i<<endl;
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }

    cout<<"Entered Matrix is printed"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }

    cout<<"Number of Islands: "<<countIslands(a,n)<<endl;
    return 0;
}