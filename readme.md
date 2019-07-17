# ros-omnidirectional-robot

*Building a ROS controlled omnidirectional robot with four mechanum wheels*

<p  align="center">
<img src="https://user-images.githubusercontent.com/35426709/61414489-79adcb00-a8c4-11e9-80f2-bca2f4627ea2.jpg" width="300"> </p>

This repository contains the files of a little ROS project done for the Mechatronics Lab of the National University of San Luis (Argentina) over an internship.

The project consisted in developing and controling an omnidirectional robot with four mechanum wheels. Using an arduino mega and a raspberry pi alongside with drivers and some 3d printed parts the idea was to be able to turn and twist the robot over wifi with a computer running a ROS master with the kinematic model of the robot.

This project was implemented but remains unfinished. The original idea was to use some sensor for speed feedback and control because the pololus didn't have encoder and also there is no proper dc power for the raspberry in the design (we used a portable battery).


## Hardware

* Mecanum wheels x4
	* All Metal Construction
	* Anodized Aluminum Hubplates
	* EPDM Rubber Rollers
	* Outside Wheel Diameter: 54mm
	* Wheel Width at Widest Point: 34mm
	* Mount Bore: 3mm
* 50:1 Metal Gearmotor 37Dx54L mm x4
* 2200mAh 11.1V 3S 20C Lipo Pack Battery
* Arduino Mega 2560
* Driver LM298
* Raspberry Pi Model 3B+
* 3d printed parts:
	* Motor housing and coupling
	* Arduino, battery, drivers and raspberry mounting

## Software

### Raspberry Pi

The raspberry pi runs a ros master with two nodes: one for the teleoperation (twist message) with the computer and the other calculates the pwm for each motor, which is recieved in a custom defined message by a node in the arduino.

<p  align="center">
<img src="https://user-images.githubusercontent.com/35426709/61414609-c2658400-a8c4-11e9-9a12-db4b07f07e16.jpg" width="600"> </p>

####Requirements and installation process

* Install Raspbian on the raspberry

	<https://www.raspberrypi.org/downloads/raspbian/>

* Install ROSberry (kinetic)

	<http://wiki.ros.org/ROSberryPi/Installing%20ROS%20Kinetic%20on%20the%20Raspberry%20Pi>
	
* Build the workspace
* Install the Arduino IDE

	`sudo apt-get install arduino-core arduino`

* Run arduino once so the sketch/libraries are created
* Install the common-msgs package in the /workspace/src

	<https://github.com/ros/common_msgs>

* Install rosserial in the /workspace/src

	<https://github.com/ros-drivers/rosserial.git>
	
* Install py-serial for communication between the raspberry and the arduino (reading/writing permissions needed and set the baud rate)

	`sudo apt-get install python-serial`

	
### Arduino

To create ros nodes on the arduino the ros.h file needs to be loaded in the libraries folder of the arduino (usually /sketches/libraries).
That is accomplished doingg the following on th pi terminal

`ros rosserial_arduino make_libraries.py <sketchbook>/libraries`

Check out the [&lt;rosserial&gt;](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup) documentation

## Setup

If the last steps worked out properly now the k\_model node can be built. The msg definition (vel\_motors.msg) and the node files are in the src of the k\_model folder.

Via catkin_make or build the rest of the files are generated and the node should be functional.

In order to communicate with the arduino so its node can understand the vel\_motors.msg the vel_motors.h (generated automatically and located in the install folder of the workspace) needs to be added to the arduino libraries folder.

Loading the motor_control.ino to the arduino and connecting it over serial to the raspberry pi is the last step.

Connected over ssh to the raspberry pi run `roscore` and the rosrun the nodes.
