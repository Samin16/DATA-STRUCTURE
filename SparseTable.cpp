// Sparse Table : For range query(Here minQuery)
// Prerequisite : It works for Associative functions like max,min,multiplication
// Associative means if f(x,y) is a function then f(a,f(b,c))=f(f(a,b),c)
// For the associative functions that are overlap friendly it works in O(1)
// Overlap friendly means overlap of two sub range or repetition of one element
// in the range doesn't create effect. min,max are overlap friendly.


#include<bits/stdc++.h>
using namespace std;

class SparseTable {
    int N;            // Number of columns in Sparse Table
    int P;            // Number of rows in Sparse Table
    vector<int> Log2; // Stores all log2(i) , i=1,2,.....,N
    vector<vector<int>> table;     // Sparse Table
    vector<vector<int>> it;        // Stores minimum elements index
public:
    SparseTable(int n)
    {
        N=n;         
        P=ceil(log2(n));
        Log2.resize(n+1,0);
        table=vector<vector<int>>(P+1,vector<int>(n));
        it=vector<vector<int>>(P+1,vector<int>(n));
    }
    void createLog2()           // Dynamically computes all log2(i) values i=0,1,..,N
    {
        for(int i=2;i<=N;i++)
        {
            Log2[i]=1+Log2[i/2];
        }
    }
    void buildTable(vector<int> & arr)    // Builds Sparse Table dynamically
    {
        for(int i=0;i<N;i++)
        {
            table[0][i]=arr[i];
            it[0][i]=i;
        }
        for(int p=1;p<=P;p++)
        {
            for(int i=0;i+(1<<p)<=N;i++)
            {
                int left=table[p-1][i];
                int right=table[p-1][i+(1<<(p-1))];
                table[p][i]=min(left,right);
                if(left<right)
                {
                    it[p][i]=it[p-1][i];
                }
                else
                {
                    it[p][i]=it[p-1][i+(1<<(p-1))];
                }
            }
        }
    }
    int minQuery(int l,int r)        // For overlap friendly function
    {
        int len=r-l+1;
        int p=Log2[len];
        int left=table[p][l];
        int right=table[p][r-(1<<p)+1];
        return min(left,right);
    }
    int cascadingMinQuery(int l,int r)        // For non overlap friendly function
    {
        int min_Val=INT_MAX;
        for(int p=Log2[r-l+1];l<=r;p=Log2[r-l+1])
        {
            min_Val=min(min_Val,table[p][l]);
            l+=(1<<p);
        }
        return min_Val;
    }
    int minIndexQuery(int l,int r)        // Minimum elements index in the range
    {
        int len=r-l+1;
        int p=Log2[len];
        int left=table[p][l];
        int right=table[p][r-(1<<p)+1];
        if(left<=right)
        {
            return it[p][l];
        }
        else
        {
            return it[p][r-(1<<p)+1];
        }
    }
};

int main()
{
    int n;
    cout<<"Enter number of elements : ";
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter array elements : ";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    SparseTable st(n);
    st.createLog2();
    st.buildTable(arr);
    cout<<"Enter total query number : ";
    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cout<<"Enter range : ";
        cin>>l>>r;
        cout<<"Minimum number in range "<<l<<" to "<<r<<" : "<<st.minQuery(l,r)<<endl;
    }
    return 0;
}




//   Output :   Enter number of elements : 10
//              Enter array elements : 7 6 -1 9 5 3 8 4 11 10
//              Enter total query number : 4
//              Enter range : 0 9
//              Minimum number in range 0 to 9 : -1
//              Enter range : 0 1
//              Minimum number in range 0 to 1 : 6
//              Enter range : 3 7
//              Minimum number in range 3 to 7 : 3
//              Enter range : 9 8
//              Minimum number in range 9 to 8 : 10