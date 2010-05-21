
cmake_minimum_required(VERSION 2.8)

project(keypers)

add_executable(keypers
  config.cc
  defaults.cc
  keypers.cc
  log.cc
  storage.cc
  handler.cc
  counter.cc

  config.hh
  defaults.hh
  keypers.hh
  log.hh
  storage.hh
  handler.hh
  counter.hh
  
  ../thrift/gen-cpp/Keyper.cpp
  ../thrift/gen-cpp/Server.cpp
  
  ../thrift/gen-cpp/keyper_types.cpp
  ../thrift/gen-cpp/server_types.cpp
)

include_directories(
  /usr/local/include/thrift
  /usr/local/include/xapian
  ../thrift/gen-cpp
)

target_link_libraries(keypers
  thrift
  xapian
  kyotocabinet
  z
  stdc++
  rt
  pthread
  m
  c
)
