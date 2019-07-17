#include "ros/ros.h"
#include "k_model/vel_motors.h"
#include "geometry_msgs/Twist.h"

namespace k_model

{

class k_model_publisher
{
	//Constructor & Destructor

	public:
	k_model_publisher();
//	~k_model_publisher();

	private:

	//NodeHandle
	ros::NodeHandle nh;
	ros::NodeHandle nh_private;

	//Publishers and subscribers
	ros::Subscriber teleop_sub;
	ros::Publisher k_model_pub;

	//Parameters
	double a_coordinate;
	double b_coordinate;
	double wheel_radius;

	//State variables
	float PWM_1;
	float PWM_2;
	float PWM_3;
	float PWM_4;

	enum proper_speed{fine, wrong};
	
	proper_speed proper_s;

	//Callbacks
	
	void teleop_callback(const geometry_msgs::Twist &vel);

	//Functions

	proper_speed check_proper_speed(float vel)
	{
	if (vel < 100.0) {return fine;}
	else {return wrong;}
	}

	float map_speed(float vel)
	{
		proper_s = check_proper_speed(vel);
		switch (proper_s) 
		{
		case fine:
			vel = (vel*400)/100;
			break;
		case wrong:
			vel=vel;
			break;    
  		}
		return vel;
	}

	float calculate_k_model(int x11, int x12, int x13, float x, float y, float theta)
	{
		float PWM_out;
		PWM_out = (x11/wheel_radius)*x+(x12/wheel_radius)*y+(((x13*(a_coordinate + b_coordinate))/wheel_radius)*theta);
		PWM_out = map_speed(PWM_out);
		return PWM_out;
	}

};	

}