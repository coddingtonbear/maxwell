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


//---HASH TYPE---
template<typename hash, typename map>
HashType<hash, map>::HashType() { 
	reset();
}


template<typename hash, typename map>
HashType<hash, map>::HashType(hash code, map value): hashCode(code), mappedValue(value) {}


template<typename hash, typename map>
HashType<hash, map>::~HashType() {};


template<typename hash, typename map>
void HashType<hash, map>::reset() {
	hashCode = 0;
	mappedValue = 0;
}

template<typename hash, typename map>
hash HashType<hash, map>::getHash() {
	return hashCode;
}

template<typename hash, typename map>
void HashType<hash, map>::setHash(hash code) {
	hashCode = code;
}

template<typename hash, typename map>
map HashType<hash, map>::getValue() {
	return mappedValue;
}

template<typename hash, typename map>
void HashType<hash, map>::setValue(map value) {
	mappedValue = value;
}

// template<typename hash, typename map>
// HashType<hash, map>& HashType<hash, map>::operator()(hash code, map value) {
// 	setHash(code);
// 	setValue(value);
// }



//---HASH NODE---
template<typename hash, typename map>
HashNode<hash, map>::HashNode(hash code, map value) {
	hashType = new HashType<hash, map>(code, value);
	previus = 0;
	next = 0;
}


template<typename hash, typename map>
HashNode<hash, map>::~HashNode() {
	delete hashType;
}


template<typename hash, typename map>
HashType<hash, map> *HashNode<hash, map>::getHashType() {
	return hashType;
}


template<typename hash, typename map>
HashNode<hash, map> *HashNode<hash, map>::getPrevius() {
	return previus;
}


template<typename hash, typename map>
HashNode<hash, map> *HashNode<hash, map>::getNext() {
	return next;
}


template<typename hash, typename map>
void HashNode<hash, map>::setPrevius(HashNode<hash, map> *previus) {
	this->previus = previus;
}


template<typename hash, typename map>
void HashNode<hash, map>::setNext(HashNode<hash, map> *next) {
	this->next = next;
}


//---HASH MAP---

//---public members---
template<typename hash, typename map>
HashMap<hash, map>::HashMap() {  
	start = 0;
	finish = 0;
	position = 0; 
	size = 0;
}


template<typename hash, typename map>
HashMap<hash, map>::~HashMap(){

	if (moveToFirst()) {

  		HashNode<hash, map> * next = position;
  		
  		while (position) {
    		next = position->getNext();
    		delete position;
    		position = next;
  		}
	}
}


template<typename hash, typename map>
void HashMap<hash, map>::put(hash key, map value) { 

	if (start == 0) {
  		start = finish = new HashNode<hash, map>(key, value);
	
	} else {
  		if (hashPairForKey(key)!=0) {
    		remove(hashPairForKey(key));
  		}
  
  		HashNode<hash, map> * temp = new HashNode<hash, map>(key, value);
  		finish->setNext(temp);
  		temp->setPrevius(finish);
  		finish = temp;
	}

	size++;
}


template<typename hash, typename map>
bool HashMap<hash, map>::containsKey(hash key) {
	return hashPairForKey(key) != 0;
}


template<typename hash, typename map>
map HashMap<hash, map>::valueFor(hash key) {
	HashNode<hash, map> *pointer = hashPairForKey(key);

	if (pointer != 0) {
  		return pointer->getHashType()->getValue();
	
	}
}


template<typename hash, typename map>
map HashMap<hash, map>::valueAt(int i) {
	moveToFirst();

	int iter = 0;
	
	do {
  		if (iter == i) {
    		return position->getHashType()->getValue();
  		}

  		iter++;
	} while (moveToNext());
}


template<typename hash, typename map>
map HashMap<hash, map>::value() {
	if (position != 0) {
  		return position->getHashType()->getValue();
	}
}


template<typename hash, typename map>
hash HashMap<hash, map>::keyFor(map value) {
	moveToFirst();

	do {
  		if (position->getHashType()->getValue() == value) {
    		return position->getHashType()->getHash();
  		}
	} while (moveToNext());
}


template<typename hash, typename map>
hash HashMap<hash, map>::keyAt(int i) {
	moveToFirst();
	
	int iter = 0;
	
	do {
  		if (iter == i) {
    		return position->getHashType()->getHash();
 		}
  		
  		iter++;
	} while (moveToNext());
}


template<typename hash, typename map>
hash HashMap<hash, map>::key() {
	if (position != 0) {
  		return position->getHashType()->getHash();
	}
}


template<typename hash, typename map>
void HashMap<hash, map>::remove(hash key) {
	HashNode<hash, map> * pointer = hashPairForKey(key);

	if (pointer != 0) {
  		remove(pointer);
	}
}


template<typename hash, typename map>
void HashMap<hash, map>::remove() {
	if (position != 0) {
  		if (size == 1) {          
    		remove(position);
    		position = 0;
  	
  		} else if (position == start) {
      		remove(position);
      		position = start;

		} else {
		    remove(position);
		    position = position->getPrevius();
 		}
	}
}


template<typename hash, typename map>
unsigned int HashMap<hash, map>::count() {
	return size;
}


template<typename hash, typename map>
bool HashMap<hash, map>::moveToFirst() {
	if (start != 0) {
  		position = start;
  		return true;

	} else {
  		return false;
	}
}


template<typename hash, typename map>
bool HashMap<hash, map>::moveToLast() {
	if (finish != 0) {
  		position = finish;
  		return true;

	} else {
  		return false;
	}
}


template<typename hash, typename map>
bool HashMap<hash, map>::moveToNext() {
	if (position->getNext() != 0) {
  		position = position->getNext();
  		return true;
	
	} else {
  		return false;
	}
}


template<typename hash, typename map>
bool HashMap<hash, map>::moveToPrev() {
	if (position->getPrevius() != 0) {
  		position = position->getPrevius();
  		return true;
	
	} else {
  		return false;
	}
}


//---private members---

template<typename hash, typename map>
HashNode<hash, map> *HashMap<hash, map>::hashPairForKey(hash key) {
	
	for(HashNode<hash, map> * pointer = start; pointer != 0; pointer = pointer->getNext()) {
  		HashType<hash, map> * hashType = pointer->getHashType();
  		
  		if (key == hashType->getHash()) {
    		return pointer;
  		}
	}
	
	return 0;
}


template<typename hash, typename map>
void HashMap<hash, map>::remove(HashNode<hash, map> * pointer) {
	if (pointer == 0) return;

	if (size == 1) {
  		start = finish = 0;

	} else if (pointer == start) {
    	start = start->getNext();
    	start->setPrevius(0);
  
  	} else if (pointer == finish) {
    	finish = finish->getPrevius();
    	finish->setNext(0);
  
  	} else {
    	pointer->getPrevius()->setNext(pointer->getNext());
    	pointer->getNext()->setPrevius(pointer->getPrevius());
  	}

	size--;
	delete pointer;
}
