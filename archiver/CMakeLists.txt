cmake_minimum_required(VERSION 3.20)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(archiver main.cpp "lib/WorkWithBitsEncode.h" "lib/WorkWithBitsDecode.h" lib/EncodeFiles.h lib/HuffmanTree.h lib/DecodeArchive.h lib/StructEncodedSymbol.h lib/HuffmanTree.cpp "lib/WorkWithBitsEncode.cpp" lib/EncodeFiles.cpp lib/DecodeArchive.cpp "lib/WorkWithBitsDecode.cpp" lib/BitsReader.cpp lib/BitsReader.h lib/BitsWriter.cpp lib/BitsWriter.h lib/ConstForWriterAndReader.h)
