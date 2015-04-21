/* cppWebSearch
 * main.cpp
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#include "cppWebSearch.h"

int main(int argc, char *argv[]) {
	WebSearch *newSearch;
	std::string url;
	getline(std::cin, url);
	std::cout << url << std::endl;
	newSearch->PrintHTML(url);	
	return 0;
}
