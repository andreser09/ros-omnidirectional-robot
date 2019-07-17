#include "k_model.h"
#include "ros/console.h"

namespace k_model
{

k_model_publisher::k_model_publisher() :
	
	nh(ros::NodeHandle()),
	nh_private(ros::NodeHandle("~"))

	{
	nh_private.param<double>("carcatbot_lenght", a_coordinate, 10.25);
	nh_private.param<double>("carcatbot_width", b_coordinate, 7.25);
	nh_private.param<double>("carcatbot_wheel_radius", wheel_radius, 2.7);
	teleop_sub = nh.subscribe("/cmd_vel", 1, &k_model_publisher::teleop_callback, this);
	k_model_pub = nh.advertise<k_model::vel_motors>("k_model_topic", 1);
	}

	void k_model_publisher::teleop_callback(const geometry_msgs::Twist &vel)
	{
		float x, y, theta;
		x = vel.linear.x;
		y = vel.linear.y;
		theta = vel.angular.z;
		PWM_1 = calculate_k_model(-1, 1, 1, x, y, theta);
		PWM_2 = calculate_k_model(1, 1, -1, x, y, theta);
		PWM_3 = calculate_k_model(-1, 1, -1, x, y, theta);
		PWM_4 = calculate_k_model(1, 1, 1, x, y, theta);
		k_model::vel_motors msg;
		msg.vel_1 = PWM_1;        
		msg.vel_2 = PWM_2;
		msg.vel_3 = PWM_3;
		msg.vel_4 = PWM_4;
		k_model_pub.publish(msg);
	}

}