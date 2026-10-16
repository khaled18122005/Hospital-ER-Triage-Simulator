cmake_minimum_required(VERSION 3.8)
project(Hospital-ER-Triage-Simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(HospitalSimulator src/main.cpp Models/HospitalSimulator.cpp)