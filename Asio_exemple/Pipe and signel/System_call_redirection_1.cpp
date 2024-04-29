#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "MyLib/stringfunctionhelper.h"
#include "MyLib/Console_Library/escape_code.h"

/* 
          This program is exemple to demostrate how to redirect a result of command line
		  in windows - same as in MacOS and Linux.
		  Author : KADDA Aoues
		  Date   : 25 / 04 / 2024

*/

std::string _trait_string_name(std::string str) {

	// 1. Remove any un-accepted char in file name / \ | * ? : < > " '
	std::string no_file_char = R"(\?/"|*<>:')";
	str = Str::removeUnusefullCharAny(str, no_file_char);
 
	// 2. Remove any extra space from string. 
	str = Str::remove_successive_char(str);

	// 3. Replace all space by space
	Str::replace_inplace(str, ' ', '_');

	return str;
}

int main() {
	print_ << "this program is to save command output to text file " << end_;
	print_ << "writen by : KADDA Aoues." << end_;

	print_ << "enter command >";
	std::string    command{};

	std::cin >> command;

	// file name for output of command line : take there name :
	std::string    file_name = _trait_string_name(command) + ".txt";
	std::cout << "output file : " << file_name << '\n';
	std::cin.get();

	// Create pipe or redirection of command line in windows : these need more documentation.
	FILE* pipe = _popen(command.c_str(), "r");


	if (!pipe) {
		std::cerr << "Error in opening pipe\n";
		return -1;
	}

	// open file
	std::ofstream  ofs(file_name);
	if (!ofs.is_open()) {
		std::cerr << "Error in opening file" << std::endl;
		_pclose(pipe);
		return 1;
	}

	// buffer
	char buffer[128];
	while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
		std::cout << buffer;
		ofs << buffer;
	}

	int exit_code = _pclose(pipe);

	if (exit_code == -1) {
		std::cerr << "Error executing command\n";
	}

	ofs.close();
	return exit_code;
}