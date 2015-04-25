#include "cppWebSearch.h"

HashTable::HashTable() {
	tableSize = 500;
	baseArray = new WordStruct[tableSize]; // array of structs to hold words

	// initialize parameters
	for(int i=0; i<tableSize; i++) {
		baseArray[i].hasValue = false;
		baseArray[i].next = nullptr;
	}
}

HashTable::~HashTable(){
	// delete linked list also
	delete [] baseArray;
}

void HashTable::Insert(std::string in_word, std::string url){
	int location = HashSum(in_word);

	// location has no values yet
	if(baseArray[location].hasValue == false) {
		baseArray[location].word = in_word;
		baseArray[location].url = url;
		baseArray[location].count = 1;
		baseArray[location].hasValue = true;
	}

	// location already has at least one word stored
	else {
		WordStruct *temp = &baseArray[location];
		// if word already added just increment count
		if(temp->word == in_word) {
			temp->count++;
			return;
		}

		// find next available location to insert word (no order)
		while(temp->next != nullptr) {
			temp = temp->next;
			// if word already added just increment count
			if(temp->word == in_word) {
				temp->count++;
				return;
			}
		}

		// create new struct and initialize parameters
		WordStruct *toInsert = new WordStruct;
		toInsert->word = in_word;
		toInsert->url = url;
		toInsert->count = 1;
		toInsert->hasValue = true;
		toInsert->next = nullptr;
		temp->next = toInsert;
	}
}

void HashTable::Find(std::string in_word){


}

void HashTable::Delete(std::string in_word){


}

void HashTable::Print(){
	int i;
	int empty = 0;
	for(i=0; i<tableSize; i++)
		if(baseArray[i].hasValue == false)
			empty++;
	if(empty == tableSize)
		std::cout<<"There are no stored words.\n";
	else {
		for(i=0; i<tableSize; i++) {
			if(baseArray[i].hasValue == true) {
				std::cout<<baseArray[i].word<<":"<<baseArray[i].url<<baseArray[i].count<<std::endl;
				if(baseArray[i].next != nullptr) {
					WordStruct *temp = baseArray[i].next;
					while(temp != nullptr) {
						std::cout<<temp->word<<":"<<temp->url<<temp->count<<std::endl;
						temp = temp->next;
					}
				}
			}
		}
	}
}

int HashTable::HashSum(std::string word){
	unsigned int location = 0;
	for(unsigned long i=0; i<word.length(); i++) {
		location += word[i]; // sum ascii values of all characters in string
	}
	location = location % tableSize;
	return location;
}
