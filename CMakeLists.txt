cmake_minimum_required(VERSION 3.20)
project(Assignment_Grp_Intelligent)

set(CMAKE_CXX_STANDARD 14)

# This tells the compiler to treat all your files as one executable
add_executable(Assignment_Grp_Intelligent
        main.cpp
        Account.cpp
        SearchAcc.cpp
        Transaction.cpp
)