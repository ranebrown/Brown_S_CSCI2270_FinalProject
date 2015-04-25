/* Project: cppWebSearch
 * File: cppWebSearch.h
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#ifndef cppWebSearch_H 
#define cppWebSearch_H

#include <iostream>
#include <queue>

 struct WordStruct {
 	std::string word;
 	std::string url;
 	int count;
 	bool hasValue;
 	WordStruct *next;
 };

class HashTable {
	public:
		HashTable();
		~HashTable();
		void Insert(std::string in_word, std::string url);
		void Find(std::string in_word);
		void Delete(std::string in_word);
		void Print();
	protected:
	private:
		int HashSum(std::string word);
		WordStruct *baseArray;
		int tableSize;
};

class WebSearch {
	public:
		WebSearch();
		virtual ~WebSearch();
		void EnqueueSite(std::string url);
		void BuildQueue(std::string url, int depth);
		void PrintHTML(std::string url);
		bool IsUnique(std::string url); // checks if url is already in queue
		void PrintURLs();
		void StoreWords();
		void PrintWords();
	protected:

	private:
		std::queue<std::string> urlList; // queue to store list of urls up to specified depth
		HashTable hTable; // hash table used to store all words from html code of each site
};

inline void DisplayMenu() {
	using namespace std;
	cout << "======Main Menu======" << endl;
	cout << "1. Initialize cppWebSearch" << endl;
	cout << "2. Search for a word" << endl;
	cout << "3. Print HTML code" << endl;
	cout << "4. Print saved URLs" << endl;
	cout << "5. Clear saved data" << endl;
	cout << "6. Quit" << endl;
}

#endif // cppWebSearch_H 
