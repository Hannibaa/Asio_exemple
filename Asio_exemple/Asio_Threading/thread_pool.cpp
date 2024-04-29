#include <asio.hpp>
#include <iostream>

#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/random_variable.h"

using byte = unsigned char;

std::vector<byte> make_random_vector(size_t _size_buffer) {
	RV::RV<int>  rand_byte{ 0, 255 };

	std::vector<unsigned char> v;
	for (int i = 0; i != _size_buffer; ++i) 
		v.push_back(static_cast<unsigned char>(rand_byte));

	return v;
}


void print_buffers(const asio::mutable_buffer& buffer, std::string_view comment, int line = 60) {
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "buffer : " << comment << " size : " << buffer.size() << "\n";
	for (int i = 0; i != buffer.size(); ++i) {
		unsigned char* pchar = static_cast<unsigned char*>(buffer.data());
		std::cout << *(pchar + i) << " , ";
		if (i % line == line - 1) std::cout << "\n";
	}

	std::cout << "\n----------------------------------------------------------------\n";
}

void print_any(std::string_view comment, int n) {
	for (int i = 0 ; i < n ; ++i)
	std::cout <<  comment ;
}

int main() {

	asio::thread_pool   pool{ 4 };

	std::vector<std::string> vstr{ "A", "|", "@" , ".", " " };


	for (auto& str : vstr) asio::post(pool, std::bind(print_any, str, 300));

	pool.join();

	wait_;
	return 0;
}








	//asio::mutable_buffer  buf;
	//auto v = make_random_vector(100);
	//buf = asio::buffer(v);
	//print_buffers(buf, "random buffer");               // buf is pointed to vector data.
	//v.clear();                                         // very bad 
	//print_buffers(buf, "random buffer after clear v"); // don't do that 