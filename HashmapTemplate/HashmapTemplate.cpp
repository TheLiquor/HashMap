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

	string get(const K &key, V &value)
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

	void put(const K &key, const V &value)
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

	void remove(const K &key)
	{
		unsigned long hashValue = hashFunc(key);
		MyNode<K, V> *prev = NULL;
		MyNode<K, V> *entry = table[hashValue];

		while (entry != NULL && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			return;

		}
		else {
			if (prev == NULL) {
				table[hashValue] = entry->getNext();

			}
			else {
				prev->setNext(entry->getNext());
			}

			delete entry;
		}
	}

private:
	MyHash(const MyHash & other);
	const MyHash & operator=(const MyHash & other);
	MyNode<K, V> *table[tableSize];
	F hashFunc;
};

struct MyKey {
long operator()(const int& k) const
{
		return k % 100;
} 

};

int main()
{
	MyHash<int, string, 10, MyKey> hmap;
	hmap.put(1, "Joe"); 
	//hmap.put(2, "Caleb");
	//hmap.put(3, "Darold");`

	string value;
	string result = hmap.get(1, value);
	cout << result << endl;


	//result = hmap.get(3, value);
	//cout << result << endl;


	//hmap.remove(3);
	//result = hmap.get(3, value);
	//cout << result << endl;

	system("pause");

	return 0;
}
