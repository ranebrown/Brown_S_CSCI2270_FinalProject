/* Project: cppWebSearch
 * File: main.cpp
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#include "cppWebSearch.h"

int main(/*int argc, char *argv[]*/) {
	WebSearch *newSearch = new WebSearch;
	std::string url, sDepth, searchWord;
	int selection, depth;
	bool quit = false;

	// display menu and get user input
	while(!quit) {
		DisplayMenu();
		std::cin>>selection;
		std::cin.clear(); // clear flags and flush buffer
		std::cin.ignore(1000,'\n');
		switch (selection) {
			case 1: // Initialize base address and search depth
				std::cout<<"Enter a base website url\n FORMAT:  http://www.address\n";
				getline(std::cin, url);
				std::cout<<"Enter depth of search\n RANGE: 1-500\n";
				getline(std::cin, sDepth);
				depth = atoi(sDepth.c_str());
				if(depth < 1 || depth > 500) {
					std::cout<<"Invalid depth\n";
					break;
				}
				else {
					newSearch->BuildQueue(url, depth);	
				}
				break;
			case 2: // Search for a word
				std::cout<<"Function will display the website with highest occurence of entered word.\n";
				std::cout<<"Enter a word to search for:\n";
				getline(std::cin, searchWord);
				newSearch->FindWebsite(searchWord);
				break;
			case 3: // Print HTML
				std::cout<<"Enter URL:\n";
				getline(std::cin, url);
				newSearch->PrintHTML(url);
				break;
			case 4: // Print saved url's 
				newSearch->PrintURLs();
				break;
			case 5: // Clear saved url's and words
				newSearch->ClearAll();
				std::cout<<"Data has been erased.\n";
				break;
			case 6: // Print all stored words
				newSearch->PrintWords();
				break;
			case 7: // Quit
				std::cout << "Goodbye!" << std::endl;
				quit = true;
				break;
			default:
				std::cout<<"Invalid Input\n";
				std::cin.clear();
				std::cin.ignore(1000,'\n');
				break;
		}
	}

	delete newSearch; // free allocated memory
	
	return 0;
}
