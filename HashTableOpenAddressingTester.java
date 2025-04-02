// Test class for Open addressing Quadratic Probing

// Must be in the same package where HashTableOpenAddressingQuadraticProbing is present or both in same folder

public class HashTableOpenAddressingTester {
    public static void main(String[] args) {
        // Create an instance of the hash table
        HashTableOpenAddressingQuadraticProbing<Integer, String> hashTable = new HashTableOpenAddressingQuadraticProbing<>();

        // Insert some key-value pairs
        hashTable.put(1, "One");
        hashTable.put(2, "Two");
        hashTable.put(3, "Three");

        // Retrieve and print values
        System.out.println("Value for key 1: " + hashTable.get(1));
        System.out.println("Value for key 2: " + hashTable.get(2));
        System.out.println("Value for key 3: " + hashTable.get(3));

        // Remove a key-value pair
        hashTable.remove(2);
        System.out.println("Value for key 2 after removal: " + hashTable.get(2));

        // Check if a key exists
        System.out.println("Contains key 1: " + hashTable.containsKey(1));
        System.out.println("Contains key 2: " + hashTable.containsKey(2));
    }
}