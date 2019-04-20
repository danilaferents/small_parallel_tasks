// #ifndef HashNode_hpp
// #define HashNode_hpp

#include <iostream>
#include <shared_mutex>
#include <mutex>
#include <functional>
#include <string>
constexpr size_t HASH_SIZE = 1031;
//Multithreaded data structes library
namespace MTDS
{
	template <typename T>
	class HashNode
	{
		private:
			int key; //hash key
			// std::string value; //hash value associated with hash key
			T value; //hash value associated with hash key
			HashNode *next; //pointer to the next 
		public:
			std::mutex _mutex;
			//constructors 
			HashNode() : next(nullptr) {}
			// HashNode(int key, std::string value) : next(nullptr), key(key), value(value) {}
			HashNode(int key, T value) : next(nullptr), key(key), value(value) {}

			//destructor
			~HashNode()
			{
				delete next;
				next = nullptr;
			}

			//getters 
			const int& getKey() 
			{
				return key;
			}
			// const std::string& getValue() const
			T& getValue() 
			{
				return value; 
			}
			HashNode* getNext() 
			{
				return next;
			}
			//setters
			// void setValue(std::string value)
			void setValue(T value)
			{
				this->value = value;
			}
			void setNext(HashNode<T> *next)
			{
				this->next = next;
			}
	};

	template <typename T>
	class HashCage
	{
		private:
			HashNode<T>* head; 
			mutable std::shared_timed_mutex _mutex;
		public:

			//destructor
			~HashCage()
			{
				std::unique_lock <std::shared_timed_mutex> lock(_mutex);
				HashNode<T>* next = head;
				HashNode<T>* current = nullptr;
				while (next != nullptr)
				{
					current = next;
					next = next->getNext();
					delete current;
				}
				head = nullptr;
			}

			//constructor
			HashCage() : head(nullptr) {}

			//shared_lock is used because of superioir of read over write
			void findKeyValue(const int& key, T& value, int& result)
			{
				std::shared_lock <std::shared_timed_mutex> _lock(_mutex);
				HashNode<T>* current = head;
				while (current != nullptr)
				{
					if (current->getKey() == key)
					{
						value = current -> getValue();
						result = 1;
						return;
					}
					current = current->getNext();
				}
				result =0;
				value = 0;
			}
			//задать вопрос про bool
			void insertValue(const int& key, const T& value)
			{
				std::unique_lock<std::shared_timed_mutex> _lock(_mutex);
				HashNode<T>* current = head;
				HashNode<T>* beforeCurrent = nullptr;
				while (current != nullptr && current->getKey() != key)
				{
					beforeCurrent = current;
					current = current->getNext();
				}
				if (current == nullptr) 
				{
					if (head != nullptr)
					{
						beforeCurrent->setNext(new HashNode<T>(key, value));
					} else {
						head=new HashNode<T>(key,value);
					}
				}
				// else {
				// 	current->setValue(value);
				// }
			}

			void deleteValue(const int&key)
			{
				//we can unlock unique_lock if we need
				std::unique_lock<std::shared_timed_mutex> _lock(_mutex);
				HashNode<T>* current = head;
				HashNode<T>* beforeCurrent = nullptr;
				while (current != nullptr &&  current->getKey() != key)
				{
					current = current->getNext();
					beforeCurrent = current;
				}
				if (current != nullptr)
				{
					if (current == head)
					{
						 head = current->getNext();
					}
					else 
					{ 
						beforeCurrent->setNext(current->getNext());
					}
					delete current;
				} 

			}
			void print()
			{
				HashNode<T>* current = head;
				while (current != nullptr)
				{
					std::cout<<current->getKey()<<" "<<current->getValue()<<std::endl;
					current = current->getNext();
				}
			}
			// void deleteCage()
			// {
			// 	std::unique_lock <std::shared_mutex> lock(_mutex);
			// 	HashNode* next = hea];
			// 	HashNode* current = nullptr;
			// 	while (next != nullptr)
			// 	{
			// 		current = next;
			// 		next = next->next;
			// 		delete current;
			// 	}
			// 	head = nullptr;
			// }
	};
	template <typename T>
	class HashTable
	{
		private: 
			const int hashSize;
			std::hash<int> hashFunction;
			HashCage<T> * hashTable;
		void countHashFn(size_t& hashNum,const int& key) 
		{
			hashNum = hashFunction(key) % hashSize;
		}
		public:

			//constructor
			HashTable(size_t _hashSize = HASH_SIZE) : hashSize(_hashSize)
			{
				hashTable = new HashCage<int>[hashSize];
			}

			//destructor
			~HashTable()
			{
				delete [] hashTable;
			}

			//we do not have copy and move constructors yet
			HashTable (const HashTable&) = delete;
            HashTable (HashTable&&) = delete;
            HashTable& operator=(const HashTable&) = delete;  
            HashTable& operator=(HashTable&&) = delete;

			void find(const int& key,T& value, int& result)
			{
				size_t hashNum;
				countHashFn(hashNum, key);
				hashTable[hashNum].findKeyValue(key, value, result);
			}
			void insert(const int& key, const T& value)
			{
				size_t hashNum;
				countHashFn(hashNum, key);
				hashTable[hashNum].insertValue(key, value);
			}
			void deleteValue(const int& key)
			{	
				size_t hashNum;
				countHashFn(hashNum, key);
				hashTable[hashNum].deleteValue(key);
			}
			void Print()
			{
				for (int i = 0; i < hashSize; ++i)
				{
					hashTable[i].print();
				}
			}
	};
}

// MTDS::HashNode<int> ourhash;
