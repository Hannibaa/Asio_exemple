#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/CFile.h"
#include "MyLib/chrono/Timer.h"


using Map_Address = std::map<std::string, std::string>;

std::vector<char> vBuffer(1 * 1024);

size_t iCount{};

void GrabSomeData(asio::ip::tcp::socket& socket,std::ostream& os) {

	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
		[&](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				std::cout << "\n\nRead " << length << " bytes\n\n";

				for (int i = 0; i < length; i++)
					os << vBuffer[i];

				++iCount;
				GrabSomeData(socket, os);
			}
		});
}

void scan_ipv4(const std::string adress_ipv4) {
	// make timer to mesure times.
	Timer timer;

	asio::error_code ec;

	// Create a "context"
	asio::io_context context;

	// Give some fake tasks to asio so the context doesnt finish
	asio::io_context::work idleWork(context);

	// Start the context 
	std::thread thrContext = std::thread([&]() {context.run(); });

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address(adress_ipv4, ec), 80);

	// Create a socket, the context will deliver the implimentation
	asio::ip::tcp::socket socket(context);

	// Tell socket to try and connect 
	timer.Restart();
	socket.connect(endpoint, ec);
	float elapsed_time = timer.GetElapsedTime();
	print_ << "time to connect : " << elapsed_time << end_;

	// open file to enregister the information about site web :
	std::ofstream ofile{ "ip_" + adress_ipv4 + ".txt" };
	ofile << "Aoues Kadda Type File : " << end_;
	ofile << "date : " << end_;
	ofile << "ipv4 : " << adress_ipv4 << end_;
	ofile << "data section : " << end_;

	if (!ec) {
		print_ << "Connected!..." << end_;
	}
	else {
		print_ << "Failed to connect to address : " << adress_ipv4 << end_ <<
			"error : " << ec.message() << end_;
		ofile << "Failed to connect to address : " << adress_ipv4 << end_ <<
			"error : " << ec.message() << end_;
	}

	// send http request : if socket is open

	if (socket.is_open()) {
		//std::string sRequest =
		//	"GET https://adservice.google.dz/adsid/google/si?gadsid=AORoGNSrQghoqyxKZGOeORpHVKTRWMXfVzkYcPxFb1T5c4rRiRVufJtt2D8bPpyH8dWfDbvM2O0TdhhMyELr6n8"
		//	"Host: adservice.google.dz\r\n"
		//	"Connection: close\r\n\r\n";
		GrabSomeData(socket, ofile);

		std::string sRequest =
			"GET  /  HTTP/1.1\r\n"
			//	"Host: google.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
		print_ << "Error of Request : " << ec.message() << end_;

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		context.stop();
		if (thrContext.joinable()) thrContext.join();


	}

	print_ << "size of buffer data : " << vBuffer.size() << end_;
	print_ << "grab data times : " << iCount << end_;
	ofile << end_;
	ofile << "elapsed time to read : " << elapsed_time << end_;

	ofile.close();
}

Map_Address get_addresses(const fs::path& filename) {

	return {};
}

int main()
{
	std::osyncstream str(std::cout);
	print_ << "-------------------------------------------------" << end_;
	print_ << "----- Program that read some data from site -----" << end_;
	print_ << "-------------------------------------------------" << end_;

	// get address from file data :
	fs::path filename_addresses;
	
	auto mapAddresses = get_addresses(filename_addresses);

	// using map to store name of site and theire ip addresses :
	Map_Address mapAddress{
		{"google","142.250.201.4" },
		{"yahoo","87.248.119.252"},
		{"no-site","8.8.8.8"}
	};


	for (const auto& e : mapAddress) {
		scan_ipv4(e.first);
	}


	
	std::cin.get();
	return 0;
}