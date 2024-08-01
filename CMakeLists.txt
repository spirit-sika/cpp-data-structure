cmake_minimum_required(VERSION 3.28)
project(SikaLinkedList)

set(CMAKE_CXX_STANDARD 17)

add_executable(SikaLinkedList main.cpp
        SikaLinkedList.h
        SikaSinglyLinkedList.h
        Person.h
        IntegerArray.h
        SikaStack.h
        SikaQueue.h
        PointerAndReference.hpp
)
