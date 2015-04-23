/* cppWebSearch
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#ifndef cppWebSearch_H 
#define cppWebSearch_H

#include <iostream>

struct WordHash {

};

class WebSearch {
	public:
		WebSearch();
		virtual ~WebSearch();
		void EnqueueSite(std::string url);
		void BuildQueue(std::string url, int depth);
		void PrintHTML(std::string url);
	protected:

	private:
		std::queue<std::string> urlList; // queue to store list of urls up to specified depth
};

inline void DisplayMenu() {
	using namespace std;
	cout << "======Main Menu======" << endl;
	cout << "1. Initialize cppWebSearch" << endl;
	cout << "2. Search for a word" << endl;
	cout << "3. Print HTML code" << endl;
	cout << "4. Clear saved data" << endl;
	cout << "5. Quit" << endl;
}

#endif // cppWebSearch_H 
