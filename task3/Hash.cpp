// #ifndef HashNode_hpp
// #define HashNode_hpp

#include <iostream>
#include <shared_mutex>
#include <mutex>
#include <functional>
#include <string>
constexpr size_t HASH_SIZE = 1031;
//Multithreaded data structs library
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
			// mutable std::shared_timed_mutex _mutex;
			bool findKey(const int& key)
			{
				head->_mutex.lock();
				HashNode<T>* prev = head;
				HashNode<T>* curr = prev->getNext();
				if (curr != nullptr) curr->_mutex.lock();

				while (curr!=nullptr)
				{
					prev->_mutex.unlock();
					prev = curr;

					if (curr->getKey() == key)
					{
						curr->_mutex.unlock();
						return true;
					}
					curr = curr->getNext();
					if (curr != nullptr) curr->_mutex.lock();
				}		
				prev->_mutex.unlock();
				return false;
			}
		public:

			//destructor
			~HashCage()
			{
				// std::unique_lock <std::shared_timed_mutex> lock(_mutex);
				head->_mutex.lock();
				HashNode<T>* prev = head;
				HashNode<T>* curr = prev->getNext();
				if (curr != nullptr) curr->_mutex.lock();

				while (curr != nullptr)
				{
					prev->_mutex.unlock();
					delete prev;
					prev = curr;
					curr = curr->getNext();
					if (curr != nullptr) curr->_mutex.lock();
				}
				prev->_mutex.unlock();
				delete prev;
				head = nullptr;
			}

			//constructor
			HashCage() : head(nullptr) {}

			//shared_lock is used because of superioir of read over write
			// void findKeyValue(const int& key, int& value, bool& result)
			void findKeyValue(const int& key)
			{
				// std::shared_lock <std::shared_timed_mutex> _lock(_mutex);
				head->_mutex.lock();
				HashNode<T>* prev = head;
				if (prev->getKey() == key) 
				{
					// value = prev -> getValue();
					// result = true;
					prev->_mutex.unlock();
					// std::cout<<"result1: "<<result;
					return;
				}
				// std::cout<<"end";
				HashNode<T>* curr = prev->getNext();
				if (curr != nullptr) curr->_mutex.lock();

				while (curr!=nullptr)
				{
					prev->_mutex.unlock();
					prev = curr;
					if (curr->getKey() == key)
					{
						// value = curr -> getValue();
						// result = true;
						// std::cout<<"result2: "<<result;
						// std::cout<<"1 ";
						curr->_mutex.unlock();
						
						return;
					}
					curr = curr->getNext();
					if (curr != nullptr) curr->_mutex.lock();
				}		
				// std::cout<<"end";
				// result = false;
				// value = 0;
				// std::cout<<"0";
				prev->_mutex.unlock();
				// std::cout<<"result3: "<<result;
			}
			//задать вопрос про bool
			void insertValue(const int& key, const T& value)
			{
				head->_mutex.lock();
				HashNode<T>* prev = head;
				HashNode<T>* curr = prev->getNext();
				if (curr!=nullptr) curr->_mutex.lock();

				while (curr!=nullptr && curr->getKey() < key)
				{
					prev->_mutex.unlock();
					prev = curr;
					curr = curr->getNext();
					if (curr != nullptr) curr->_mutex.lock();
				}
				if (curr == nullptr)
				{
					auto newNode = new HashNode<T>(key, value);
					prev->setNext(newNode);
					prev->_mutex.unlock();
					return;	
				}
				else 
				{
					if (curr->getKey() == key)
					{
						curr->_mutex.unlock();
						prev->_mutex.unlock();
						return;
					} 
					else 
					{
						auto newNode = new HashNode<T>(key, value);
						newNode->setNext(curr);
						prev->setNext(newNode);
						curr->_mutex.unlock();
						prev->_mutex.unlock();
					}
					
				}
				
			}

			void deleteValue(const int&key)
			{
				//we can unlock unique_lock if we need
				// std::unique_lock<std::shared_timed_mutex> _lock(_mutex);
				if (!findKey(key)) return;

				head->_mutex.lock();
				HashNode<T>* prev = head;
				HashNode<T>* curr = prev->getNext();
				if (curr != nullptr) curr->_mutex.lock();

				while (curr != nullptr && curr->getKey() != key)
				{
					prev->_mutex.unlock();
					prev = curr;
					curr = curr->getNext();
					if (curr != nullptr) curr->_mutex.lock();
				}

				if (curr == head)
				{
				 	head = curr->getNext();
				} 
				else 
				{
					prev->setNext(curr->getNext());
				}
				prev->_mutex.unlock();
				if (curr != nullptr) curr->_mutex.unlock();
				delete curr;
			}
			void print()
			{
				head->_mutex.lock();
				HashNode<T>* prev = head;
				HashNode<T>* curr = prev->getNext();
				if (curr != nullptr) curr->_mutex.lock();
				while (curr!=nullptr)
				{
					prev->_mutex.unlock();
					prev = curr;
					if (prev->getKey() !=0) std::cout<<prev->getKey()<<" "<<prev->getValue()<<std::endl;
					curr = curr->getNext();
					if (curr != nullptr) curr->_mutex.lock();
				}
				prev->_mutex.unlock();
			}
			void setStartHead()
			{
				head = new HashNode<T>();
			}	
			int countSize()
			{
				int countsize = 0;
				HashNode<T>* curr = head;

				while (curr!=nullptr)
				{
					countsize+=1;
					curr = curr->getNext();
				}
				return countsize;
			}
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
				hashTable = new HashCage<T>[hashSize];
				for (int i = 0; i < hashSize; ++i)
				{
					hashTable[i].setStartHead();
				}
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

			// void find(const int& key, bool& result)
			void find(const int& key)
			{
				size_t hashNum;
				countHashFn(hashNum, key);
				hashTable[hashNum].findKeyValue(key);
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
			int countSize()
			{
				int countsize = 0;
				for (int i = 0; i < hashSize; ++i)
				{
					countsize+=hashTable[i].countSize();
				}
				return (countsize - hashSize);
			}
	};
}

// MTDS::HashNode<int> ourhash;
