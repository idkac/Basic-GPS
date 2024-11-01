#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class HashMap
{
    public:
        HashMap() : m_maxLoad(0.75), bucketSize(10), numItems(0)
        {
            m_buckets = new vector<valueHolder>[10];
            updateCurLoad();
        }; // constructor

        HashMap(double maxLoad) : m_maxLoad(maxLoad), bucketSize(10), numItems(0)
        {
            m_buckets = new vector<valueHolder>[10];
            updateCurLoad();
        };
        ~HashMap()
        {
            delete[] m_buckets;
        }; // destructor; deletes all of the items in the hashmap
              //
        int size() const { return numItems; }; // return the number of associations in the hashmap

        // The insert method associates one item (key) with another (value).
        // If no association currently exists with that key, this method inserts
        // a new association into the hashmap with that key/value pair. If there is
        // already an association with that key in the hashmap, then the item
        // associated with that key is replaced by the second parameter (value).
        // Thus, the hashmap must contain no duplicate keys.
        void insert(const std::string& key, const T& value)
        {
            bool hasAdded = false;
            size_t h = std::hash<std::string> ()(key); //hash string
            size_t tempvalue = bucketSize;
            size_t position = h % tempvalue; //figure out position
            if (m_buckets[position].size() == 0) //if the position doesnt have item, then we insert
            {
                numItems++;
                m_buckets[position].push_back(valueHolder(key, value));
                hasAdded = true;
            }
            else //if the bucket has items, then find the item associated and we change the value
            {
                for (valueHolder temp : m_buckets[position])
                    if (temp.getKey() == key)
                    {
                        temp.setValue(value);
                        hasAdded = true;
                    }
            }

            if (!hasAdded)
            { //case where there is a bunch of items but none of them have the same key, in which case we add teh item
                numItems++;
                m_buckets[position].push_back(valueHolder(key, value));
            }
            updateCurLoad(); //update load
            if (m_curLoad > m_maxLoad)
            {
                reallocate(); //checks if we need to rehash to keep load factor below maxload
            }
        };

        // Defines the bracket operator for HashMap, so you can use your map like this:
        // your_map["david"] = 2.99;
        // If the key does not exist in the hashmap, this will create a new entry in
        // the hashmap and map it to the default value of type T (0 for builtin types).
        // It returns a reference to the newly created value in the map.
        T& operator[](const std::string& key)
        {
               T* result = find(key);
               if (result != nullptr)
                   return *result;
               insert(key, T());
               return *find(key);
        }
        // If no association exists with the given key, return nullptr; otherwise,
        // return a pointer to the value associated with that key. This pointer can be
        // used to examine that value within the map.
        const T* find(const std::string& key) const
        {
            size_t h = std::hash<std::string> ()(key);
            size_t tempvalue = bucketSize;
            size_t position = h % tempvalue;
            if (m_buckets[position].size() == 0)
                return nullptr;
            else
                for (typename vector<valueHolder>::iterator i = m_buckets[position].begin(); i < m_buckets[position].end(); i++)
                    if ((*i).getKey () == key)
                        return (*i).getValueReference();

            return nullptr;
        }
        // If no association exists with the given key, return nullptr; otherwise,
        // return a pointer to the value associated with that key. This pointer can be
        // used to examine that value or modify it directly within the map.
        T* find(const std::string& key) {
            const auto& hm = *this;
            return const_cast<T*>(hm.find(key));
        }
    private:
        struct valueHolder
        {
            string key;
            T value;
            valueHolder(const string& k, const T& value) : key(k), value(value) {} ;
            void setKey(string k) { key = k; };
            void setValue(T v) { value = v; };
            string getKey() const { return key; };
            T getValue() { return *value; };
            T* getValueReference() { return &value; };
        };

        void updateCurLoad() { m_curLoad = numItems / bucketSize; };
        double m_curLoad;
        double m_maxLoad;
        vector<valueHolder>* m_buckets;
        double bucketSize;
        double numItems;

        void reallocate()
        {
            size_t newBucketSize = bucketSize * 2; //create new bucket with double size
            vector<valueHolder>* newBuckets = new vector<valueHolder>[newBucketSize];

            for (size_t i = 0; i < bucketSize; ++i) { //inset all items
                for (const auto& item : m_buckets[i]) {
                    size_t h = std::hash<std::string>()(item.getKey()) % newBucketSize;
                    newBuckets[h].push_back(item);
                }
            }

            delete[] m_buckets; //delete original bucket and add new bucket
            m_buckets = newBuckets;
            bucketSize = newBucketSize;
            updateCurLoad();
        }
};

#endif // HASHMAP_H_
