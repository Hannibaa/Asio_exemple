#include <iostream>
#include <memory>
#include <string>

#include <asio.hpp>

#define API_KEY2   "bc62313ee6d37ec63dd2c3cdac147bb1"                // "d317200af99ae45b51c9e5c3e8f6eb80"
#define API_KEY    "d317200af99ae45b51c9e5c3e8f6eb80"
#define BASE_URL   "https://api.openweathermap.org/data/2.5/weather" // OpenWeatherMap API URL

// function to construct the api request URL based on city ID
std::string build_url(int city_id) {
	return BASE_URL + std::string("?q=") + "London,uk" + "&APPID=" + API_KEY;
}

// function to parse the JSON response and extract relevant weather information
std::string parse_weather(const std::string& json) {
	// Implement logic to parse JSON data using a JSON library (RapidJSON, nlohmann)
	// Extract specific weather data (e.g., temperature, description ...) and format a human-readable string
	// Replace this placeholder with your parsing logic

	return json;
}

int main() {
	// Replace the city id you want to get weather for 
	int city_id = 524901; // London (exemple)

	try {
		asio::io_context  ctx;

		// Create a tcp socket
		asio::ip::tcp::socket  socket(ctx);

		// Resolve the hostname and port
		asio::ip::tcp::resolver resolver(ctx);
		asio::ip::tcp::resolver::results_type endpoints =
			resolver.resolve({ "api.openweathermap.org", "https" });

		// Connect to the server
		asio::connect(socket, endpoints);

		// Build the HTTP Get request
		std::string request = "GET " + build_url(city_id) + " HTTP/1.1\r\n";
		request += "Host: api.openweathermap.org\r\n";
		request += "Connection: close\r\n\r\n";

		// Send the request
		asio::write(socket, asio::buffer(request));

		// Recieve the request
		asio::streambuf resp_buff;
		asio::read_until(socket, resp_buff, "\r\n\r\n");

		// Extract the response body
		std::string response = asio::buffer_cast<const char*>(resp_buff.data());

		std::cout << response << "\n";
	}
	catch (std::exception& e) {
		std::cerr << "Exception : " << e.what() << "\n";
	}

	return 0;
}