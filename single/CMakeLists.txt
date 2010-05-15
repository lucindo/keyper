
cmake_minimum_required(VERSION 2.8)

project(keypers)

add_executable(keypers
  config.cc
  defaults.cc
  keypers.cc
  log.cc
  storage.cc
  server.cc
  connection.cc
  request_handler.cc
  reply.cc
  request_parser.cc

  config.hh
  defaults.hh
  keypers.hh
  log.hh
  storage.hh
  server.hh
  connection.hh
  request_handler.hh
  request.hh
  reply.hh
  request_parser.hh
)

target_link_libraries(keypers
  pthread
  boost_thread
  boost_system
  boost_program_options
  xapian
)
