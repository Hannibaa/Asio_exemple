#include <iostream>
#include <thread>

#include <asio.hpp>
#include <MyLib/stringfunctionhelper.h>
#include <MyLib/Console_Library/escape_code.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    Function that get all IP address of hostname http address
//    Returned to vector on string ip addresses  
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string>   get_ip_address_from(const std::string& http_address) {
	// create context for asio run 
	asio::io_context   ctx;

	// create resolver and assossiated to context
	asio::ip::tcp::resolver resolver(ctx);

	// create vector of string
	std::vector<std::string>  vIPaddresses;

	// call function asyncrozly 
	resolver.async_resolve(asio::ip::tcp::resolver::query(http_address, "http"),
		[&vIPaddresses](const std::error_code& ec, asio::ip::tcp::resolver::iterator iter) {
			if (ec) {
				std::cerr << "Error : " << ec.message() << '\n';
				return;
			}

			asio::ip::tcp::resolver::iterator end;

			for (; iter != end; ++iter) {
				asio::ip::tcp::endpoint endpoint = *iter;
				vIPaddresses.push_back(endpoint.address().to_string());
			}
		});


	// run io context 
	ctx.run();

	return vIPaddresses;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    Get Entire HTML code and in buffer.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////


asio::mutable_buffer    get_HTML(const std::string& http_address) {


	return{};
}







/*                      
*                    this testing check for the function get_ip_address_from;
* 
int main() {
	Print_(color::Red, "Testing of function get_ip from http address hostname") << end_;
	// testing function 

	auto v_ip = get_ip_address_from("www.yahoo.com");

	print_ << "numbers of ip is : " << v_ip.size() << end_;

	Str::PrintWords(v_ip);

	Print_(color::Green, "End of Program") << end_;
	return 0;
}
*/