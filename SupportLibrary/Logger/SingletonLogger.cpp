/////////////////////////////////////////////////////////////////////
// SingletonLogger.cpp - provides logging to multiple streams      //
// ver 1.0                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
/*
* Package Description:
* ===============================
* This package provides logging facility for project #2
* Singleton logger is provided in this package
* You should use factory mode to get logger instances 
* in your implementation of logger.
* ===============================
* File Description:
* This file contains a test stub for Logger packages,
* You can test logger facility functionally here.
* ===============================
* Required files:
* SingletonLogger.h
* FileUtilities.h
* CodeUtilities.h
* ===============================
*/

#include "SingletonLogger.h"
//#include "../Utilities/FileUtilities.h"
//#include "../Utilities/CodeUtilities.h"
#include "../Utilities/Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#define TEST_SINGLETONLOGGER

#ifdef TEST_SINGLETONLOGGER
int main()
{
	/*		Test Stub		*/
	std::cout << "\n  Demonstrating Singleton Logger"; std::cout << "\n ================================";
	using Logger = Utilities::Logger<1, Utilities::Lock>;
	Logger* pLogger = Logger::getInstance();
	Logger* pTest = Logger::getInstance();
	if (pTest == pLogger) std::cout << "\n  Observed singleton behavior\n";
	else std::cout << "\n  Not behaving as singleton\n";
	// Logger has &std::cout as default stream.
	// Uncomment the statement below to remove that default.
	//pLogger->removeStream(&std::cout);
	std::string fileSpec = "..\\Logger_Test_Stub.txt";
	std::ofstream outfileStrm(fileSpec, std::ios::out);
	if (outfileStrm.good())
		pLogger->addStream(&outfileStrm);  // adding pointer to std::ofstream instance
	std::cout << "\n  logging to console and " << fileSpec << "\n";
	std::string head = "\n  Demonstration Log";
	pLogger->writeHead(head);
	pLogger->write("  Hi from main");
	pLogger->write("  hi again");
	pLogger->writeTail();
	outfileStrm.close();
	std::string msg = "displaying contents of " + fileSpec;
	// Demonstrates writing file contents to std::ostringstream.
	// If you remove out, will display directly to console inside
	// function.
	std::ostringstream out; Utilities::displayFileContents(msg, fileSpec, out);
	std::cout << out.str(); std::cout << "\n";	pLogger->addStream(&out);
	std::cout << "\n  attempting to remove std::ostringstream out";
	if (pLogger->usingStream(&out)) std::cout << "\n  Logger has std::ostringstream out";
	else std::cout << "\n  Logger does not have std::ostringstream out";
	std::cout << "\n  removing std::ostringstream out";
	pLogger->removeStream(&out);
	std::cout << "\n  attempting to remove std::ostringstream out";
	if (pLogger->usingStream(&out)) std::cout << "\n  Logger has std::ostringstream out";
	else std::cout << "\n  Logger does not have std::ostringstream out"; std::cout << "\n\n";
	outfileStrm.close();
	return 0;
}
#endif