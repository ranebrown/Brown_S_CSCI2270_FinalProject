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

	// create connection to the entered url and print the html code
    http::client client;
    http::client::request request(url);
    request << header("Connection", "close");
    http::client::response response = client.get(request);
	std::ofstream txtFile("temp.txt");
	if(txtFile.is_open()) {
		txtFile << body(response);
		txtFile << "\n";
	}
	txtFile.close();
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
