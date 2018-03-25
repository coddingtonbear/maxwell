/* 
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   https://github.com/alessandro1105
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Implementation of a HashMap data structure.
|| | This version is heavily based upon a suggestion from Alessandro1105
|| | Thank you for your contribution!
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see LICENSE.
||
*/


/*
	WARNING!!!!!!!!!

	Header file: 	HashMap.h
	Cpp File:		HashMap_Impl.h

	La suddivisione è stata così imposta per aggirare il problema dei template e allo stesso
	tempo mantenere la suddivisione tra Header e Implementazione.

*/

#ifndef HASHMAP_H
#define HASHMAP_H


//---HASH TYPE---

//class template
template<typename hash, typename map>

//class HashType
class HashType {

	public:

		//--costruttori
		HashType();
		HashType(hash code, map value);
		~HashType(); //distruttore

		void reset();
		
		hash getHash();

		void setHash(hash code);

		map getValue();

		void setValue(map value);

		//void operator()(hash code, map value);


	private:
		
		hash hashCode;
		map mappedValue;
};



//---HASH NODE---

//class template
template<typename hash, typename map>

//class HashNode
class HashNode {

	public:

		HashNode(hash code, map value);

		~HashNode();

		HashType<hash, map> *getHashType();

		HashNode<hash, map> *getPrevius();

		HashNode<hash, map> *getNext();

		void setPrevius(HashNode<hash, map> *previus);

		void setNext(HashNode<hash, map> *next);


	private:

		HashType<hash, map> *hashType;
		HashNode *previus;
		HashNode *next;
};



//---HASH MAP---
//Classe principale

//class template
template<typename hash, typename map>

//class HashMap
class HashMap {

	public:

		HashMap();
		~HashMap();

		void put(hash key, map value);

		bool containsKey(hash key);

		map valueFor(hash key);

		map valueAt(int i);

		map value();

		hash keyFor(map value);

		hash keyAt(int i);

		hash key();

		void remove(hash key);

		void remove();

		unsigned int count();

		bool moveToFirst();

		bool moveToLast();

		bool moveToNext();

		bool moveToPrev();	


	private:

		HashNode<hash, map> *hashPairForKey(hash key);

		void remove(HashNode<hash, map> *pointer);

		HashNode<hash, map> *start;
		HashNode<hash, map> *finish;
		HashNode<hash, map> *position;
		int size;
};

//incluso per workaround problema template
#include "HashMap_Impl.h"

#endif // HASHMAP_H