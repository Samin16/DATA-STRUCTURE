// Hash Table Open Addressing Quadratic Probing

// package DataStructure.HashTable;
// Here both (this file and tester) in the same folder and using the default package

class Element<S,T> {                      // Each Element for a Hash Table
    public int hashValue;                 // Hash for the element
    private S key;                        // Key for accessing an Element
    private T value;                      // Value for a specific Element
    public Element(S key,T value) {       // Initializing the Element
        this.key=key;
        this.value=value;
        hashValue=(key!=null)?key.hashCode():0;
    }

    @Override
    public int hashCode() {               // Generates a hash code for a key
        final int prime=31;
        int result=1;
        result=prime*result+((key==null)?0:key.hashCode());
        result=prime*result+((value==null)?0:value.hashCode());
        result=prime*result+hashValue;
        return result;
    }

    @Override
    public boolean equals(Object obj) {        //Overrides equals method to check whether obj is equal to this element or not 
        if(this==obj) {
            return true;
        }
        if(obj==null) {
            return false;
        }
        if(getClass()!=obj.getClass()) {
            return false;
        }
        Element other=(Element)obj;
        if(hashValue!=other.hashValue) {
            return false;
        }
        if(key==null) {
            if(other.key!=null) {
                return false;
            }
        } else if(!key.equals(other.key)) {
            return false;
        }
        if(value==null) {
            if(other.value!=null) {
                return false;
            }
        } else if(!value.equals(other.value)) {
            return false;
        }
        return true;
    }

    public S getKey() {                    // Getters and Setters
        return key;
    }
    public T getValue() {
        return value;
    }
    public void setKey(S key) {
        this.key = key;
    }
    public void setValue(T value) {
        this.value = value;
    }
}

public class HashTableOpenAddressingQuadraticProbing<S,T> {             // Class to implement all methods for Hash Table
    private static final int DEFAULT_CAPACITY=16;                  // Default capacity
    private static final double LOAD_FACTOR=0.75;                  // Load factor(By which factor number of elements in hash table can be spacified)
    private static final class DeletedMarker<S,T> extends Element<S,T> {        // Class to create a marker that will mark an position of Hash Table as Deleted
        private DeletedMarker() {
            super(null,null);
            this.hashValue=-1;
        }
        @Override public S getKey() { throw new UnsupportedOperationException(); }
        @Override public T getValue() { throw new UnsupportedOperationException(); }
        @Override public void setKey(S key) { throw new UnsupportedOperationException(); }
        @Override public void setValue(T value) { throw new UnsupportedOperationException(); }
    }

    private static final Element<?,?> DELETED=new DeletedMarker();       // An Element that has the characteristics of a deleted element
    private Element<S,T>[] table;                                     // Array to store the elements
    private int size;                                                 // Size of the table(array)
    private int capacity;                                             // Capacity of the table(array)
    private int threshold;                                            // Maximum Element that can be inserted in the hash table for a specific capacity
    private Element<S,T>[] createArray(int size) {             // Method to create a type safe array
        return (Element<S,T>[]) new Element<?,?>[size];
    }

    public HashTableOpenAddressingQuadraticProbing() {         // Initialization with DEFAULT_CAPACITY
        this(DEFAULT_CAPACITY);
    }

    public HashTableOpenAddressingQuadraticProbing(int initialCapacity) {      // Initialization for a specific capacity
        if(initialCapacity<=0) {
            throw new IllegalArgumentException("Initial capacity must be positive");
        }
        this.capacity=initialCapacity;
        this.size=0;
        this.threshold=(int)(capacity*LOAD_FACTOR);
        this.table=createArray(capacity);
    }

    private int nextPowerofTwo(int n) {       // Next power of two is need to always make the array size power of two
        int power=1;                          // which is must for quadratic function (x²+x)/2
        while(power<n) {
            power<<=1;
        }
        return power;
    }

    public int size() {                  // Returns number of elements in the Hash Table
        return size;
    }

    public boolean isEmpty() {           // Returns whether the Hash Table is empty or not
        return size==0;
    }

    public void clear() {                // Clears the Hash Table
        for(int i=0;i<capacity;i++) {
            table[i]=null;
        }
        size=0;
    }

    private int normalizeIndex(int hash) {      // Returns an index that in range of the hash table's capacity
        return (hash & 0x7FFFFFFF)%capacity;
    }

    private int probeOffset(int x) {        // Probing function for Quadratic Probing
        return ((x*x)+x)/2;
    }

    private void resizeTable() {            // Resizes the Hash Table with double capacity and places all the elements in the Hash Table with
        capacity*=2;                        // lower capacity in correct position in the new table 
        threshold=(int)(capacity*LOAD_FACTOR);
        Element<S,T>[] oldTable=table;
        table=createArray(capacity);
        size=0;
        for(Element<S,T> element:oldTable) {
            if(element!=null && element!=DELETED) {
                put(element.getKey(),element.getValue());
            }
        }
    }

    public T put(S key,T value) {               // Method to insert an Element in the Hash Table
        if(key==null) {
            throw new IllegalArgumentException("Key cannot be null");
        }
        if(size>=threshold) {                    // If size exceeds capacity then resizes the Hash Table
            resizeTable();
        }
        int hash=key.hashCode();                 // Hash code for the key
        int index=normalizeIndex(hash);          // Correct index in the Hash Table
        int i=1;                                 // Used to get the correct value to pass to the probe function
        int x=1;
        Element<S,T> existingElement=table[index];     // Element at current index
        int firstDeletedIndex=-1;                      // To get if any position contains a DELETED marker
        while(existingElement!=null) {                 // Iterate until finds a position to store the new element
            if(existingElement==DELETED) {             // If finds a Element with DELETED marker and it's the first such element store the index
                if(firstDeletedIndex==-1) {
                    firstDeletedIndex=index;
                }
            } else if(existingElement.getKey().equals(key)) {      // If finds that the key already contains a value then updates the value and returns the old value 
                T oldValue=existingElement.getValue();
                existingElement.setValue(value);
                return oldValue;
            }
            index=normalizeIndex(hash+probeOffset(x));       // Until a empty place is found it makes a new index offset to the previous indes using quadratic probing function
            existingElement=table[index];                    // Element at current index
            i++;                                             // Increments i to set x to get new index value through probing function
            x=i;
        }
        if(firstDeletedIndex!=-1) {               // If any index found with DELETED for the key then place the key there
            index=firstDeletedIndex;
        }
        table[index]=new Element<>(key,value);   // otherwise, create a new element at store it at the index where is no Element
        size++;                                  // and increase the size
        return null;
    }

    public T get(S key) {                   // Method to get the value for a given key
        if(key==null) {
            throw new IllegalArgumentException("Key cannot be null");
        }
        int hash=key.hashCode();            // Following the same probing technique as put method if any position in hash Table is found with the key
        int index=normalizeIndex(hash);     // returns the value , if key is not found then returns null
        int i=1,x=1;
        Element<S,T> existingElement=table[index];
        while(existingElement!=null) {
            if(existingElement!=DELETED && existingElement.getKey().equals(key)) {
                return existingElement.getValue();
            }
            index=normalizeIndex(hash+probeOffset(x));
            existingElement=table[index];
            i++;
            x=i;
        }
        return null;
    }

    public T remove(S key) {          // Method to remove an Element from Hash Table
        if(key==null) {
            throw new IllegalArgumentException("Key cannot be null");
        }
        int hash=key.hashCode();              // As before tries to find whether the key is in the Hash Table using Quadratic Probind
        int index=normalizeIndex(hash);       // if found marks the position as DELETED, decreases size and returns value for deleted element  
        int i=1,x=1;                          // Otherwise returns null
        Element<S,T> existingElement=table[index];
        while(existingElement!=null) {
            if(existingElement!=DELETED && existingElement.getKey().equals(key)) {
                T value=existingElement.getValue();
                table[index]=(Element<S,T>)DELETED;
                size--;
                return value;
            }
            index=normalizeIndex(hash+probeOffset(x));
            i++;
            x=i;
        }
        return null;
    }
    public boolean containsKey(S key) {           // Returns whether Hash Table contains the key or not
        return get(key)!=null;
    }
    public String toString() {                    // Represents the Hash Table in a nice way
        StringBuilder sb=new StringBuilder();
        sb.append("{");
        boolean first=true;
        for(Element<S,T> element:table) {
            if(element!=null && element!=DELETED) {
                if(!first) {
                    sb.append(", ");
                }
                sb.append(element.getKey()).append("=").append(element.getValue());
                first=false;
            }
        }
        sb.append("}");
        return sb.toString();
    }
}
