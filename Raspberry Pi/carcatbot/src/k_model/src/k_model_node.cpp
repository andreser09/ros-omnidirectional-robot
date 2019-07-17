#include "ros/ros.h"
#include "k_model.h"

int main(int argc, char **argv)
{
ros::init(argc, argv, "k_model_node");
ros::NodeHandle n;

k_model::k_model_publisher k_publisher_inst;

ros::spin();

return 0;

}
