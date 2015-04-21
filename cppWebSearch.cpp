/* cppWebSearch.cpp
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#include "cppWebSearch.h"

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
* PrintHTML accepts the url of a website and prints out the associated HTML code to std out
* Format of url is http://www."remainder of address"
*/
void WebSearch::PrintHTML(std::string url) {     

	using namespace boost::network;

    http::client client;
    http::client::request request(url);
    request << header("Connection", "close");
    http::client::response response = client.get(request);
    std::cout << body(response) << std::endl;

}
