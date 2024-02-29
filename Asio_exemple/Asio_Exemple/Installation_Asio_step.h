#pragma once
/*
          step to install asio in visual studio
          1. download Asio from asio library c++ no boost stand alone.
          2. download Zip file
          3. unZip file 
          4. Create empty project 
          5. add source file
          6. Link project  
            6.1 Propertie page->(all config & all platform)->VC++ directory
                ->include directories: add path : E:\lsjflsfj\sfs\asio1.18\include
         also
         #define ASIO_STANDALONE
         in windows add ?
         #ifndef _WIN32
         #define _WIN32_WINNT 0x0A00
         #endif

         In Linux : 
         some way.
         in source repository ???.
*/