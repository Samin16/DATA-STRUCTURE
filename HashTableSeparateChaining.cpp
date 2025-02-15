// HashTable using separate chaining
// Author : Samin Yasar


#include<bits/stdc++.h>
using namespace std;

template<typename S,typename T>
class Element                      // To store each pair (key and value) in the hashTable
{                                  // Each element has its own hash value
    int hash;
    S key;
    T value;
public:
    Element(S key,T value)
    {
        this->key=key;
        this->value=value;
        this->hash=std::hash<S>{}(key);     // To compute the hash for that key
    }
    void setValue(T value)          // Sets a value to this->value
    {
        this->value=value;
    }
    S getKey() const                        // Getter functions
    {
        return key;
    }
    T getValue() const
    {
        return value;
    }
    bool equals(const Element<S,T>& other) const
    {
        if(hash!=other.hash)
        {
            return false;
        }
        return key==other.key;
    }
};

template<typename S,typename T>      // Class having all functions related to HashTable
class HashTableSeparateChaining
{
    static const int DEFAULT_CAPACITY;
    static constexpr double DEFAULT_LOAD_FACTOR=0.75;
    double maxLoadFactor;
    int capacity,threshold,size=0;
    vector<list<Element<S,T>>> table;
    int normalizeIndex(int keyHash) const      // Normalizes the hash to remain inside table capacity
    {
        return (keyHash & 0x7FFFFFFF)%capacity;
    }
    void resizeTable()             // Resizes table if threshold value that it can contain reaches its limit
    {
        capacity*=2;
        threshold=static_cast<int>(capacity*maxLoadFactor);
        vector<list<Element<S,T>>> newTable(capacity);
        for(auto& bucket:table)
        {
            for(auto& element:bucket)
            {
                int bucketIndex=normalizeIndex(std::hash<S>{}(element.getKey()));
                newTable[bucketIndex].push_back(element);
            }
        }
        table=move(newTable);        // Simply hands the newTable to table
    }
public:
    // Constructors with different parameters
    HashTableSeparateChaining():HashTableSeparateChaining(DEFAULT_CAPACITY,DEFAULT_LOAD_FACTOR){}
    HashTableSeparateChaining(int capacity):HashTableSeparateChaining(capacity,DEFAULT_LOAD_FACTOR){}
    HashTableSeparateChaining(int capacity,double loadFactor)
    {
        if(capacity<0)             // Exception handling
        {
            throw invalid_argument("Invalid capacity");
        }
        if(loadFactor<=0 || isnan(loadFactor) || isinf(loadFactor))
        {
            throw invalid_argument("Invalid maxLoadFactor");
        }
        this->capacity=capacity;
        this->maxLoadFactor=loadFactor;
        this->threshold=static_cast<int>(this->capacity*this->maxLoadFactor);
        table.resize(capacity);
    }
    int getSize() const       // Returns size
    {
        return size;
    }
    bool isEmpty() const      // Returns true if the table has no element
    {
        return size==0;
    }
    void clear()              // Clears the table
    {
        table.clear();
        table.resize(capacity);
        size=0;
    }
    bool containsKey(const S& key) const     // Checks if the given key is in any bucket
    {
        int bucketIndex=normalizeIndex(std::hash<S>{}(key));
        auto& bucket=table[bucketIndex];
        for(auto& element:bucket)
        {
            if(element.getKey()==key)
            {
                return true;
            }
        }
        return false;
    } 
    T insert(const S& key,const T& value)        // Inserts an element, if already exists simply update its values
    {
        int bucketIndex=normalizeIndex(std::hash<S>{}(key));
        auto& bucket=table[bucketIndex];
        for(auto& element:bucket)
        {
            if(element.getKey()==key)
            {
                T oldValue=element.getValue();
                element.setValue(value);
                return oldValue;
            }
        }
        bucket.emplace_back(key,value);
        if(++size>threshold)            // If size exceeds threshold, then resize
        {
            resizeTable();
        }
        return T();
    }
    T get(const S& key) const        // Returns the value at the given key
    {
        int bucketIndex=normalizeIndex(std::hash<S>{}(key));
        for(const auto& element:table[bucketIndex])
        {
            if(element.getKey()==key)
            {
                return element.getValue();
            }
        }
        return T();
    }
    T remove(const S& key)           // If given key is in container deletes it
    {
        int bucketIndex=normalizeIndex(std::hash<S>{}(key));
        auto& bucket=table[bucketIndex];
        for(auto it=bucket.begin();it!=bucket.end();it++)
        {
            if(it->getKey()==key)
            {
                T oldValue=it->getValue();
                bucket.erase(it);
                size--;
                return oldValue;
            }
        }
        return T();
    }
    vector<S> keys() const              // Returns all keys of the hashTable
    {
        vector<S> keys;
        for(const auto& bucket:table)
        {
            for(const auto& element:bucket)
            {
                keys.push_back(element.getKey());
            }
        }
        return keys;
    }
    vector<T> values() const           // Returns all values of hashTable
    {
        vector<T> values;
        for(const auto& bucket:table)
        {
            for(const auto& element:bucket)
            {
                values.push_back(element.getValue());
            }
        }
        return values;
    }
    void display() const             // A display format for all elements
    {
        for(int i=0;i<capacity;i++)
        {
            cout<<"Bucket "<<i<<" : ";
            for(const auto& element:table[i])
            {
                cout<<"("<<element.getKey()<<", "<<element.getValue()<<")";
            }
            cout<<"\n";
        }
    }
};

template<typename S,typename T>                               // Initializing static variables
const int HashTableSeparateChaining<S,T>::DEFAULT_CAPACITY=4;

int main()
{
    HashTableSeparateChaining<string, int> hashTable;

    // Insert key-value pairs
    hashTable.insert("Alice", 25);
    hashTable.insert("Bob", 30);
    hashTable.insert("Charlie", 35);

    // Retrieve values
    cout << "Alice's age: " << hashTable.get("Alice") << endl; // Output: 25

    // Update value
    hashTable.insert("Alice", 26);
    cout << "Alice's updated age: " << hashTable.get("Alice") << endl; // Output: 26

    // Check if a key exists
    cout << "Contains key 'Bob': " << hashTable.containsKey("Bob") << endl; // Output: 1 (true)

    // Remove a key
    hashTable.remove("Bob");
    cout << "Contains key 'Bob' after removal: " << hashTable.containsKey("Bob") << endl; // Output: 0 (false)

    // Display all keys and values
    cout << "Keys: ";
    for (const auto &key : hashTable.keys())
    {
        cout << key << " ";
    }
    cout << endl;

    cout << "Values: ";
    for (const auto &value : hashTable.values())
    {
        cout << value << " ";
    }
    cout << endl;

    // Display the hash table
    hashTable.display();

    return 0;
}

// Output : Alice's age: 25
//          Alice's updated age: 26
//          Contains key 'Bob': 1
//          Contains key 'Bob' after removal: 0
//          Keys: Charlie Alice
//          Values: 35 26
//          Bucket 0 : (Charlie, 35)
//          Bucket 1 : (Alice, 26)
//          Bucket 2 :
//          Bucket 3 :