//
// Created by oem on 24. 7. 25..
//

#include "vicon.hpp"

Vicon::Vicon(std::string host_address, int buffer_size): host_address_(host_address), buffer_size_(buffer_size) {

}

void Vicon::initVicon() {
  while (!client_.IsConnected().Connected) {
    std::cout << "Connecting" << std::endl;
    client_.Connect(host_address_);
  }

  client_.EnableSegmentData();
  client_.EnableMarkerData();
  if (client_.EnableMarkerData().Result != ViconDataStreamSDK::CPP::Result::Success) {
    throw std::runtime_error("Failed to enable marker data.");
  }
  if (client_.EnableSegmentData().Result != ViconDataStreamSDK::CPP::Result::Success) {
    throw std::runtime_error("Failed to enable segment data.");
  }
  client_.SetStreamMode(StreamMode::ServerPush);
  client_.SetBufferSize(buffer_size_);
}

void Vicon::initData() {

}

void Vicon::viconUpdate() {
  auto Output = client_.GetFrame();
  if(Output.Result == Result::Success)
  {
    Output_GetFrameNumber frame_number = client_.GetFrameNumber();
    unsigned int subject_num = client_.GetSubjectCount().SubjectCount;
    for (unsigned int subject_idx = 0; subject_idx < subject_num; subject_idx++) {
      std::string subject_name = client_.GetSubjectName(subject_idx).SubjectName;
      unsigned int segment_num = client_.GetSegmentCount(subject_name).SegmentCount;
      std::string segment_name = client_.GetSegmentName(subject_name, 0).SegmentName;
      Output_GetTimecode outputTimeCode = client_.GetTimecode();
      Output_GetFrameRate outputFrameRate = client_.GetFrameRate();
      Output_GetSegmentGlobalTranslation trans =
          client_.GetSegmentGlobalTranslation(subject_name, segment_name);
      Output_GetSegmentGlobalRotationMatrix rot =
          client_.GetSegmentGlobalRotationMatrix(subject_name, segment_name);
      Output_GetSegmentGlobalRotationQuaternion quat =
          client_.GetSegmentGlobalRotationQuaternion(subject_name, segment_name);

      double timeStamp = outputTimeCode.Hours * 1e6 + outputTimeCode.Minutes * 1e3 + outputTimeCode.Seconds;
      std::cout << "Subject: " << subject_name << ", Segment: " << segment_name << ", Translation: "
                << trans.Translation[0] << ", " << trans.Translation[1] << ", " << trans.Translation[2] << std::endl;
    }
  }
}


