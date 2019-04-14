// #ifndef HashNode_hpp
// #define HashNode_hpp

#include <stdio.h>
#include <shared_mutex>
#include <mutex>
#include <string>
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
			const int& getKey() const
			{
				return key;
			}
			// const std::string& getValue() const
			const T& getValue() const
			{
				return value; 
			}
			const HashNode* getNext()
			{
				return next;
			}
			//setters
			// void setValue(std::string value)
			void setValue(T value)
			{
				this->value = value;
			}
	};

	template <typename T>
	class HashCage
	{
		private:
			HashNode<T>* head; 
			mutable std::shared_mutex _mutex;
		public:

			//destructor
			~HashCage()
			{
				std::unique_lock <std::shared_mutex> lock(_mutex);
				HashNode<int>* next = head;
				HashNode<int>* current = nullptr;
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
			bool findKeyValue(const int& key, T& value)
			{
				std::shared_lock <std::shared_mutex> _mutex;
				HashNode* curent = head;
				while (head != nullptr)
				{
					if (head->getValue == value)
					{

					}
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
}

MTDS::HashNode<int> ourhash;
int main()
{
	// HashNode<int> *ourhash = new HashNode<int>;
	// ourhash->setValue(4);
	// ourhash->getValue();
}
// #endif /* HashNode_hpp */
