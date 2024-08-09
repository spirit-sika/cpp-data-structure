cmake_minimum_required(VERSION 3.28)
project(SikaLinkedList)

set(CMAKE_CXX_STANDARD 17)

add_executable(SikaLinkedList
        SikaLinkedList.h
        SikaSinglyLinkedList.h
        Person.h
        IntegerArray.h
        SikaStack.h
        SikaQueue.h
        PointerAndReference.hpp
        SikaTree.cpp
        SikaTree.h
        SikaBinaryTree.cpp
        SikaBinaryTree.h
        tree_by_gpt.cpp
        main.cpp
)
