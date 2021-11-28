#ifndef HASHNODE_HPP
#define HASHNODE_HPP

template <typename K, typename V>
class HashNode
{
private:
    K key;   // key
    V value; // the value corresponding to the key

public:
    explicit HashNode() : next(nullptr) {}
    explicit HashNode(K const &key, V const &value) : next(nullptr), key(key), value(value) {}
    ~HashNode()
    {
        next = nullptr;
    }
    inline const K &getKey() const { return key; }
    inline const V &getValue() const { return value; }
    inline void setValue(V const &value) { this->value = value; }

    HashNode *next;
};

#endif