//                                   SENDER OF MESSAGE
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <thread>

#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/stringfunctionhelper.h>

/*
         This Program react as sender to stdin ; some random string : every 5 sec :
         ===== NOT WORKING =====
*/

bool bStop = false;

int main() {
    // Create Thread stopper
    std::thread  thrStoper([] {
        while (true) {
            if (_getch() == ESCAPE) {
                bStop = true;
                break;
            }
        }
        });

    // Create random string
    std::string buf ;

    // Loop that create random string and send in to stdin : 
    int count{};
    while (true) {
        buf = Str::getRandomString(10);
        std::cout << ++count << " " << buf << end_;
        fputs(buf.c_str(), stdin);
        std::this_thread::sleep_for(std::chrono::seconds(3));

        if (bStop == true) break;
    }


    thrStoper.detach();

    print_ << "End of Program Sender" << end_;
    return 0;
}