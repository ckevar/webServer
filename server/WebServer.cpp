#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>

#include "WebServer.h"

// Handler for when a message is received from the client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	// Parse out the client's request string e.g. GET /index.html HTTP/1.1
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	// Some defaults for output to the client (404 file not found 'page')
	std::string content = "<h1>404 Not Found</h1>";
	std::string requestedFile = "/index.html";
	contentType = "text/html";
	int errorCode = 404;
	// If the GET request is valid, try and get the name
	if (parsed.size() >= 3 && parsed[0] == "GET") {

		requestedFile = parsed[1];
		std::cout << parsed[6] << " asks for " << parsed[1] << std::endl; 
		// If the file is just a slash, use index.html. This should really
		// be if it _ends_ in a slash. I'll leave that for you :)
		if (requestedFile == "/")
			requestedFile = "/index.html";

		MIMEType(&requestedFile);

	}

	// Open the document in the local file system
	std::ifstream f("../wwwroot" + requestedFile);

	// Check if it opened and if it did, grab the entire contents
	if (f.good()) {
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}

	f.close();

	// Write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << errorCode << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: "<< contentType << "\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), size);
}


void MIMEType(rType) {
	int idx = requestedFile.size();
	while (requestedFile[idx - 1] != '.') idx--; 
	std::string mimetype = requestedFile.substr(idx);

	if (mimetype == "html")
		contentType = "text/html";
	
	else if (mimetype == "js") 
		contentType = "text/javascript";

	else if (mimetype == "css") 
		contentType = "text/css";

	else if (mimetype == "jpeg" || mimetype == "jpg") 
		contentType = "image/jpeg";
	
	else if (mimetype == "png") 
		contentType = "image/png";

	else if (mimetype == "mp4")
		contentType = "video/mp4";
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{
	
}