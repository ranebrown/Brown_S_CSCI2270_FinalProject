/* cppWebSearch
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#ifndef cppWebSearch_H 
#define cppWebSearch_H

#include <iostream>

struct WebQueue {
	
};

struct WordHash {

};

class WebSearch {
	public:
		WebSearch();
		virtual ~WebSearch();
		void EnqueueSite(std::string url);
		void PrintHTML(std::string url);
	protected:

	private:

};

#endif // cppWebSearch_H 
