#include <iostream>
#include <asio.hpp>

#include <MyLib/Console_Library/escape_code.h>

#define __exemple_2

template<typename T>
void print_buf(asio::mutable_buffer buf) {
	print_ << "buf.data() : " << buf.data() << end_;

	if constexpr (std::is_same_v<T, wchar_t>)
		wprint_ << "(T*)buf.data() : " << (T*)buf.data() << wend_;
	else
		print_ << "(T*)buf.data() : " << (T*)buf.data() << end_;

	print_ << "(void*)buf.data() : " << (void*)buf.data() << end_;
	print_ << "size : " << buf.size() << end_;
}

void print_const_buf(asio::const_buffer cbuf) {

	print_ << "cbuf.data() : " << cbuf.data() << end_;
	print_ << "cbuf.size() : " << cbuf.size() << end_;
	
}

#ifdef __exemple_2

struct _Point {
	float x;
	float y;
};


int main() {
	Print_(color::Green, "Exemple buffers in vector") << end_;

	std::vector<int> vi{ 2,3,4,5,6 };
	std::vector<_Point> vpoints(10, _Point(1.f,1.5f));
	std::array<uint8_t, 10> head{ 0x23, 0xaa };
	std::string msg{ "hello world asio" };
	std::wstring wmsg{ L"windows message" };

	std::vector<asio::const_buffer>  buffers{ asio::buffer(vi),
											 asio::buffer(vpoints),
											 asio::buffer(head),
											 asio::buffer(msg),
											 asio::buffer(wmsg) };


	for (auto& e : buffers)
		print_const_buf(e);
	

	Print_(color::Green, "End program") << end_;
	wait_;
	return 0;
}

#endif






#ifdef  __exemple_1


int main() {
	Print_(color::Green, "Exemple testing Buffer asio") << end_;

	std::string str{ "hello" };
	std::wstring wstr{ L"hi Hello \x2588" };

	asio::mutable_buffer  buf(asio::buffer(str));
	asio::mutable_buffer  buf2(asio::buffer(wstr));
	asio::mutable_buffer  buf3((void*)wstr.data(), wstr.size() * sizeof(std::wstring::value_type));
	asio::mutable_buffer  buf4(wstr.data(), wstr.size());

	print_buf<char>(buf);
	print_ << "-------------------------------------------------------------";
	print_buf<wchar_t>(buf2);
	print_ << "-------------------------------------------------------------";
	print_buf<char>(buf2);
	print_ << "-------------------------------------------------------------";
	print_buf<wchar_t>(buf3);
	print_ << "-------------------------------------------------------------";
	print_buf<wchar_t>(buf4);

	Print_(color::Green, "End of program") << end_;
	wait_;
	return 0;
}

#endif 