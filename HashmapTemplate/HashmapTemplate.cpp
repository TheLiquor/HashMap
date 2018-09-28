#include <iostream>

using namespace std;

template <typename K, typename V>
class HashNode
{
public:
	HashNode(const K &key, const V &value) :
		_key(key), _value(value), _next(NULL)
	{
	}

	K getKey() const
	{
		return _key;
	}

	V getValue() const
	{
		return _value;
	}

	void setValue(V value)
	{
		_value = value;
	}

	HashNode *getNext() const
	{
		return _next;
	}

	void setNext(HashNode *next)
	{
		_next = next;
	}

private:
	// key-value pair
	K _key;
	V _value;
	// next bucket with the same key
	HashNode *_next;
	// disallow copy and assignment
	HashNode(const HashNode &);
	HashNode & operator=(const HashNode &);
};

template <typename K, typename V, size_t tableSize, typename F = KeyHash<K, tableSize> >
class HashMap
{
public:
	HashMap() :
		table(),
		hashFunc()
	{
	}

	~HashMap()
	{
		// destroy all buckets one by one
		for (size_t i = 0; i < tableSize; ++i) {
			HashNode<K, V> *entry = table[i];

			while (entry != NULL) {
				HashNode<K, V> *prev = entry;
				entry = entry->getNext();
				delete prev;
			}

			table[i] = NULL;
		}
	}

	bool get(const K &key, V &value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V> *entry = table[hashValue];

		while (entry != NULL) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return true;
			}

			entry = entry->getNext();
		}

		return false;
	}

	void put(const K &key, const V &value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V> *prev = NULL;
		HashNode<K, V> *entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new HashNode<K, V>(key, value);

			if (prev == NULL) {
				// insert as first bucket
				table[hashValue] = entry;

			}
			else {
				prev->setNext(entry);
			}

		}
		else {
			// just update the value
			entry->setValue(value);
		}
	}

	void remove(const K &key)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V> *prev = NULL;
		HashNode<K, V> *entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			// key not found
			return;

		}
		else {
			if (prev == NULL) {
				// remove first bucket of the list
				table[hashValue] = entry->getNext();

			}
			else {
				prev->setNext(entry->getNext());
			}

			delete entry;
		}
	}

private:
	HashMap(const HashMap & other);
	const HashMap & operator=(const HashMap & other);
	// hash table
	HashNode<K, V> *table[tableSize];
	F hashFunc;
};

struct MyKeyHash {
	unsigned long operator()(const int& k) const
	{
		return k % 10;
	}
};

int main()
{
	HashMap<int, string, 10, MyKeyHash> hmap;
	hmap.put(1, "1");
	hmap.put(2, "2");
	hmap.put(3, "3");

	string value;
	bool result = hmap.get(2, value);
	cout << result << endl;


	result = hmap.get(3, value);
	cout << result << endl;


	hmap.remove(3);
	result = hmap.get(3, value);
	cout << result << endl;

	system("pause");

	return 0;
}
