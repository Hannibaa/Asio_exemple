#include <iostream>
#include <syncstream>

#include <asio.hpp>
#include "MyLib/Console_Library/escape_code.h"
#include "asio_utillity.h"


/*
      Posting work by using post
      .post()
*/

#define  out   print_ 

void timer_expire(std::string id) {
    print_ << now_time << " " << id << " enter.\n";
    Sleep(Seconds(3));
    print_ << now_time << " " << id << " leave.\n";
}

int main() {
    print_ << "main thread id " << ThreadId << end_;

    asio::io_service service;
    asio::io_service::strand strand(service);

    asio::steady_timer timer1(service, Seconds(5));
    asio::steady_timer timer2(service, Seconds(5));
    // add third timer.
    asio::steady_timer timer3(service, Seconds(6));

    timer1.async_wait(strand.wrap([](auto...args) {
        print_ << "timer1 " << ThreadId << end_;
        timer_expire("timer1");
        }));

    timer2.async_wait(strand.wrap([](auto...args) {
        print_ << "timer2 " << ThreadId << end_;
        timer_expire("timer2");
        }));

    timer3.async_wait([](auto...args) {
        print_ << "timer3 " << ThreadId << end_;
        timer_expire("timer3");
        });

    std::thread ta([&] {service.run(); });
    std::thread tb([&] {service.run(); });
    std::thread tc([&] {service.run(); });

    ta.join();
    tb.join();
    tc.join();

    print_ << "program end..." << end_;
    return 0;
}





//// before use strand
//int main() {
//    print_ << "main thread id " << ThreadId << end_;
//
//    asio::io_service service;
//    asio::io_service::strand strand(service);
//
//    asio::steady_timer timer1(service, Seconds(5));
//    asio::steady_timer timer2(service, Seconds(5));
//
//    timer1.async_wait([](auto...args) {
//        print_ << "timer1 " << ThreadId << end_;
//        timer_expire("timer1");
//        });
//
//    timer2.async_wait([](auto...args) {
//        print_ << "timer2 " << ThreadId << end_;
//        timer_expire("timer2");
//        });
//
//
//    std::thread ta([&] {service.run(); });
//    std::thread tb([&] {service.run(); });
//
//    ta.join();
//    tb.join();
//
//    print_ << "program end..." << end_;
//    return 0;
//}
//


//int main() {
//    print_ << "this id : " << ThreadId << end_;
//
//    asio::io_context  ctx;
//
//    ctx.post([] { out << "eat \n"; out << "id : " << ThreadId << end_;  });
//
//    ctx.post([] { out << "drink \n"; out << "id : " << ThreadId << end_; });
//
//    asio::post([] {out << "hello world post :\n"; out << "id : " << ThreadId << end_; });
//
//    std::thread thrContext([&] {
//        ctx.run();
//        });
//
//
//    thrContext.join();
//
//    return 0;
//}


