#include <iostream>
#include <string>

using namespace std;

template <typename K, typename V>
class MyNode
{
public:
	MyNode(const K &key, const V &value) :
		key(key), value(value), next(NULL)
	{
	}

	K getKey() const
	{
		return key;
	}

	V getValue() const
	{
		return value;
	}

	void setValue(V value)
	{
		value = value;
	}

	MyNode *getNext() const
	{
		return next;
	}

	void setNext(MyNode *next)
	{
		next = next;
	}

private:
	K key;
	V value;
	MyNode *next;
	MyNode(const MyNode &);
	MyNode & operator=(const MyNode &);
};

template <typename K, typename V, size_t tableSize, typename F = MyKey<K, tableSize> >
class MyHash
{
public:
	MyHash() :
		table(),
		hashFunc()
	{
	}

	~MyHash()
	{
		for (size_t i = 0; i < tableSize; ++i) {
			MyNode<K, V> *entry = table[i];

			while (entry != NULL) {
				MyNode<K, V> *prev = entry;
				entry = entry->getNext();
				delete prev;
			}

			table[i] = NULL;
		}
	}

	string retrieve(const K &key, V &value)
	{
		string none = "No result found";
		unsigned long hashValue = hashFunc(key);
		MyNode<K, V> *entry = table[hashValue];

		while (entry != NULL) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return value;
			}

			entry = entry->getNext();
		}

		return none;
	}

	void insert(const K &key, const V &value)
	{
		unsigned long hashValue = hashFunc(key);
		MyNode<K, V> *prev = NULL;
		MyNode<K, V> *entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new MyNode<K, V>(key, value);

			if (prev == NULL) {
				table[hashValue] = entry;
			}
			else {
				prev->setNext(entry);
			}

		}
		else {
			entry->setValue(value);
		}
	}

private:
	MyHash(const MyHash & other);
	const MyHash & operator=(const MyHash & other);
	MyNode<K, V> *table[tableSize];
	F hashFunc;
};

struct MyKey {
long operator()(const string& k) const
{
		return k.length() % 100; // modding the string length as you suggested. This was where I was messing up, thank you
} 

};

int main()
{
	MyHash<string, string, 10, MyKey> hmap;
	hmap.insert("Joe", "402555555"); 

	string value;
	string result = hmap.retrieve("Joe", value);
	cout << result << endl;

	system("pause");

	return 0;
}
