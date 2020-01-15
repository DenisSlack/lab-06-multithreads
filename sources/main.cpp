// Copyright 2020 Stitch
#include <boost/log/utility/setup.hpp>
#include <iostream>
#include <vector>

#include "../include/brute_force_hash.h"

int main(int argc, char* argv[]) {
  size_t num_thread = std::thread::hardware_concurrency();
  if (argc > 1) num_thread = boost::lexical_cast<size_t>(argv[1]);

  auto file = boost::log::add_file_log("logs/log.log");
  file->set_filter(boost::log::trivial::severity >=
                   boost::log::trivial::trace);  // trace пускаем в файл,
                                                 // фильтрация логирования
  auto console = boost::log::add_console_log(std::cout);
  console->set_filter(boost::log::trivial::severity >=
                      boost::log::trivial::info);  // info пускаем в консоль,
                                                   // фильтрация логирования

  std::vector<std::thread> threads;
  for (size_t i = 0; i < num_thread; i++)
    threads.emplace_back(FinderHash::find);
  for (std::thread& th : threads) {
    th.join();
  }

  return 0;
}
