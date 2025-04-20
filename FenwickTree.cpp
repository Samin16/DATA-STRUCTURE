// Fenwick Tree implementation

#include<bits/stdc++.h>
using namespace std;

class FenwickTree
{
    int capacity;                // Capacity of the tree
    vector<int> tree;            // Fenwick tree for range sum
    int LSB(int x)               // Returns the decimal of the Least Significant Bit (Like for 1110 it returns 0010(2))
    {
        return x & -x;
    }
public:
    FenwickTree(int n)           // Fenwich Tree initialization
    {
        capacity=n;
        tree.resize(n+1,0);      // The fenwick Tree is 1 indexed
    }
    void build(vector<int>& data)       // Builds the fenwick tree with the given array
    {
        for(int i=0;i<capacity;i++)
        {
            pointUpdate(i+1,data[i]);
        }
    }
    void pointUpdate(int idx,int delta)  // Point update of tree index for all indices that that are dependent 
    {                                    // on the given index with the given value(HERE THE VALUE IS DIFFERENCE)
        while(idx<=capacity)
        {
            tree[idx]+=delta;
            idx+=LSB(idx);
        }
    }
    int prefixQuery(int idx)      // Function to compute prefix sum of [1,idx]
    {
        int result=0;
        while(idx>0)
        {
            result+=tree[idx];
            idx-=LSB(idx);
        }
        return result;
    }
    int rangeQuery(int l,int r)   // Function to compute sum of [l,r] (l and r are index in the given array)
    {
        return prefixQuery(r+1)-prefixQuery(l);   // sum[l:r]=sum[r+1:0]-sum[l:0]
    }
    void printTree()                              // Prints the tree for debugging 
    {
        cout<<"Fenwick Tree : ";
        for(int i=1;i<=capacity;i++)
        {
            cout<<tree[i]<<" ";
        }
        cout<<"\n";
    }
};

int main()
{
    vector<int> data={3,4,-2,7,3,11,5,-8,-9,2,4,-8};
    FenwickTree ft(data.size());
    ft.build(data);
    ft.printTree();
    cout<<"Range sum from index 2 to 5 : "<<ft.rangeQuery(1,4)<<"\n";
    cout<<"Range sum from index 0 to 12 : "<<ft.rangeQuery(0,11)<<"\n";
    ft.pointUpdate(5,-1);                              // Here means now data[5]=data[5]+(-1)
    cout<<"Range sum from index 2 to 5 : "<<ft.rangeQuery(0,4)<<"\n";
    return 0;
}

// Output : Fenwick Tree : 3 7 -2 12 3 14 5 23 -9 -7 4 -11 
//          Range sum from index 2 to 5 : 12
//          Range sum from index 0 to 12 : 12
//          Range sum from index 2 to 5 : 14