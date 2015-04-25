#Brown_S_CSCI2270_FinalProject

##Project Summarry
Project Name: cppWebSearch

cppWebSearch is a webcrawler/search engine. The goal of the project is to create a simple search program that runs from command-line. The program operates by downloading the HTML code from a base website and scanning this code for links to other websites. Each website will be stored in a queue and when it is dequeued the text will be scanned for further links. A ranking algorithm will be used to determine the number of occurences of keywords. The user can then enter a word and the website with the highest occurence of that word will be returned. 

##How to Run
1. Install Dependencies
2. If desired run tests from cpp-netlib and boost websites to ensure dependencies are operating correctly.
3. Modify makefile so required header files and libraries are referenced correctly.
4. Compile using `make`
5. Run `./test` to ensure functions are operating correctly

##Dependencies
###cpp-netlib v0.11.1
1. Install make if not already installed. For Mac this is installed through Xcode - developer tools.
2. Install Cmake [http://www.cmake.org/download/](http://www.cmake.org/download/)
  2. Download the source code, not the binary.
  2. Place the downloaded source code in desired directory.
  2. In terminal `cd /*pathTo*/cmake-3.2.2`
  2. Default install directory is /usr/local/bin to change the install directory use `--prefix=/*desiredPath*` option (after ./bootstrap)
  2. Type `./bootstrap --help` for other options
  2. Install Cmake with `./bootstrap && make && make install`
3. Install boost - instructions below
4. Download cpp-netlib [http://cpp-netlib.org/#download](http://cpp-netlib.org/#download)
5. Place download in desired directory and `cd /*pathTo*/cpp-netlib-0.11.1-final`
  2. Make a build directory: `mkdir build && cd build` (cpp-netlib recommends making build directory outside of source directory but I didn't do this)
  2. Run Cmake with following commands
   ```
   cmake -DCMAKE_BUILD_TYPE=Debug \
    
   -DCMAKE_C_COMPILER=clang   \
       
   -DCMAKE_CXX_COMPILER=clang++ \
    
   -DBOOST_ROOT=/*pathTo*/boost_1_57_0 \

   /*pathTo*/cpp-netlib-0.11.1-final
   ```
  2. Run `make test` (optional)
  2. Run `sudo make install`
   This installs libraries in /usr/local/lib

###boost v1.57.0
1. Download boost source code [http://www.boost.org/users/history/version_1_57_0.html](http://www.boost.org/users/history/version_1_57_0.html)
2. Place source code in desired directory. Open terminal `cd /*pathTo*/boost_1_57_0`
3. `./bootstrap.sh --help` for options
4. Install boost libraries
  2. `./bootstrap.sh --prefix=/*pathToInstall*`
  2. Run `./b2 install`
5. Binaries will be installed in /lib subdirectory of installation path
6. Header files will be installed in /include directory of installation path 

##System Requirments
All code was written and tested on a Mac running OSX Yosemite. 

All dependencies are compatible with Windows and Linux. It should be possible to run the main program on these OS's but it has not been tested.

##Group Members
Rane Brown

##Contributors

##Open issues/bugs
When using boost in conjunctio with cpp-netlib it is not possible to run lldb debugger. Initial testing was done in Xcode and Xcode would crash when trying to run cppWebSearch. Using a makefile and running from command line seemed to fix issue. When attempting to debug with lldb from the command line recieved "bus error 10".

Due to the above issues debugging was conducted by commenting out sections of code that request a http connection. 
