/* cppWebSearch
 * main.cpp
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#include "cppWebSearch.h"

int main(int argc, char *argv[]) {
	WebSearch *newSearch = new WebSearch;
	std::string url;
	std::cout<<"Enter a url\n";
	getline(std::cin, url);
	newSearch->PrintHTML(url);	
	return 0;
}
