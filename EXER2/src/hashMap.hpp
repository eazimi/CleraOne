#ifndef HASHMAP_H
#define HASHMAP_H

#include <memory>
#include <functional>
#include "hashBucket.hpp"

constexpr int HASH_DEF_SIZE = 997; // pick a prime number to cause better distribution of values in buckets

// this class represent the hash table.
// the "HASH_DEF_SIZE" will be used in case the hash size is not provided.
// std::hash is to provide the hash function.
// hash table is an array of HashBuckets.
// a seperate lock is dedicated to each hash bucket, hence in case of multithreading, multiple threads can write
// simultaneously in different buckets in the hash map.
template <typename K, typename V>
class HashMap
{
private:
    const int hashSize;
    unique_ptr<HashBucket<K, V>[]> hashTable;

public:
    explicit HashMap(int hashSize = HASH_DEF_SIZE) : hashSize(hashSize)
    {
        // using container based data structures are not allowed by the problem definition
        hashTable = make_unique<HashBucket<K, V>[]>(hashSize);
    }

    // no copy, no move
    HashMap(HashMap const &) = delete;
    HashMap(HashMap &&) = delete;
    HashMap &operator=(HashMap const &) = delete;
    HashMap &operator=(HashMap &&) = delete;

    bool find(K const &key, V &value) const;
    void insert(K const &key, V const &value);
    void clear();
    void erase(K const &key);
};

// this function finds an entry in the hash map matching the key.
// if key is found, the corresponding value is copied into the parameter "value" and function returns true,
// otherwise it returns false
template <typename K, typename V>
bool HashMap<K, V>::find(K const &key, V &value) const
{
    auto hashValue = hash<K>{}(key) % hashSize;
    return hashTable[hashValue].find(key, value);
}

// insert into hash map. if key already exists, update the value, else insert a new node in the bucket
template <typename K, typename V>
void HashMap<K, V>::insert(const K &key, const V &value)
{
    auto hashValue = hash<K>{}(key) % hashSize;
    hashTable[hashValue].insert(key, value);
}

// dispose the hasp map
template <typename K, typename V>
void HashMap<K, V>::clear()
{
    for (auto i = 0; i < hashSize; i++)
        (hashTable[i]).clear();
}

// removes the element in the hash bucket with a 'key' equivalant to key
template <typename K, typename V>
void HashMap<K, V>::erase(K const &key)
{
    auto hashValue = hash<K>{}(key) % hashSize;
    hashTable[hashValue].erase(key);
}

#endif