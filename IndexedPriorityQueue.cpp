// Indexed Priority Queue for Integer key and value

#include<bits/stdc++.h>
using namespace std;

class IndexedPriorityQueue       
{
    vector<int> value;      // Values of each element
    vector<int> pm;         // Stores the position where the node in Heap
    vector<int> im;         // At a position in Heap which key exists (The i th value represents at i th position this key exists)
    int capacity;
    int size;
public:
    IndexedPriorityQueue(int capacity)     // Initialize with capacity
    {
        this->capacity=capacity;
        size=0;
        value.resize(capacity,INT_MAX);
        pm.resize(capacity,-1);
        im.resize(capacity,-1);
    }
    void swim(int i);
    void sink(int i);
    bool less(int i,int j);
    void Swap(int i,int j);
    void insert(int key,int val);
    void remove(int key);
    int poll();
    int peekKey();
    int peekValue();
    void updateValue(int key,int newVal);
    void increaseVal(int key,int newVal);
    void decreaseVal(int key,int newVal);
};

bool IndexedPriorityQueue::less(int i,int j)   // To check if i th element in heap is less than j th element in heap 
{
    return value[im[i]]<value[im[j]];
}

void IndexedPriorityQueue::Swap(int i,int j)  // Specialized swapping function
{
    pm[im[i]]=j;       // Swap the positions of i th and j th key get from inverse mapping
    pm[im[j]]=i;
    swap(im[i],im[j]);   // Swap the key positions in inverse mapping
}

void IndexedPriorityQueue::swim(int i)     // Heapifies a tree from bottom-up
{
    int p=(i-1)/2;
    while(i>0 && less(i,p))           // If i th element(under p) is small then need to heapify it
    {                                 // and do same until reach the root of the heap
        Swap(i,p);
        i=p;
        p=(i-1)/2;
    }
}

void IndexedPriorityQueue::sink(int i)   // Dives into the heap from a given node
{
    int smallest=i;
    int left=2*i+1,right=2*i+2;
    if(left<size && less(left,smallest))
    {
        smallest=left;
    }
    if(right<size && less(right,smallest))
    {
        smallest=right;
    }
    if(smallest!=i)
    {
        Swap(i,smallest);
        sink(smallest);
    }
}

void IndexedPriorityQueue::insert(int key,int val)  // Inserts a val for specified key maintaining heap property
{
    if(pm[key]!=-1)
    {
        cout<<"Already Exists Data Here\n";
        return;
    }
    value[key]=val;
    pm[key]=size;
    im[size]=key;
    swim(size);
    size+=1;
}

void IndexedPriorityQueue::remove(int key)    // Removes a given key
{
    int k=pm[key];
    if(k==-1)
    {
        cout<<"No data here to delete\n";
        return;
    }
    Swap(k,size-1);
    size-=1;
    swim(k);
    sink(k);
    pm[key]=-1;
    value[key]=INT_MAX;
    im[size]=-1;
    cout<<key<<" deleted\n";
}

int IndexedPriorityQueue::poll()      // Returns first element in heap and deletes it
{
    if(size==0)
    {
        cout<<"No data in the IPQ\n";
        return INT_MAX;
    }
    int d=im[0];
    Swap(0,size-1);
    pm[d]=-1;
    size-=1;
    sink(0);
    return d;
}

int IndexedPriorityQueue::peekKey()    // Returns the first elemnts key in heap
{
    if(size==0)
    {
        cout<<"IPQ is empty\n";
        return INT_MAX;
    }
    return im[0];
}

int IndexedPriorityQueue::peekValue()   // Value of the first key in heap
{
    if(size==0)
    {
        cout<<"IPQ is empty\n";
        return INT_MAX;
    }
    return value[im[0]];
}

void IndexedPriorityQueue::updateValue(int key,int newVal)  // Updates the value of an element 
{
    int k=value[key];
    value[key]=newVal;
    swim(pm[key]);
    sink(pm[key]);
    cout<<"Value updated\n";
}

void IndexedPriorityQueue::increaseVal(int key,int newVal) // Increases the value of a given key to given value
{
    int k=value[key];
    if(newVal>k)
    {
        value[key]=newVal;
    }
    sink(pm[key]);
    cout<<"Value Increased\n";
}

void IndexedPriorityQueue::decreaseVal(int key,int newVal)  // Same as increase function but needs to decrease value
{
    int k=value[key];
    if(newVal<k)
    {
        value[key]=newVal;
    }
    swim(pm[key]);
    cout<<"Value decreased\n";
}

int main()
{
    IndexedPriorityQueue ipq(10);
    ipq.insert(1,10);
    ipq.insert(4,8);
    ipq.insert(3,12);
    ipq.insert(2,16);
    ipq.insert(5,20);
    ipq.insert(6,4);
    ipq.insert(7,9);
    cout<<"Key with lowest value : ";
    cout<<ipq.peekKey()<<"\n";
    cout<<"Key with lowest value : ";
    cout<<ipq.poll()<<"\n";
    cout<<"Key with lowest value : ";
    cout<<ipq.peekKey()<<"\n";
    ipq.remove(7);
    ipq.updateValue(4,12);
    cout<<"Key with lowest value : ";
    cout<<ipq.peekKey()<<"\n";
    ipq.decreaseVal(4,8);
    cout<<"Key with lowest value : ";
    cout<<ipq.peekKey()<<"\n";
    return 0;
} 

// Output : Key with lowest value : 6
//          Key with lowest value : 6
//          Key with lowest value : 4
//          7 deleted
//          Value updated
//          Key with lowest value : 1
//          Value decreased
//          Key with lowest value : 4