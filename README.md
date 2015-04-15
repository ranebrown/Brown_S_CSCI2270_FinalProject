#Brown_S_CSCI2270_FinalProject

##Project Summarry


##How to Run

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
None currently 
