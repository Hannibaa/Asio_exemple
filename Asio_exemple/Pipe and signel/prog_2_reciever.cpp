//                                    RECIEVER OF MESSAGE
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <thread>

#include <MyLib/Console_Library/escape_code.h>

/*
		 This Program react as reciever to stdin ; some random string : every 5 sec :
		 =============== NOT WORKING ===================
		 IN MATTER TO SENDE A DATA MESSAGE AND RECIEVE MESSAGE 
		 WE NEED TO IMPLEMENT PIPE OR SHARED MEMORIE 
		 WE TRIE THIS IN MAC-OS AND WINDOWS <LINUX KALI> .
*/




bool bStop = false;




int main() {

	// Lunch thread stoping loops
	std::thread thrStop([] {
		while (true) {
			if (_getch() == ESCAPE) {
				bStop = true;
				std::terminate();
				break;
			}
		}
		});

	char buff[11]{};
	int count{};

	while (true) {
		if (bStop) break;

		if (fgets(buff, sizeof(buff), stdin) == NULL) {
			std::cout << "Empty!" << end_;
			continue;
		}

		std::cout << ++count << " " << buff << end_;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	thrStop.detach();

	print_ << "End of reciever program" << end_;
	return 0;
}