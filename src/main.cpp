//
// Created by oem on 24. 7. 25..
//

#include "vicon.hpp"
#include "thread"
#include <csignal>
#include <atomic>

std::atomic<bool> keep_running(true);

void signal_handler(int signal) {
  if (signal == SIGINT) {
    keep_running = false;
  }
}

int main() {
  std::string host_address = "";
  int buffer_size = 10;
  Vicon vicon(host_address, buffer_size);
  vicon.initVicon();
  vicon.initData();

  while (keep_running) {
    vicon.viconUpdate();
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Adjust the sleep duration as needed
  }

  std::cout << "Terminating Vicon update loop." << std::endl;

  return 0;
}