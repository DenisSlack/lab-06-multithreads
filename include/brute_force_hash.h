// Copyright 2020 Stitch

#include <picosha2.h>

#include <boost/log/trivial.hpp>
#include <iostream>
#include <string>
#include <thread>

struct data {
  std::string all;
  std::string hash;
  std::string end;
};

class FinderHash {
 public:
  FinderHash();
  static void find();  // может вызываться без объекта
};

void FinderHash::find() {
  auto id = std::this_thread::get_id();
  data temp;
  while (true) {
    temp.all = std::to_string(std::rand());
    temp.hash = picosha2::hash256_hex_string(temp.all);
    temp.end = temp.hash.substr(60);
    if (temp.end == "0000")
      BOOST_LOG_TRIVIAL(info) << " Thread id- " << id << " Data: " << temp.all
                              << " Desired Hash: " << temp.hash;
    else
      BOOST_LOG_TRIVIAL(trace) << "Thread id- " << id << " Data: " << temp.all
                               << " Hash: " << temp.hash;
  }
}
FinderHash::FinderHash() {}
