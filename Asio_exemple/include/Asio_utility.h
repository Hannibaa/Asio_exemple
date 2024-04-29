#pragma once

#define  now_time           std::chrono::system_clock::now()
#define  time_now           now_time
#define  Seconds(n)         std::chrono::seconds(n)
#define  Milli(n)           std::chrono::milliseconds(n)
#define  Sleep(duration)    std::this_thread::sleep_for(duration)   
#define  ThreadId           std::this_thread::get_id()

//#define in
//#define out

#define  _CTRL_C            3