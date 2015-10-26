/*
 * Copyright (c) 2015, Mina  Kamel, ASL, ETH Zurich, Switzerland
 * You can contact the author at <mina.kamel@mavt.ethz.ch>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * created on Sep 30, 2015 5:00:11 AM
 */

#include <royale/CameraManager.hpp>
#include <iostream>
#include <ros_picoflexx/ros_picoflexx.h>
#include <memory>

PicoFlexxCamera::PicoFlexxCamera(royale::CameraManager& _manager, std::string _camera_name)
    : manager_(_manager),
      camera_name_(_camera_name)
{

}

PicoFlexxCamera::~PicoFlexxCamera()
{

}

void PicoFlexxCamera::Initialize()
{
  //read ros parameters
  nh_ = ros::NodeHandle("~/" + camera_name_);

  nh_.param < std::string > ("camera_id", camera_id_, "0005-1203-0034-1816");
  nh_.param<int>("exposure_time", exposure_time_, 2000);
  nh_.param<bool>("auto_exposure_time", auto_exposure_time_, true);
  nh_.param < std::string > ("operation_mode", operation_mode_, "MODE_9_5FPS_2000");

  std::vector < std::string > camlist = manager_.getConnectedCameraList();
  for (int i = 0; i < camlist.size(); i++) {
    if (camlist[i] == camera_id_) {
      camera_device_ = manager_.createCamera(camlist[i]);
      ROS_INFO_STREAM(camera_name_ << " initialized correctly");
    }
  }

  if (camera_device_->initialize() != royale::CameraStatus::SUCCESS) {
    ROS_ERROR("Cannot initialize the camera device");
    return;
  }
  royale::LensParameters lensParams;
  camera_device_->getLensParameters (lensParams);

  // display some information about the connected camera
  std::cout << "====================================" << std::endl;
  std::cout << "        Camera information" << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << "Id:              " << camera_device_->getId() << std::endl;
  std::cout << "Type:            " << (int) camera_device_->getCameraType() << std::endl;
  std::cout << "Width:           " << camera_device_->getMaxSensorWidth() << std::endl;
  std::cout << "Height:          " << camera_device_->getMaxSensorHeight() << std::endl;
  std::cout << "Operation modes: " << camera_device_->getOperationModes().size() << std::endl;
  std::cout << "Focal Length  fx: " << lensParams.focalLength.first << std:endl;
  std::cout << "Focal Length  fy: " << lensParams.focalLength.second << std::endl;
  std::cout << "Principal Pt. px: " << lensParams.principalPoint.first << std::endl;
  std::cout << "Principal Pt. py: " << lensParams.principalPoint.second << std::endl;
  std::cout << "Dist. Coeff k1:   " << std::get<0>(lensParams.distortionRadial) << std::endl;
  std::cout << "Dist. Coeff k2:   " << std::get<1>(lensParams.distortionRadial) << std::endl;
  std::cout << "Dist. Coeff k3:   " << std::get<2>(lensParams.distortionRadial) << std::endl;
  std::cout << "Dist. Coeff p1:   " << lensParams.distortionTangential.first << std::endl;
  std::cout << "Dist. Coeff p2:   " << lensParams.distortionTangential.second << std::endl;

  for (auto mode : camera_device_->getOperationModes()) {
    std::cout << "    " << royale::getOperationModeName(mode) << std::endl;
  }

  // set an operation mode
  updateOperationMode();

  //set exposure settings
  //updateExposureSettings();

  config_service_ = nh_.advertiseService("config", &PicoFlexxCamera::configCameraCallback, this);

  thread_ = std::thread(&PicoFlexxCamera::startAcquisition, this);
}

bool PicoFlexxCamera::startAcquisition()
{
  DepthDataListener listener(camera_name_);
  camera_device_->registerDataListener(&listener);

  // start capture mode
  camera_device_->startCapture();

  ros::waitForShutdown();

  if (camera_device_->isCapturing()) {
    camera_device_->stopCapture();
    std::cout << "Stop capturing..." << std::endl;
  }
  camera_device_->unregisterDataListener();
  camera_device_->stopRecording();
}

void PicoFlexxCamera::updateOperationMode()
{
  royale::CameraStatus operation_mode_set = royale::CameraStatus::OPERATION_MODE_NOT_SUPPORTED;
  for (auto mode : camera_device_->getOperationModes()) {
    if (royale::getOperationModeName(mode) == operation_mode_) {
      ROS_INFO_STREAM(" Setting Operaton Mode to:   " << royale::getOperationModeName(mode));
      operation_mode_set = camera_device_->setOperationMode(mode);
    }
  }

  if (operation_mode_set != royale::CameraStatus::SUCCESS) {
    ROS_WARN("Operation mode not supported. Setting default operation mode.");
  }
}

void PicoFlexxCamera::updateExposureSettings()
{

  royale::CameraStatus status;
  status = camera_device_->setExposureMode(royale::ExposureMode(auto_exposure_time_));

  if (status != royale::CameraStatus::SUCCESS) {
    ROS_WARN_STREAM("Exposure mode error : " << (int) status);
    return;
  }
  if (camera_device_->getExposureMode() == royale::ExposureMode::AUTOMATIC) {
    ROS_INFO("Automatic exposure time is selected.");
  } else {
    ROS_INFO("Manual exposure time is selected.");
    status = camera_device_->setExposureTime((uint32_t) exposure_time_);
    if (status != royale::CameraStatus::SUCCESS) {
      ROS_WARN_STREAM("Exposure mode error : " << (int) status);
    }
  }
}

bool PicoFlexxCamera::configCameraCallback(ros_picoflexx::PicoFlexxConfig::Request &req,
                                           ros_picoflexx::PicoFlexxConfig::Response &res)
{
  operation_mode_ = req.operation_mode;
  updateOperationMode();
  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "picoflexx");

  ros::NodeHandle nh("");
  royale::CameraManager manager;

  std::vector < std::shared_ptr < PicoFlexxCamera >> picoflexx_cameras_vector;

  //get cameras list
  std::vector < std::string > camlist;
  int attempts = 5;

  ROS_INFO("Detecting cameras...");

  do {
    ros::Duration(1).sleep();
    camlist = manager.getConnectedCameraList();
    attempts--;
  } while (camlist.empty() & attempts > 0);

  std::cout << "Detected " << camlist.size() << " camera(s)." << std::endl;

  if (camlist.empty()) {
    ROS_ERROR("No PicoFLexx cameras detected.. aborting");
    return 1;
  }

  for (int i = 0; i < camlist.size(); i++) {
    std::shared_ptr<PicoFlexxCamera> tmp;
    picoflexx_cameras_vector.push_back(tmp);
    picoflexx_cameras_vector.back().reset(new PicoFlexxCamera(manager, "cam" + std::to_string(i)));

    picoflexx_cameras_vector.back()->Initialize();
  }

  ros::AsyncSpinner spinner(4);  // Use 4 threads
  spinner.start();
  ros::waitForShutdown();

}

