#ifndef CART_TRAJECTORY_IMPEDANCE_CONTROLLER_HPP
#define CART_TRAJECTORY_IMPEDANCE_CONTROLLER_HPP

#include <algorithm>

// #include "ohrc_automation/cart_trajectory_controller.hpp"
#include "ohrc_automation/impedance_controller.hpp"
#include "ohrc_msgs/GetTrajectories.h"

class CartTrajectoryImpedanceController : public ImpedanceController {
  ros::ServiceClient client;
  std::vector<moveit_msgs::CartesianTrajectory> _trjs;
  bool _flagTrjs = false;
  int targetIdx = 0;
  int nTrjs = 0;

  moveit_msgs::CartesianTrajectory trj;
  bool updateTrjs = true;

  int t_i = 0;
  int forward = 1;  // -1: rest, 1: target

  bool updateImpedanceTarget(const VectorXd& x, VectorXd& xd) override;

  void setSubscriber() override final {
    // CartTrajectoryController::setSubscriber();
    ImpedanceController::setSubscriber();
  };

  void cbTargetPoses(const geometry_msgs::PoseArray::ConstPtr& msg) override final;

  bool getTrajectories(const geometry_msgs::PoseArray& targetPoses, std::vector<moveit_msgs::CartesianTrajectory>& trjs);

public:
  // using CartTrajectoryController::CartTrajectoryController;
  using ImpedanceController::ImpedanceController;

  void initInterface() override final;

  void updateTargetPose(KDL::Frame& pose, KDL::Twist& twist) override final {
    ImpedanceController::updateTargetPose(pose, twist);
  };
};

#endif  // CART_TRAJECTORY_IMPEDANCE_CONTROLLER_HPP
