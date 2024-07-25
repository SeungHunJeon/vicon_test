//
// Created by oem on 24. 7. 25..
//

#ifndef VICON_EXAMPLE_INCLUDE_VICON_HPP_
#define VICON_EXAMPLE_INCLUDE_VICON_HPP_

#endif //VICON_EXAMPLE_INCLUDE_VICON_HPP_

#include <string>
#include <iostream>
#include "DataStreamClient.h"

using namespace ViconDataStreamSDK::CPP;
class Vicon
{
 public:
  Vicon(std::string host_address, int buffer_size);

  void initVicon();

  void viconUpdate();

  void initData();

 private:
  ViconDataStreamSDK::CPP::Client client_;
  std::string host_address_;
  int buffer_size_;
};