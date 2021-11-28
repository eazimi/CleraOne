#ifndef HASHBUCKET_H
#define HASHBUCKET_H

#include <shared_mutex>
#include <mutex>
#include "hashNode.hpp"

using namespace std;

// HashBucket class represents a hash bucket. 
// it is implemented as a singly linked list.   
template <typename K, typename V>
class HashBucket
{
    private:
        HashNode<K, V> *head;
        mutable shared_timed_mutex mu; // The mutex for the hash bucket

    public:
        explicit HashBucket() : head(nullptr) {}
        ~HashBucket();                             // clear the has bucket
        bool find(K const &key, V &value) const;   // finds the element in the hash bucket with a 'key' equivalent to key
        void insert(K const &key, V const &value); // inserts an element into the hash bucket.
                                                   // If key already exists, update the value,
                                                   // else insert a new node in the bucket with the <key, value> pair.
        void clear();                              // erases all elements from hash bucket
        void erase(K const &key);                  // removes the element in the hash bucket with a 'key' equivalant to key
};

template <typename K, typename V>
HashBucket<K, V>::~HashBucket()
{
    clear();
}

template <typename K, typename V>
void HashBucket<K, V>::clear()
{
    // exclusive write to enable single write in the bucket
    unique_lock<shared_timed_mutex> lock(mu);
    auto p = head;
    HashNode<K, V> * prev = nullptr;
    while (p != nullptr)
    {
        prev = p;
        p = p->next;
        delete prev;
        prev = nullptr;
    }
    head = nullptr;
}

template <typename K, typename V>
void HashBucket<K, V>::insert(K const &key, V const &value)
{
    // exclusive lock to enable single write in the bucket
    unique_lock<shared_timed_mutex> lock(mu);
    auto p = head;
    HashNode<K, V> *prev = nullptr;
    while ((p != nullptr) && (p->getKey() != key))
    {
        prev = p;
        p = p->next;
    }

    if (p == nullptr) // new element
    {
        if (head == nullptr) // it's the first element
        {
            head = new HashNode<K, V>(key, value);
            return;
        }
        prev->next = new HashNode<K, V>(key, value); // add new element to the tail of bucket
    }
    else
        p->setValue(value); // update the value
}

// if key is found, the corresponding value is copied into the parameter "value" and function returns true,
// if key is not found, function returns false.
template <typename K, typename V>
bool HashBucket<K, V>::find(K const &key, V &value) const
{
    // A shared mutex is used to enable mutiple concurrent reads
    std::shared_lock<std::shared_timed_mutex> lock(mu);
    auto p = head;
    while (p != nullptr)
    {
        if (p->getKey() == key)
        {
            value = p->getValue();
            return true;
        }
        p = p->next;
    }
    return false;
}

template <typename K, typename V>
void HashBucket<K, V>::erase(K const &key)
{
    //Exclusive lock to enable single write in the bucket
    unique_lock<shared_timed_mutex> lock(mu);
    auto p = head;
    HashNode<K, V> *prev = nullptr;
    while ((p != nullptr) && (p->getKey() != key))
    {
        prev = p;
        p = p->next;
    }

    if (p == nullptr) // key not found
        return;
    
    // remove the node from the bucket
    if (p == head)
        head = head->next;
    else
        prev->next = p->next;
    delete p; //Free up the memory
}

#endif