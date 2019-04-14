// #ifndef HashNode_hpp
// #define HashNode_hpp

#include <stdio.h>
#include <shared_mutex>
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
				next = nullptr;
			}

			//getters and setters 
			const int& getKey() const
			{
				return key;
			}
			// const std::string& getValue() const
			const T& getValue() const
			{
				return value; 
			}
			// void setValue(std::string value)
			void setValue(T value)
			{
				this->value = value;
			}
	};
	class HashCage
	{
		private:
			HashNode* head; 
	}
}

HashNode<int> ourhash;
int main()
{
	// HashNode<int> *ourhash = new HashNode<int>;
	// ourhash->setValue(4);
	// ourhash->getValue();
}
// #endif /* HashNode_hpp */
