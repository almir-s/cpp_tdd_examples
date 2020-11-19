 - This repository covers basics of TDD principles provided in the book "Modern C++ Programming with Test-Driven development" by Jeff Langr.
 
 Prerequisites:
  - C++ compailer std = c++14.
  - Boost CPP libraries - For ubuntu run "sudo apt-get install libboost-all-dev"
  - Libcurl library - For ubuntu run "sudo apt-get install libcurl4 libcurl4-openssl-dev -y"
  - Meson build tool (https://mesonbuild.com/Quick-guide.html)

 Run tests:
  -  Create build directory inside root directory
  -  Navigate to build directory  
  -  Run the following commands:
      - meson ..
      - ninja
      - ./test/TddSessionTests
        or use filter options for example: 
          ./test/TddSessionTests --gtest_filter=APortfolio* 
        to run APortfolio test Suit

