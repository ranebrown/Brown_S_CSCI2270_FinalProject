/* Project: cppWebSearch
 * File: cppWebSearch.cpp
 *
 * Created by Rane Brown 4/19/2015
 *
*/

#include "cppWebSearch.h"
#include <boost/network/protocol/http/client.hpp>
#include <string>
#include <fstream>
#include <unistd.h> // for usleep function


/*
Function prototype:
WebSearch::WebSearch()

Function description:
Constructor - creates instance of WebSearch class. No required initilization.

Example:
N/A

Pre-conditions: N/A
Post-conditions: N/A
*/
WebSearch::WebSearch() {

}


/*
Function prototype:
WebSearch::~WebSearch()

Function description:
Destructor - destroys instance of WebSearch class when it goes out of scope

Example:
N/A

Pre-conditions: N/A
Post-conditions: N/A
*/
WebSearch::~WebSearch() {

}

/*
Function prototype:
void WebSearch::EnqueueSite(string)

Function description:
EnqueSite function accepts the address of a website and adds it to the queue
of sites that are waiting to be searched for further links and keywords.
Format of url is http://www."remainder of address"

Example:
WebSearch *newSearch = new WebSearch;
newSearch.EnqueueSite("http://www.google.com");

Pre-conditions: a valid url must be entered as string 
Post-conditions: prints the url that was added to queue
*/
void WebSearch::EnqueueSite(std::string url) {
	std::string valid = "http://";
	std::string check(url, 0, 7); //writes the first 7 characters of url to string check
	
	// Check if a valid url was entered
	if(valid.compare(check) != 0) {
		std::cout<<"invalid url\n"<<"url must begin with http://\n";
		return;
	}
	urlList.push(url);
	std::cout<<url<<" has been added to queue\n";
}

/*
Function prototype:
void WebSearch::BuildQueue(string, int)

Function description:
Build Queue scans each website for links and adds the links to a queue. 
The queue is set to be of size depth specified by user. Once the queue is full
further searching stops.

Example:
WebSearch *newSearch = new WebSearch;
newSearch.BuildQueue("http://www.google.com");

Pre-conditions: a valid url must be entered as string 
Post-conditions: displays each site as it is processed
*/
void WebSearch::BuildQueue(std::string url, int depth) {
	using namespace boost::network;
	if(!urlList.empty()) {
		std::cout<<"Base queue of urls has already been built\n";
		return;
	}
	urlList.push(url); // add url to queue
	bool scan = true;
	std::queue<std::string> tempQ;
	tempQ.push(url);

	while((int)urlList.size() < depth) {
		scan = true;
		if(tempQ.empty()) // couldn't find enough links to
			break;
		url = tempQ.front(); // extract next url and scan for more links
		tempQ.pop();
		usleep(200000); // .2 second delay

		// create connection to url and save html code to a text file
   		try {
			std::cout<<"Processing: "<<url<<std::endl;
			http::client client;
    		http::client::request request(url);
    		request << header("Connection", "close");
    		http::client::response response = client.get(request);
			remove("temp.txt"); // delete old temporary text file
			std::ofstream tempOut("temp.txt");
			if(tempOut.is_open()) {
				tempOut << body(response);
				tempOut << "\n";
			}
			tempOut.close();
		}
		catch(boost::system::system_error const& ec) {
			std::cout<<"Connection error to url: "<<url<<std::endl;
			scan = false;
			if(urlList.size() ==1)
				return;
		}
		catch(std::bad_alloc& ba) {
			std::cout<<"Allocation error with:"<<url<<std::endl;
			scan = false;
			if(urlList.size() ==1)
				return;
		}
		catch (const std::length_error& le) {
			std::cout<<"Length error with:"<<url<<std::endl;
			scan = false;
			if(urlList.size() ==1)
				return;
		}

		if(scan == true) {
			// open the text file and scan for urls
			std::ifstream tempIn("temp.txt");
			if(!tempIn.is_open())
				std::cout<<"Error opening file\n";
			else {
				std::string temp;
				std::size_t start, end;
				bool unique;
				while(getline(tempIn,temp,' ')) {
					if((int)urlList.size() >= depth)
						break;
					start = temp.find("http://www."); // find the beginning of a new url
					end = temp.find('"',start); // find the end of the url (assuming url in inside "quotes")
					if(start != std::string::npos && end != std::string::npos) {
						std::string foundURL = temp.substr(start, (end-start)); // extract only the url
						std::string valid = "http://";
						std::string check(foundURL, 0, 7);
	
						// Check found url is valid
						if(valid.compare(check) != 0); // do nothing
						else {
							unique = IsUnique(foundURL); // check if found url is unique (hasn't already been found)
							if(unique == true) {
								urlList.push(foundURL);
								tempQ.push(foundURL);
							}
						}
					}
					if( tempIn.eof() ) break;	
				}
			}	
		}
	}
	std::cout<<"...................\n";
	StoreWords();
}

/*
Function prototype:
bool WebSearch::IsUnique(string)

Function description:
Takes a url as input and checks if that url has already been added to queue.
If it has already been added returns false. Otherwise returns true.

Example:
WebSearch *newSearch = new WebSearch;
newSearch.IsUnique("http://www.google.com");

Pre-conditions: a valid url must be entered as string 
Post-conditions: returns true or false
*/
bool WebSearch::IsUnique(std::string url) {
	bool unique = true;
	std::queue<std::string> tempQueue;
	std::string dqURL;

	// copy queue to temp location
	while(!urlList.empty()) {
		dqURL = urlList.front();
		urlList.pop();
		tempQueue.push(dqURL);
	}
	
	// check if url has already been added
	while(!tempQueue.empty()) {
		dqURL = tempQueue.front();
		tempQueue.pop();
		if(dqURL == url)
			unique = false;
		urlList.push(dqURL); // copy back to original queue
	}		
	return unique;
}

/*
Function prototype:
void WebSearch::PrintHTML(string) 

Function description:
PrintHTML accepts the url of a website and prints out the associated HTML code to std out
Format of url is http://www."remainder of address"

Example:
WebSearch *newSearch = new WebSearch;
newSearch.PrintHTML("http://www.google.com");

Pre-conditions: a valid url must be entered as string 
Post-conditions: prints the html code to std out
*/
void WebSearch::PrintHTML(std::string url) {     
	std::string valid = "http://";
	std::string check(url, 0, 7); //writes the first 11 characters of url to string check
	
	// Check if a valid url was entered
	if(valid.compare(check) != 0) {
		std::cout<<"invalid url\n"<<"url must begin with http://\n";
		return;
	}
	
	using namespace boost::network;

	try {
		http::client client;
		http::client::request request(url);
		request << header("Connection", "close");
		http::client::response response = client.get(request);
		std::cout << body(response) << std::endl;
	}
	catch(boost::system::system_error const& ec) {
		std::cout<<"Connection error to url: "<<url<<std::endl;
		return;
	}
	catch(std::bad_alloc& ba) {
		std::cout<<"Allocation error with:"<<url<<std::endl;
		return;
	}
	catch (const std::length_error& le) {
		std::cout<<"Length error with:"<<url<<std::endl;
		return;
	}
}

/*
Function prototype:
void WebSearch::PrintURLs() 

Function description:
Prints all saved urls while preserving the original queue

Example:
WebSearch *newSearch = new WebSearch;
newSearch.PrintURLs();

Pre-conditions: Must have initialized search with BuildQueue function
Post-conditions: prints all saved urls or error message
*/
void WebSearch::PrintURLs() {
	std::queue<std::string> tempQueue;
	std::string dqURL;

	if(urlList.empty())
		std::cout<<"No urls in queue, they have already been processed or not yet stored\n";

	// copy queue to temp location
	while(!urlList.empty()) {
		dqURL = urlList.front();
		urlList.pop();
		tempQueue.push(dqURL);
	}

	// Print all queued urls
	while(!tempQueue.empty()) {
		dqURL = tempQueue.front();
		tempQueue.pop();
		std::cout<<dqURL<<std::endl;
		urlList.push(dqURL);
	}
}

/*
Function prototype:
void WebSearch::StoreWords()

Function description:
Processes each URL in the queue for words. Function stores each word and the 
number of times that word occurs in each website

Example:
WebSearch *newSearch = new WebSearch;
newSearch.StoreWords();

Pre-conditions: Must have at least one url stored in queue
Post-conditions: Displays each site as it is processed, creates hash table of stored words
*/
void WebSearch::StoreWords() {
	using namespace boost::network;
	if(urlList.empty()) {
		std::cout<<"There are no URLs to process for words.\n";
		return;
	}
	std::string url;
	bool scan;
	std::queue<std::string> temp;
	while(!urlList.empty()) {
		scan = true;
		url = urlList.front();
		urlList.pop();
		temp.push(url);
		usleep(200000); // .2 second delay

		// create connection to url and save html code to a text file
   		try {
			std::cout<<"Processing: "<<url<<" for words\n";
			http::client client;
    		http::client::request request(url);
    		request << header("Connection", "close");
    		http::client::response response = client.get(request);
			remove("temp.txt"); // delete old temporary text file
			std::ofstream tempOut("temp.txt");
			if(tempOut.is_open()) {
				tempOut << body(response);
				tempOut << "\n";
			}
			tempOut.close();
		}
		catch(boost::system::system_error const& ec) {
			std::cout<<"Connection error to url: "<<url<<std::endl;
			std::cout<<"Remainder of URLs will process\n";
			scan = false;
			
		}
		catch(std::bad_alloc& ba) {
			std::cout<<"Allocation error with:"<<url<<std::endl;
			std::cout<<"Remainder of URLs will process\n";
			scan = false;
		}
		catch (const std::length_error& le) {
			std::cout<<"Length error with:"<<url<<std::endl;
			std::cout<<"Remainder of URLs will process\n";
			scan = false;
		}
		if(scan == true) {
			// open the text file and scan for urls
			std::ifstream tempIn("temp.txt");
			if(!tempIn.is_open())
				std::cout<<"Error opening file\n";
			else {
				std::string temp;
				int i = 0;
				while(getline(tempIn,temp,' ')) {
					i++;
					hTable.Insert(temp,url); // store the word and related url in hash table
					if( tempIn.eof() ) break;
				}
				std::cout<<"\t found:"<<i<<" words"<<std::endl;
			}	
		}
	}
	// copy urls back to original queue
	while(!temp.empty()) {
		url = temp.front();
		temp.pop();
		urlList.push(url);
	}
}

/*
Function prototype:
void WebSearch::PrintWords()

Function description:
Prints all stored words

Example:
WebSearch *newSearch = new WebSearch;
newSearch.PrintWords();

Pre-conditions: Must have words stored hash table
Post-conditions: Displays all stored words to std out
*/
void WebSearch::PrintWords() {
	hTable.Print();
}

/*
Function prototype:
void WebSearch::FindWebsite(string)

Function description:
Searches for the website that contains the highest occurence of a user specifed word
Prints the found website url

Example:
WebSearch *newSearch = new WebSearch;
newSearch.FindWebsite("it");

Pre-conditions: Must have words stored hash table
Post-conditions: Prints address of URL with highest occurence of word
*/
void WebSearch::FindWebsite(std::string word) {
	hTable.Find(word);
}

/*
Function prototype:
void WebSearch::ClearAll()

Function description:
Deletes all stored words and URLs

Example:
WebSearch *newSearch = new WebSearch;
newSearch.ClearAll();

Pre-conditions: Must initialized queue and have words stored in hashtable
Post-conditions: Deletes all stored values
*/
void WebSearch::ClearAll() {
	// clear hash table values
	hTable.Clear();
	// clear queue of saved urls
	while(!urlList.empty()) {
		urlList.pop();
	}
}
