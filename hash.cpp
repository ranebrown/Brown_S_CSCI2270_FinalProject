#include "cppWebSearch.h"

/*
* Constructor to create base hash table
*/
HashTable::HashTable() {
	tableSize = 500;
	baseArray = new WordStruct[tableSize]; // array of structs to hold words

	// initialize parameters
	for(int i=0; i<tableSize; i++) {
		baseArray[i].hasValue = false;
		baseArray[i].next = nullptr;
	}
}

/*
* Destructor, frees all memory that was allocated in relation to hash table
*/
HashTable::~HashTable(){
	// delete all linked list word structs and all top url structs in vector
	for(int i=0; i<tableSize; i++) {
		if(baseArray[i].next != nullptr) {
		 	WordStruct *temp = baseArray[i].next;
		 	WordStruct *prev;
		 	while(temp->next != nullptr) {
		 		prev = temp;
		 		temp = temp->next;
		 		prev->wOccr.clear();
		 		delete prev;
			}
		}
	}
	// delete original array
	delete [] baseArray;
}

/*
* Calculates the hash table location for a processed word. If the word has already been found
* within a website the count for that word is incremented. If the word is found in a new website
* that website url is stored.
*/
void HashTable::Insert(std::string in_word, std::string url){
	int location = HashSum(in_word);

	// location has no values yet
	if(baseArray[location].hasValue == false) {
		baseArray[location].word = in_word;
		// TopURL struct stores each website and the number of occurences of a word in that site
		TopURL *cU = new TopURL;
		cU->count = 1;
		cU->url = url;
		baseArray[location].wOccr.push_back(cU);
		baseArray[location].hasValue = true;
	}

	// location already has at least one word stored
	else {
		WordStruct *temp = &baseArray[location];
		// if word already added increment count
		if(temp->word == in_word) {
			for(int i=0; i<(int)temp->wOccr.size(); i++) {
				// same word found within the same website
				if(temp->wOccr[i]->url == url) {
					temp->wOccr[i]->count++;
					return;
				}
			}

			// same word found within a different website
			TopURL *cU = new TopURL;
			cU->count = 1;
			cU->url = url;
			temp->wOccr.push_back(cU);
			//temp->count++;
			return;
		}

		// find next available location to insert word (no order)
		while(temp->next != nullptr) {
			temp = temp->next;
			// if word already added just increment count
			if(temp->word == in_word) {
				for(int i=0; i<(int)temp->wOccr.size(); i++) {
					// same word found within the same website
					if(temp->wOccr[i]->url == url) {
						temp->wOccr[i]->count++;
						return;
					}
				}

				// same word found within a different website
				TopURL *cU = new TopURL;
				cU->count = 1;
				cU->url = url;
				temp->wOccr.push_back(cU);
				//temp->count++;
				return;
			}
		}

		// create new struct and initialize parameters
		WordStruct *toInsert = new WordStruct;
		toInsert->word = in_word;
		TopURL *cU = new TopURL;
		cU->count = 1;
		cU->url = url;
		toInsert->wOccr.push_back(cU);
		toInsert->hasValue = true;
		toInsert->next = nullptr;
		temp->next = toInsert;
	}
}

/*
* Searches for the website that has the highest occurence of entered word
*/
void HashTable::Find(std::string in_word){
	int location = HashSum(in_word);
	if(baseArray[location].hasValue == false) {
		std::cout<<"Word not found\n";
		return;
	}
	if(baseArray[location].word == in_word) {
		int max = 0;
		std::string bestURL;
		WordStruct *temp = &baseArray[location];
		for(int i=0; i<(int)temp->wOccr.size(); i++) {
			if(temp->wOccr[i]->count > max) {
				max = temp->wOccr[i]->count;
				bestURL = temp->wOccr[i]->url;
			}
		}
		std::cout<<"Best website is: "<<bestURL<<"\n"<<in_word<<" count = "<< max << std::endl;
		return;
	}
	else {
		int max = 0;
		std::string bestURL;
		WordStruct *temp = &baseArray[location];
		while(temp->next != nullptr) {
			temp = temp->next;
			if(temp->word == in_word)
				break;
		}
		if(temp->word != in_word) {
			std::cout << "Word not found\n";
			return;
		}
		for(int i=0; i<(int)temp->wOccr.size(); i++) {
			if(temp->wOccr[i]->count > max) {
				max = temp->wOccr[i]->count;
				bestURL = temp->wOccr[i]->url;
			}
		}
		std::cout<<"Best website is: "<<bestURL<<"\n"<<in_word<<" count = "<< max << std::endl;
	}

}

/*
* Prints all words stored in the hash table
*/
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
				std::cout<<baseArray[i].word<<std::endl;
				if(baseArray[i].next != nullptr) {
					WordStruct *temp = baseArray[i].next;
					while(temp != nullptr) {
						std::cout<<temp->word<<std::endl;
						temp = temp->next;
					}
				}
			}
		}
	}
}

/* 
* Calculates the hash sum needed to acces correct element of array
*/
int HashTable::HashSum(std::string word){
	unsigned int location = 0;
	for(unsigned long i=0; i<word.length(); i++) {
		location += word[i]; // sum ascii values of all characters in string
	}
	location = location % tableSize;
	return location;
}

/*
* Clears all values stored in hash table
*/
void HashTable::Clear() {
	for(int i=0; i<tableSize; i++) {
		if(baseArray[i].next != nullptr) {
		 	WordStruct *temp = baseArray[i].next;
		 	WordStruct *prev;
		 	while(temp->next != nullptr) {
		 		prev = temp;
		 		temp = temp->next;
		 		prev->wOccr.clear();
		 		delete prev;
			}
		}
		baseArray[i].hasValue = false;
	}
}
