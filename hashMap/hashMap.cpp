#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

// General helper functions

bool isPrime(size_t n) // Prime number checker
{
    if (n <= 1)
    {
        return false;
    }
    if (n <= 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

int nextPrime(int n) // Finds next prime number of a number
{
    if (n <= 1)
    {
        return 2;
    }
    int nextPrime = n + 1;
    if (nextPrime % 2 == 0 && nextPrime != 2)
    {
        nextPrime++;
    }
    while (!isPrime(nextPrime))
    {
        nextPrime += 2;
    }
    return nextPrime;
}

string generateRandomString(int minLen = 5, int maxLen = 10) // String Generator
{
    static const string characters = "abcdefghijklmnopqrstuvwxyz";
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> lenDist(minLen, maxLen);
    uniform_int_distribution<> charDist(0, characters.size() - 1);
    int len = lenDist(generator);
    string randomString;
    randomString.reserve(len);
    for (int i = 0; i < len; i++)
    {
        randomString += characters[charDist(generator)];
    }
    return randomString;
}

vector<string> generateRandomWords(size_t len) // Creates a string array with len random strings
{
    vector<string> words;
    while (words.size() < len)
    {
        words.push_back(generateRandomString());
    }
    return words;
}

size_t hash1(const string &key) // Hash 1 (Polynomial Rollback)
{
    const size_t prime = 31;
    size_t hashValue = 0;
    const size_t m = 1e9 + 9;
    size_t pPow = 1;
    for (char c : key)
    {
        hashValue = (hashValue + (c - 'a' + 1) * pPow) % m;
        pPow = (pPow * prime) % m;
    }
    return hashValue;
}

size_t hash2(const string &key) // Hash 2 (djb2 hash function)
{
    size_t hashValue = 5381;
    for (char c : key)
    {
        hashValue = ((hashValue << 5) + hashValue) + c;
    }
    return hashValue;
}

// Red Black Tree

template <typename K, typename V>
class TreeNode
{
public:
    K key;
    V value;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int color;
    TreeNode(const K &k, const V &v) : key(k), value(v)
    {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = 1;
    }
};

template <typename K, typename V> // RBT for separate chaining
class RedBlackTree
{
    TreeNode<K, V> *root;
    TreeNode<K, V> *TNULL;
    int size;
    void initializeTNULL()
    {
        TNULL = new TreeNode<K, V>(K(), V());
        TNULL->color = 0;
        TNULL->left = TNULL;
        TNULL->right = TNULL;
    }
    void leftRotate(TreeNode<K, V> *x)
    {
        TreeNode<K, V> *y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(TreeNode<K, V> *x)
    {
        TreeNode<K, V> *y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }
    void insertFixup(TreeNode<K, V> *z)
    {
        while (z->parent != nullptr && z->parent->color == 1)
        {
            if (z->parent == z->parent->parent->left)
            {
                TreeNode<K, V> *y = z->parent->parent->right;
                if (y != nullptr && y->color == 1)
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color = 1;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                TreeNode<K, V> *y = z->parent->parent->left;
                if (y != nullptr && y->color == 1)
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color = 1;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = 0;
    }
    void transplant(TreeNode<K, V> *u, TreeNode<K, V> *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    TreeNode<K, V> *minimum(TreeNode<K, V> *x)
    {
        while (x->left != TNULL)
        {
            x = x->left;
        }
        return x;
    }
    void deleteFixup(TreeNode<K, V> *x)
    {
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                TreeNode<K, V> *w = x->parent->right;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == 0 && w->right->color == 0)
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == 0)
                    {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                TreeNode<K, V> *w = x->parent->left;
                if (w->color == 1)
                {
                    w->color = 0;
                    w->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->left->color == 0 && w->right->color == 0)
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == 0)
                    {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
    void destroy(TreeNode<K, V> *node)
    {
        if (node != nullptr && node != TNULL)
        {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    RedBlackTree()
    {
        initializeTNULL();
        root = TNULL;
        size = 0;
    }
    ~RedBlackTree()
    {
        destroy(root);
        delete TNULL;
    }
    bool isEmpty() // To check if here any node exists or not
    {
        return size == 0;
    }
    TreeNode<K, V> *getRoot() const // To get the root of
    {
        return root;
    }
    bool isTNULL(TreeNode<K, V> *node) const // To check if the node whether a leaf or not
    {
        return node == TNULL;
    }
    V *search(const K &key) // Searches for a given key
    {
        TreeNode<K, V> *current = root;
        while (current != TNULL)
        {
            if (key == current->key)
            {
                return &(current->value);
            }
            else if (key < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return nullptr;
    }
    void insert(const K &key, const V &value) // Inserts a key value pair in RBT
    {
        TreeNode<K, V> *node = new TreeNode<K, V>(key, value);
        node->left = TNULL;
        node->right = TNULL;
        TreeNode<K, V> *y = nullptr;
        TreeNode<K, V> *x = root;
        while (x != TNULL)
        {
            y = x;
            if (x->key == node->key)
            {
                return;
            }
            if (node->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (y->key > node->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
        insertFixup(node);
        size++;
    }
    void deleteNode(const K &key) // Deletes an existing node from RBT
    {
        TreeNode<K, V> *z = root;
        while (z != TNULL)
        {
            if (z->key == key)
            {
                break;
            }
            else if (z->key > key)
            {
                z = z->left;
            }
            else
            {
                z = z->right;
            }
        }
        if (z == TNULL)
        {
            return;
        }
        TreeNode<K, V> *y = z;
        TreeNode<K, V> *x = TNULL;
        int yOriginalColor = y->color;
        if (z->right == TNULL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else if (z->left == TNULL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else
        {
            y = minimum(y->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        size--;
        if (yOriginalColor == 0)
        {
            deleteFixup(x);
        }
    }
};

// Hash Tables

class HashTableSeparateChaining // Separate Chainiing
{
    vector<RedBlackTree<string, int>> table;
    size_t tableSize;
    double loadFactor;
    size_t threshold;
    size_t collisions;
    size_t size;
    size_t (*hashFunc)(const string &);
    size_t normalize(size_t hash)
    {
        return (hash & 0x7FFFFFFF) % tableSize;
    }
    void resizeTable()
    {
        size_t oldSize = tableSize;
        tableSize = nextPrime(tableSize * 2);
        threshold = static_cast<size_t>(tableSize * loadFactor);
        collisions = 0;
        vector<RedBlackTree<string, int>> newTable(tableSize);
        for (auto &bucket : table)
        {
            queue<TreeNode<string, int> *> q;
            auto *root = bucket.getRoot();
            if (root != nullptr && !bucket.isTNULL(root))
            {
                q.push(root);
            }
            while (!q.empty())
            {
                auto *node = q.front();
                q.pop();
                if (bucket.isTNULL(node))
                {
                    continue;
                }
                size_t idx = normalize(hashFunc(node->key));
                if (!newTable[idx].isEmpty())
                {
                    collisions++;
                }
                newTable[idx].insert(node->key, node->value);
                if (!bucket.isTNULL(node->left))
                {
                    q.push(node->left);
                }
                if (!bucket.isTNULL(node->right))
                {
                    q.push(node->right);
                }
            }
        }
        table = move(newTable);
    }

public:
    HashTableSeparateChaining(size_t tSize, double lf, size_t (*hf)(const string &)) : loadFactor(lf), hashFunc(hf), collisions(0)
    {
        tableSize = nextPrime(tSize);
        table.resize(tableSize);
        threshold = static_cast<size_t>(loadFactor * tableSize);
        size = 0;
    }
    ~HashTableSeparateChaining()
    {
        clear();
    }
    bool insert(const string &key, int value) // Insertion in hash table
    {
        size_t idx = normalize(hashFunc(key));
        if (table[idx].search(key) != nullptr)
        {
            return false;
        }
        if (!table[idx].isEmpty())
        {
            collisions++;
        }
        table[idx].insert(key, value);
        size++;
        if (size >= threshold)
        {
            resizeTable();
        }
        return true;
    }
    int *search(const string &key) // Searches for a key in the hash table
    {
        size_t idx = normalize(hashFunc(key));
        return table[idx].search(key);
    }
    void deleteElement(const string &key) // Deletes an existing element from hash table
    {
        size_t idx = normalize(hashFunc(key));
        if (table[idx].search(key))
        {
            table[idx].deleteNode(key);
            size--;
        }
    }
    int getCollisions() const // Returns total collision for insertion
    {
        return collisions;
    }
    void clear()
    {
        table.clear();
        table.resize(tableSize);
        size = 0;
        collisions = 0;
    }
};

// Open addressing

class HashTableLinearProbing // Hash table linear probing
{
    vector<pair<string, int>> table;
    size_t tableSize;
    pair<string, int> RIP;
    double loadFactor;
    size_t threshold;
    int collisions;       // collisions during insertion
    int probeCount;       // probe count during insertion
    int deleteProbeCount; // probe count during deletion
    size_t (*hashFunc)(const string &);
    // size_t diff;          // Needed for probing (A number for which this number and tableSize are relatively prime)
    size_t size;
    // size_t gcd(size_t a, size_t b)
    // {
    //     while (b != 0)
    //     {
    //         size_t temp = b;
    //         b = a % b;
    //         a = temp;
    //     }
    //     return a;
    // }
    // size_t findDiff(size_t tableSize)
    // {
    //     if (tableSize <= 2)
    //     {
    //         return 1;
    //     }
    //     for (size_t a = 2; a <= tableSize; a++)
    //     {
    //         if (gcd(a, tableSize) == 1)
    //         {
    //             return a;
    //         }
    //     }
    //     return 1;
    // }
    // size_t probeOffset(size_t x) // Probing function
    // {
    //     return diff * x;
    // }
    size_t probeOffset(size_t x) // Probing function
    {
        return 5 * x;
    }
    size_t normalizeIndex(size_t hash)
    {
        return (hash & 0x7FFFFFFF) % tableSize;
    }
    void resizeTable()
    {
        vector<pair<string, int>> oldTable = table;
        size_t oldSize = tableSize;
        tableSize = nextPrime(tableSize * 2);
        threshold = static_cast<size_t>(tableSize * loadFactor);
        // diff = findDiff(tableSize);
        collisions = 0;
        probeCount=0;
        size = 0;
        table.assign(tableSize, {"", -1});
        for (auto &element : oldTable)
        {
            if (!element.first.empty() && element != RIP)
            {
                insert(element.first, element.second);
            }
        }
    }
public:
    HashTableLinearProbing(size_t tSize, double lf, size_t (*hf)(const string &)) : loadFactor(lf), hashFunc(hf), probeCount(0), collisions(0)
    {
        RIP = {"#RIP#", -1};
        tableSize = nextPrime(tSize);
        table.resize(tableSize, {"", -1});
        threshold = static_cast<size_t>(tableSize * loadFactor);
        // diff = findDiff(tableSize);
        deleteProbeCount = 0;
        size = 0;
    }
    bool insert(const string &key, int value)     // Inserts a (key,value) pair in a hash table
    {
        if (size >= threshold)
        {
            resizeTable();
        }
        if (search(key).first != nullptr)
        {
            return false;
        }
        size_t hash = hashFunc(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        int firstDeletedIndex = -1;
        bool collisionCounted = false;
        while (!table[idx].first.empty())
        {
            probeCount++;
            if (table[idx] == RIP)
            {
                if (firstDeletedIndex == -1)
                {
                    firstDeletedIndex = idx;
                }
            }
            else if (!collisionCounted)
            {
                collisions++;
                collisionCounted = true;
            }
            idx = normalizeIndex(hash + probeOffset(x));
            i++;
            x = i;
        }
        probeCount++;
        if (firstDeletedIndex != -1)
        {
            idx = firstDeletedIndex;
        }
        table[idx] = {key, value};
        size++;
        return true;
    }
    pair<int*,int> search(const string &key)    // Checks for a key whether it is in the table or not
    {                                           // and returns {node,probeCountForTheSearch} pair
        int searchProbe=0;
        size_t hash = hashFunc(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        while (!table[idx].first.empty())
        {
            searchProbe++;
            if (table[idx] != RIP && table[idx].first == key)
            {
                return {&table[idx].second,searchProbe};
            }
            idx = normalizeIndex(hash + probeOffset(x));
            i++;
            x = i;
        }
        return {nullptr,searchProbe};
    }
    bool deleteElement(const string &key)      // Deletes a key,value pair from hash table
    {
        size_t hash = hashFunc(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        while (!table[idx].first.empty())
        {
            deleteProbeCount++;
            if (table[idx] != RIP && table[idx].first == key)
            {
                table[idx] = RIP;
                size--;
                return true;
            }
            idx = normalizeIndex(hash + probeOffset(x));
            i++;
            x = i;
        }
        return false;
    }
    int getCollisions() const       // Total collisions during insertion
    {
        return collisions;
    }
    void clear()
    {
        table.assign(tableSize, {"", -1});
        size = 0;
        collisions = 0;
        probeCount = 0;
        deleteProbeCount=0;
    }
};

class HashTableDoubleHashing      // Hash table double hashing
{
    vector<pair<string, int>> table;
    size_t tableSize;
    pair<string, int> RIP;
    double loadFactor;
    size_t threshold;
    int collisions;       // collisions during insertion
    int probeCount;       // probe count during insertion
    int deleteProbeCount; // probe count during deletion
    size_t (*hashFunc1)(const string &);
    size_t (*hashFunc2)(const string &);
    size_t size;
    size_t probeOffset(const string &key,size_t x) // Probing function
    {
        return  x*hashFunc2(key);
    }
    size_t normalizeIndex(size_t hash)
    {
        return (hash & 0x7FFFFFFF) % tableSize;
    }
    void resizeTable()
    {
        vector<pair<string, int>> oldTable = table;
        size_t oldSize = tableSize;
        tableSize = nextPrime(tableSize * 2);
        threshold = static_cast<size_t>(tableSize * loadFactor);
        collisions = 0;
        probeCount=0;
        size = 0;
        table.assign(tableSize, {"", -1});
        for (auto &element : oldTable)
        {
            if (!element.first.empty() && element != RIP)
            {
                insert(element.first, element.second);
            }
        }
    }
public:
    HashTableDoubleHashing(size_t tSize, double lf, size_t (*hf1)(const string &), size_t (*hf2)(const string &)) : loadFactor(lf), hashFunc1(hf1), hashFunc2(hf2), probeCount(0), collisions(0)
    {
        RIP = {"#RIP#", -1};
        tableSize = nextPrime(tSize);
        table.resize(tableSize, {"", -1});
        threshold = static_cast<int>(tableSize * loadFactor);
        deleteProbeCount = 0;
        size = 0;
    }
    bool insert(const string &key, int value)     // Inserts a (key,value) pair in a hash table
    {
        if (size >= threshold)
        {
            resizeTable();
        }
        if (search(key).first != nullptr)
        {
            return false;
        }
        size_t hash = hashFunc1(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        int firstDeletedIndex = -1;
        bool collisionCounted = false;
        while (!table[idx].first.empty())
        {
            probeCount++;
            if (table[idx] == RIP)
            {
                if (firstDeletedIndex == -1)
                {
                    firstDeletedIndex = idx;
                }
            }
            else if (!collisionCounted)
            {
                collisions++;
                collisionCounted = true;
            }
            idx = normalizeIndex(hash + probeOffset(key,x));
            i++;
            x = i;
        }
        probeCount++;
        if (firstDeletedIndex != -1)
        {
            idx = firstDeletedIndex;
        }
        table[idx] = {key, value};
        size++;
        return true;
    }
    pair<int*,int> search(const string &key)    // Checks for a key whether it is in the table or not
    {                                           // and returns {node,probeCountForTheSearch} pair
        int searchProbe=0;
        size_t hash = hashFunc1(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        while (!table[idx].first.empty())
        {
            searchProbe++;
            if (table[idx] != RIP && table[idx].first == key)
            {
                return {&table[idx].second,searchProbe};
            }
            idx = normalizeIndex(hash + probeOffset(key,x));
            i++;
            x = i;
        }
        return {nullptr,searchProbe};
    }
    bool deleteElement(const string &key)      // Deletes a key,value pair from hash table
    {
        size_t hash = hashFunc1(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        while (!table[idx].first.empty())
        {
            deleteProbeCount++;
            if (table[idx] != RIP && table[idx].first == key)
            {
                table[idx] = RIP;
                size--;
                return true;
            }
            idx = normalizeIndex(hash + probeOffset(key,x));
            i++;
            x = i;
        }
        return false;
    }
    int getCollisions() const       // Total collisions during insertion
    {
        return collisions;
    }
    void clear()
    {
        table.assign(tableSize, {"", -1});
        size = 0;
        collisions = 0;
        probeCount = 0;
        deleteProbeCount=0;
    }
};

void createReport(ostream& out)
{
    vector<string> toInserted=generateRandomWords(10000);
    mt19937 rng(random_device{}());

    double lf=0.4;

    // Separate Chaining

    out<<"-------- Separate Chaining  Hash1--------\n";
    for(int i=0;i<6;i++)
    {
        double currentLf=lf+(i*0.1);
        HashTableSeparateChaining scht(100,currentLf,hash1);
        vector<string> inserted;
        int value=1;
        for(const string& temp:toInserted)
        {
            if(scht.search(temp)==nullptr)
            {
                scht.insert(temp,value);
                inserted.push_back(temp);
                value++;
            }
        }
        out<<"Collision for load factor "<<currentLf<<" is : "<<scht.getCollisions()<<"\n";
        vector<string> searchList=inserted;
        shuffle(searchList.begin(),searchList.end(),rng);
        int testSize=inserted.size()/10;
        searchList.resize(testSize);
        auto start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            scht.search(key);
        }
        auto end=high_resolution_clock::now();
        double averageTimeBefore=duration<double,nano>(end-start).count()/testSize;
        vector<string> toDelete(searchList.begin(),searchList.begin()+testSize/2);
        vector<string> toKeep(searchList.begin()+testSize/2,searchList.end());
        for(const auto& key:toDelete)
        {
            scht.deleteElement(key);
        }
        start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            scht.search(key);
        }
        end=high_resolution_clock::now();
        double averageTimeAfter=duration<double,nano>(end-start).count()/testSize;
        out<<"Average search time (Before Deletion) for load factor "<<currentLf<<" : "<<averageTimeBefore<<" ns\n";
        out<<"Average search time (After Deletion) for load factor "<<currentLf<<" : "<<averageTimeAfter<<" ns\n";
    }
    lf=0.4;
    out<<"-------- Separate Chaining  Hash2--------\n";
    for(int i=0;i<6;i++)
    {
        double currentLf=lf+(i*0.1);
        HashTableSeparateChaining scht(100,currentLf,hash2);
        vector<string> inserted;
        int value=1;
        for(const string& temp:toInserted)
        {
            if(scht.search(temp)==nullptr)
            {
                scht.insert(temp,value);
                inserted.push_back(temp);
                value++;
            }
        }
        out<<"Collision for load factor "<<currentLf<<" is : "<<scht.getCollisions()<<"\n";
        vector<string> searchList=inserted;
        shuffle(searchList.begin(),searchList.end(),rng);
        int testSize=inserted.size()/10;
        searchList.resize(testSize);
        auto start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            scht.search(key);
        }
        auto end=high_resolution_clock::now();
        double averageTimeBefore=duration<double,nano>(end-start).count()/testSize;
        vector<string> toDelete(searchList.begin(),searchList.begin()+testSize/2);
        vector<string> toKeep(searchList.begin()+testSize/2,searchList.end());
        for(const auto& key:toDelete)
        {
            scht.deleteElement(key);
        }
        start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            scht.search(key);
        }
        end=high_resolution_clock::now();
        double averageTimeAfter=duration<double,nano>(end-start).count()/testSize;
        out<<"Average search time (Before Deletion) for load factor "<<currentLf<<" : "<<averageTimeBefore<<" ns\n";
        out<<"Average search time (After Deletion) for load factor "<<currentLf<<" : "<<averageTimeAfter<<" ns\n";
    }

    // Linear Probing


    lf=0.4;
    out<<"\n--------Linear Probing Hash1---------\n";
    for(int i=0;i<6;i++)
    {
        double currentLf=lf+i*0.1;
        HashTableLinearProbing lpht(100,currentLf,hash1);
        vector<string> inserted;
        int value=1;
        for(const string& temp:toInserted)
        {
            if(lpht.search(temp).first==nullptr)
            {
                lpht.insert(temp,value);
                inserted.push_back(temp);
                value++;
            }
        }
        out<<"Collision for load factor "<<currentLf<<" is : "<<lpht.getCollisions()<<"\n";
        vector<string> searchList=inserted;
        shuffle(searchList.begin(),searchList.end(),rng);
        int testSize=inserted.size()/10;
        int totalProbesBefore=0;
        searchList.resize(testSize);
        auto start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesBefore+=lpht.search(key).second;
        }
        auto end=high_resolution_clock::now();
        double averageTimeBefore=duration<double,nano>(end-start).count()/testSize;
        double averageProbesBefore=totalProbesBefore/(double)testSize;
        vector<string> toDelete(searchList.begin(),searchList.begin()+testSize/2);
        vector<string> toKeep(searchList.begin()+testSize/2,searchList.end());
        for(const auto& key:toDelete)
        {
            lpht.deleteElement(key);
        }
        int totalProbesAfter=0;
        start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesAfter+=lpht.search(key).second;
        }
        end=high_resolution_clock::now();
        double averageTimeAfter=duration<double,nano>(end-start).count()/testSize;
        double averageProbesAfter=totalProbesAfter/(double)testSize;
        
        out<<"Average search time (After Deletion) for load factor "<<currentLf<<" : "<<averageTimeAfter<<" ns\n";
        out<<"Average probes (Before Deletion) for load factor "<<currentLf<<" : "<<averageProbesBefore<<" ns\n";
        out<<"Average search time (Before Deletion) for load factor "<<currentLf<<" : "<<averageTimeBefore<<" ns\n";
        out<<"Average probes (After Deletion) for load factor "<<currentLf<<" : "<<averageProbesAfter<<" ns\n";
    }
    lf=0.4;
    out<<"\n--------Linear Probing Hash2---------\n";
    for(int i=0;i<6;i++)
    {
        double currentLf=lf+i*0.1;
        HashTableLinearProbing lpht(100,currentLf,hash2);
        vector<string> inserted;
        int value=1;
        for(const string& temp:toInserted)
        {
            if(lpht.search(temp).first==nullptr)
            {
                lpht.insert(temp,value);
                inserted.push_back(temp);
                value++;
            }
        }
        out<<"Collision for load factor "<<currentLf<<" is : "<<lpht.getCollisions()<<"\n";
        vector<string> searchList=inserted;
        shuffle(searchList.begin(),searchList.end(),rng);
        int testSize=inserted.size()/10;
        int totalProbesBefore=0;
        searchList.resize(testSize);
        auto start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesBefore+=lpht.search(key).second;
        }
        auto end=high_resolution_clock::now();
        double averageTimeBefore=duration<double,nano>(end-start).count()/testSize;
        double averageProbesBefore=totalProbesBefore/(double)testSize;
        vector<string> toDelete(searchList.begin(),searchList.begin()+testSize/2);
        vector<string> toKeep(searchList.begin()+testSize/2,searchList.end());
        for(const auto& key:toDelete)
        {
            lpht.deleteElement(key);
        }
        int totalProbesAfter=0;
        start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesAfter+=lpht.search(key).second;
        }
        end=high_resolution_clock::now();
        double averageTimeAfter=duration<double,nano>(end-start).count()/testSize;
        double averageProbesAfter=totalProbesAfter/(double)testSize;
        
        out<<"Average search time (After Deletion) for load factor "<<currentLf<<" : "<<averageTimeAfter<<" ns\n";
        out<<"Average probes (Before Deletion) for load factor "<<currentLf<<" : "<<averageProbesBefore<<" ns\n";
        out<<"Average search time (Before Deletion) for load factor "<<currentLf<<" : "<<averageTimeBefore<<" ns\n";
        out<<"Average probes (After Deletion) for load factor "<<currentLf<<" : "<<averageProbesAfter<<" ns\n";
    }

    // Double Hashing

    lf=0.4;
    out<<"\n--------Double Hashing Hash1---------\n";
    for(int i=0;i<6;i++)
    {
        double currentLf=lf+i*0.1;
        HashTableDoubleHashing dhht(100,currentLf,hash1,hash2);
        vector<string> inserted;
        int value=1;
        for(const string& temp:toInserted)
        {
            if(dhht.search(temp).first==nullptr)
            {
                dhht.insert(temp,value);
                inserted.push_back(temp);
                value++;
            }
        }
        out<<"Collision for load factor "<<currentLf<<" is : "<<dhht.getCollisions()<<"\n";
        vector<string> searchList=inserted;
        shuffle(searchList.begin(),searchList.end(),rng);
        int testSize=inserted.size()/10;
        int totalProbesBefore=0;
        searchList.resize(testSize);
        auto start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesBefore+=dhht.search(key).second;
        }
        auto end=high_resolution_clock::now();
        double averageTimeBefore=duration<double,nano>(end-start).count()/testSize;
        double averageProbesBefore=totalProbesBefore/(double)testSize;
        vector<string> toDelete(searchList.begin(),searchList.begin()+testSize/2);
        vector<string> toKeep(searchList.begin()+testSize/2,searchList.end());
        for(const auto& key:toDelete)
        {
            dhht.deleteElement(key);
        }
        int totalProbesAfter=0;
        start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesAfter+=dhht.search(key).second;
        }
        end=high_resolution_clock::now();
        double averageTimeAfter=duration<double,nano>(end-start).count()/testSize;
        double averageProbesAfter=totalProbesAfter/(double)testSize;
        
        out<<"Average search time (After Deletion) for load factor "<<currentLf<<" : "<<averageTimeAfter<<" ns\n";
        out<<"Average probes (Before Deletion) for load factor "<<currentLf<<" : "<<averageProbesBefore<<"\n";
        out<<"Average search time (Before Deletion) for load factor "<<currentLf<<" : "<<averageTimeBefore<<" ns\n";
        out<<"Average probes (After Deletion) for load factor "<<currentLf<<" : "<<averageProbesAfter<<"\n";
    }
    lf=0.4;
    out<<"\n--------Double Hashing Hash2---------\n";
    for(int i=0;i<6;i++)
    {
        double currentLf=lf+i*0.1;
        HashTableDoubleHashing dhht(100,currentLf,hash2,hash1);
        vector<string> inserted;
        int value=1;
        for(const string& temp:toInserted)
        {
            if(dhht.search(temp).first==nullptr)
            {
                dhht.insert(temp,value);
                inserted.push_back(temp);
                value++;
            }
        }
        out<<"Collision for load factor "<<currentLf<<" is : "<<dhht.getCollisions()<<"\n";
        vector<string> searchList=inserted;
        shuffle(searchList.begin(),searchList.end(),rng);
        int testSize=inserted.size()/10;
        int totalProbesBefore=0;
        searchList.resize(testSize);
        auto start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesBefore+=dhht.search(key).second;
        }
        auto end=high_resolution_clock::now();
        double averageTimeBefore=duration<double,nano>(end-start).count()/testSize;
        double averageProbesBefore=totalProbesBefore/(double)testSize;
        vector<string> toDelete(searchList.begin(),searchList.begin()+testSize/2);
        vector<string> toKeep(searchList.begin()+testSize/2,searchList.end());
        for(const auto& key:toDelete)
        {
            dhht.deleteElement(key);
        }
        int totalProbesAfter=0;
        start=high_resolution_clock::now();
        for(const auto& key:searchList)
        {
            totalProbesAfter+=dhht.search(key).second;
        }
        end=high_resolution_clock::now();
        double averageTimeAfter=duration<double,nano>(end-start).count()/testSize;
        double averageProbesAfter=totalProbesAfter/(double)testSize;
        
        out<<"Average search time (After Deletion) for load factor "<<currentLf<<" : "<<averageTimeAfter<<" ns\n";
        out<<"Average probes (Before Deletion) for load factor "<<currentLf<<" : "<<averageProbesBefore<<"\n";
        out<<"Average search time (Before Deletion) for load factor "<<currentLf<<" : "<<averageTimeBefore<<" ns\n";
        out<<"Average probes (After Deletion) for load factor "<<currentLf<<" : "<<averageProbesAfter<<"\n";
    }
}

int main()
{
    ofstream fout("report.txt");
    if(!fout.is_open())
    {
        cerr<<"Failed to open output file.\n";
        return 1;
    }
    createReport(cout);
    createReport(fout);
    fout.close();
    return 0;
}