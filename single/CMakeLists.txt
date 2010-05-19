
cmake_minimum_required(VERSION 2.8)

project(keypers)

add_executable(keypers
  config.cc
  defaults.cc
  keypers.cc
  log.cc
  storage.cc

  config.hh
  defaults.hh
  keypers.hh
  log.hh
  storage.hh
)

include_directories(
  ../thrift/gen-cpp
)

target_link_libraries(keypers
  pthread
  thrift
  xapian
)
