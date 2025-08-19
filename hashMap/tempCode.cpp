#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

bool isPrime(int n) // Prime Checker
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

int nextPrime(int n) // To find next closest prime number
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

string generateRandomString(int minLen = 5, int maxLen = 10)
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

vector<string> generateRandomWords(int count) // Random word generator
{
    vector<string> words;
    while (words.size() < count)
    {
        words.push_back(generateRandomString());
    }
    return words;
}

size_t hash1(const string &key) // Hash 1 (Polynomial Rolling)
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

size_t hash2(const string &key)
{
    size_t hashValue = 5381;
    for (char c : key)
    {
        hashValue = ((hashValue << 5) + hashValue) + c;
    }
    return hashValue;
}

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

template <typename K, typename V>
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
    void destroy(TreeNode<K, V> *node)
    {
        if (node != nullptr && node != TNULL)
        {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
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
    bool isEmpty()
    {
        return size == 0;
    }
    TreeNode<K, V> *getRoot() const
    {
        return root;
    }
    bool isTNULL(TreeNode<K, V> *node) const
    {
        return node == TNULL;
    }
    V *search(const K &key)
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
    void insert(const K &key, const V &value)
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
    void deleteNode(const K &key)
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

class HashTableSeparateChaining
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
        threshold = static_cast<int>(tableSize * loadFactor);
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
        threshold = static_cast<int>(loadFactor * tableSize);
        size = 0;
    }
    ~HashTableSeparateChaining()
    {
        clear();
    }
    bool insert(const string &key, int value)
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
    int *search(const string &key)
    {
        size_t idx = normalize(hashFunc(key));
        return table[idx].search(key);
    }
    void deleteElement(const string &key)
    {
        size_t idx = normalize(hashFunc(key));
        if (table[idx].search(key))
        {
            table[idx].deleteNode(key);
            size--;
        }
    }
    int getCollisions() const
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

class HashTableLinearProbling
{
    vector<pair<string, int>> table;
    size_t tableSize;
    pair<string, int> RIP;
    double loadFactor;
    int collisions;
    int deleteProbeCount;
    int probeCount;
    size_t (*hashFunc)(const string &);
    int threshold;
    size_t diff;
    size_t size;
    size_t gcd(size_t a, size_t b)
    {
        while (b != 0)
        {
            size_t temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    size_t findDiff(size_t tableSize)
    {
        if (tableSize <= 2)
        {
            return 1;
        }
        for (size_t a = 2; a <= tableSize; a++)
        {
            if (gcd(a, tableSize) == 1)
            {
                return a;
            }
        }
        return 1;
    }
    size_t probeOffset(size_t x)
    {
        return diff * x;
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
        threshold = static_cast<int>(tableSize * loadFactor);
        diff = findDiff(tableSize);
        collisions = 0;
        probeCount = 0;
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
    HashTableLinearProbling(size_t tSize, double lf, size_t (*hf)(const string &)) : loadFactor(lf), hashFunc(hf), probeCount(0), collisions(0)
    {
        RIP = {"#RIP#", -1};
        tableSize = nextPrime(tSize);
        table.resize(tableSize, {"", -1});
        threshold = static_cast<int>(tableSize * loadFactor);
        diff = findDiff(tableSize);
        deleteProbeCount=0;
        size = 0;
    }
    bool insert(const string &key, int value)
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
    pair<int*,int> search(const string &key)
    {
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
    bool deleteElement(const string &key)
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
    int getCollisions() const
    {
        return collisions;
    }
    int getProbeCount() const
    {
        return probeCount;
    }
    void clear()
    {
        table.assign(tableSize, {"", -1}); // Reset all slots to empty
        size = 0;
        collisions = 0;
        probeCount = 0;
    }
};

class HashTableDoubleHashing
{
    vector<pair<string, int>> table;
    size_t tableSize;
    pair<string, int> RIP;
    double loadFactor;
    int collisions;
    int probeCount;
    int probeDeleteCount;
    int insertions;
    size_t (*hashFunc1)(const string &);
    size_t (*hashFunc2)(const string &);
    int threshold;
    size_t size;
    size_t probeOffset(const string &key, size_t x)
    {
        return x * hashFunc2(key);
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
        threshold = static_cast<int>(tableSize * loadFactor);
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
        size = 0;
        probeDeleteCount=0;
    }
    ~HashTableDoubleHashing()
    {
        clear();
    }

    bool insert(const string &key, int value)
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
            idx = normalizeIndex(hash + probeOffset(key, x));
            i++;
            x = i;
        }
        if (firstDeletedIndex != -1)
        {
            idx = firstDeletedIndex;
        }
        table[idx] = {key, value};
        size++;
        return true;
    }
    pair<int*,int> search(const string &key)
    {
        int probeSearch=0;
        size_t hash = hashFunc1(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        while (!table[idx].first.empty())
        {
            probeSearch++;
            if (table[idx] != RIP && table[idx].first == key)
            {
                return {&table[idx].second,probeSearch};
            }
            idx = normalizeIndex(hash + probeOffset(key, x));
            i++;
            x = i;
        }
        return {nullptr,probeSearch};
    }
    bool deleteElement(const string &key)
    {
        size_t hash = hashFunc1(key);
        size_t idx = normalizeIndex(hash);
        size_t i = 1;
        size_t x = 1;
        while (!table[idx].first.empty())
        {
            probeDeleteCount++;
            if (table[idx] != RIP && table[idx].first == key)
            {
                table[idx] = RIP;
                size--;
                return true;
            }
            idx = normalizeIndex(hash + probeOffset(key, x));
            i++;
            x = i;
        }
        return false;
    }
    int getCollisions() const
    {
        return collisions;
    }
    int getProbeCount() const
    {
        return probeCount;
    }
    void clear()
    {
        table.assign(tableSize, {"", -1});
        size = 0;
        collisions = 0;
        probeCount = 0;
    }
};

void createReport() {
    vector<string> toInserted = generateRandomWords(20000);
    mt19937 rng(random_device{}());

    double lf = 0.4;
    cout << "==================== SEPARATE CHAINING ====================\n";
    for (int i = 0; i < 6; i++) {
        double currentLF = lf + i * 0.1;
        HashTableSeparateChaining scht(10001, currentLF, hash1);
        vector<string> inserted;

        // Insert
        for (const string& temp : toInserted) {
            if (scht.search(temp) == nullptr) {
                scht.insert(temp, 1);
                inserted.push_back(temp);
            }
        }

        // Search test before deletion
        vector<string> searchSet = inserted;
        shuffle(searchSet.begin(), searchSet.end(), rng);
        int testSize = inserted.size() / 10;
        searchSet.resize(testSize);

        auto start = high_resolution_clock::now();
        for (const auto& key : searchSet)
            scht.search(key);
        auto end = high_resolution_clock::now();

        double avgTimeBefore = duration<double, micro>(end - start).count() / testSize;

        // Deletion: delete half of searchSet
        vector<string> toDelete(searchSet.begin(), searchSet.begin() + testSize / 2);
        vector<string> toKeep(searchSet.begin() + testSize / 2, searchSet.end());

        for (const auto& key : toDelete)
            scht.deleteElement(key);

        // Search test after deletion (50% expected to fail)
        vector<string> afterSearchSet = toDelete;
        afterSearchSet.insert(afterSearchSet.end(), toKeep.begin(), toKeep.end());
        shuffle(afterSearchSet.begin(), afterSearchSet.end(), rng);

        start = high_resolution_clock::now();
        for (const auto& key : afterSearchSet)
            scht.search(key);
        end = high_resolution_clock::now();

        double avgTimeAfter = duration<double, micro>(end - start).count() / afterSearchSet.size();

        // Report
        cout << "Load Factor: " << currentLF << "\n";
        cout << " - Avg Search Time (Before Deletion): " << avgTimeBefore << " micro second\n";
        cout << " - Avg Search Time (After Deletion): " << avgTimeAfter << " micro second\n\n";
    }

    // --------------------------------------------------
    lf = 0.4;
    cout << "==================== LINEAR PROBING ====================\n";
    for (int i = 0; i < 6; i++) {
        double currentLF = lf + i * 0.1;
        HashTableLinearProbling lpht(10001, currentLF, hash1);
        vector<string> inserted;

        for (const string& temp : toInserted) {
            if (lpht.search(temp).first == nullptr) {
                lpht.insert(temp, 1);
                inserted.push_back(temp);
            }
        }

        cout << "Load Factor: " << currentLF << "\n";
        cout << " - Collision Count: " << lpht.getCollisions() << "\n";
        cout << " - Avg Insert Probe: " << lpht.getProbeCount() / (double)inserted.size() << "\n";

        // Search test before deletion
        vector<string> searchSet = inserted;
        shuffle(searchSet.begin(), searchSet.end(), rng);
        int testSize = inserted.size() / 10;
        searchSet.resize(testSize);

        int totalProbeBefore = 0;
        auto start = high_resolution_clock::now();
        for (const auto& key : searchSet)
            totalProbeBefore += lpht.search(key).second;
        auto end = high_resolution_clock::now();
        double avgTimeBefore = duration<double, micro>(end - start).count() / testSize;
        double avgProbeBefore = totalProbeBefore / (double)testSize;

        // Delete half
        vector<string> toDelete(searchSet.begin(), searchSet.begin() + testSize / 2);
        vector<string> toKeep(searchSet.begin() + testSize / 2, searchSet.end());
        for (const auto& key : toDelete)
            lpht.deleteElement(key);

        // Search after deletion
        vector<string> afterSearchSet = toDelete;
        afterSearchSet.insert(afterSearchSet.end(), toKeep.begin(), toKeep.end());
        shuffle(afterSearchSet.begin(), afterSearchSet.end(), rng);

        int totalProbeAfter = 0;
        start = high_resolution_clock::now();
        for (const auto& key : afterSearchSet)
            totalProbeAfter += lpht.search(key).second;
        end = high_resolution_clock::now();
        double avgTimeAfter = duration<double, micro>(end - start).count() / afterSearchSet.size();
        double avgProbeAfter = totalProbeAfter / (double)afterSearchSet.size();

        // Report
        cout << " - Avg Search Time (Before): " << avgTimeBefore << " micro second\n";
        cout << " - Avg Probe (Before): " << avgProbeBefore << "\n";
        cout << " - Avg Search Time (After): " << avgTimeAfter << " micro second\n";
        cout << " - Avg Probe (After): " << avgProbeAfter << "\n\n";
    }

    // --------------------------------------------------
    lf = 0.4;
    cout << "==================== DOUBLE HASHING ====================\n";
    for (int i = 0; i < 6; i++) {
        double currentLF = lf + i * 0.1;
        HashTableDoubleHashing dhht(10001, currentLF, hash1, hash2);
        vector<string> inserted;

        for (const string& temp : toInserted) {
            if (dhht.search(temp).first == nullptr) {
                dhht.insert(temp, 1);
                inserted.push_back(temp);
            }
        }

        cout << "Load Factor: " << currentLF << "\n";
        cout << " - Collision Count: " << dhht.getCollisions() << "\n";
        cout << " - Avg Insert Probe: " << dhht.getProbeCount() / (double)inserted.size() << "\n";

        // Search test before deletion
        vector<string> searchSet = inserted;
        shuffle(searchSet.begin(), searchSet.end(), rng);
        int testSize = inserted.size() / 10;
        searchSet.resize(testSize);

        int totalProbeBefore = 0;
        auto start = high_resolution_clock::now();
        for (const auto& key : searchSet)
            totalProbeBefore += dhht.search(key).second;
        auto end = high_resolution_clock::now();
        double avgTimeBefore = duration<double, micro>(end - start).count() / testSize;
        double avgProbeBefore = totalProbeBefore / (double)testSize;

        // Delete half
        vector<string> toDelete(searchSet.begin(), searchSet.begin() + testSize / 2);
        vector<string> toKeep(searchSet.begin() + testSize / 2, searchSet.end());
        for (const auto& key : toDelete)
            dhht.deleteElement(key);

        // Search after deletion
        vector<string> afterSearchSet = toDelete;
        afterSearchSet.insert(afterSearchSet.end(), toKeep.begin(), toKeep.end());
        shuffle(afterSearchSet.begin(), afterSearchSet.end(), rng);

        int totalProbeAfter = 0;
        start = high_resolution_clock::now();
        for (const auto& key : afterSearchSet)
            totalProbeAfter += dhht.search(key).second;
        end = high_resolution_clock::now();
        double avgTimeAfter = duration<double, micro>(end - start).count() / afterSearchSet.size();
        double avgProbeAfter = totalProbeAfter / (double)afterSearchSet.size();

        // Report
        cout << " - Avg Search Time (Before): " << avgTimeBefore << " micro second\n";
        cout << " - Avg Probe (Before): " << avgProbeBefore << "\n";
        cout << " - Avg Search Time (After): " << avgTimeAfter << " micro second\n";
        cout << " - Avg Probe (After): " << avgProbeAfter << "\n\n";
    }
}


int main()
{
    createReport();
    return 0;
}