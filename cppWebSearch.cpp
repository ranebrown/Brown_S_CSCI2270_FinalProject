/* cppWebSearch.cpp
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#include "cppWebSearch.h"
#include <boost/network/protocol/http/client.hpp>
#include <string>
#include <queue>
#include <fstream>
#include <unistd.h> // for usleep function

/* 
* Constructor - creates instance of WebSearch class
*/
WebSearch::WebSearch() {

}

/*
* Destructor - destorys instance of WebSearch class when it goes out of scope
*/
WebSearch::~WebSearch() {

}

/*
* EnqueSite function accepts the address of a website and adds it to the queue
* of sites that are waiting to be searched for further links and keywords.
* Format of url is http://www."remainder of address"
*/
void WebSearch::EnqueueSite(std::string url) {

}

/*
* Build Queue scans each website for links and adds the links to a queue. 
* The queue is set to be of size depth specified by user. Once the queue is full
* further searching stops.
*/
void WebSearch::BuildQueue(std::string url, int depth) {
	using namespace boost::network;
	std::queue<std::string> urlList; // queue to store list of urls up to specified depth
	urlList.push(url); // add url to queue
	while((int)urlList.size() < depth) {
		url = urlList.front(); // dequeue a url and scan for more links
		usleep(5000); // 5000 microsecond delay

		// create connection to url and save html code to a text file
   		http::client client;
    	http::client::request request(url);
    	request << header("Connection", "close");
    	http::client::response response = client.get(request);
		std::ofstream tempOut("temp.txt");
		if(tempOut.is_open()) {
			tempOut << body(response);
			tempOut << "\n";
		}
		tempOut.close();
	
		// open the text file and scan for urls
		std::ifstream tempIn("temp.txt");
		if(!tempIn.is_open())
			std::cout<<"Error opening file\n";
		else {
			std::string temp;
			std::size_t start, end;
			while(getline(tempIn,temp,' ')) {
				start = temp.find("http://www."); // find the beginning of a new url
				end = temp.find('"',start); // find the end of the url (assuming url in inside "quotes")
				if(start != std::string::npos && end != std::string::npos) {
					std::string foundURL = temp.substr(start, (end-start)); // extract only the url
					urlList.push(foundURL);
				}	
			}
		}	
	}
	while(!urlList.empty()) {
		url = urlList.front();
		urlList.pop();
		std::cout<<url<<std::endl;
	}
}

/*
* PrintHTML accepts the url of a website and prints out the associated HTML code to std out
* Format of url is http://www."remainder of address"
*/
void WebSearch::PrintHTML(std::string url) {     
	std::string valid = "http://www.";
	std::string check(url, 0, 11); //writes the first 11 characters of url to string check
	
	// Check if a valid url was entered
	if(valid.compare(check) != 0) {
		std::cout<<"invalid url\n"<<"url must begin with http://www.\n";
		return;
	}
	
	using namespace boost::network;
	
	// create connection to the entered url and print the html code
    http::client client;
    http::client::request request(url);
    request << header("Connection", "close");
    http::client::response response = client.get(request);
    std::cout << body(response) << std::endl;

}
