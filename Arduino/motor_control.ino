#include <ros.h>
#include <vel_motors.h>
#include <MotorDC.h>

MotorDC m1;
MotorDC m2;
MotorDC m3;
MotorDC m4;

// Declaracion de pines para el PWM
int motFrontalizquierdo_PWM = 5;
int motFrontalderecho_PWM = 6;
int motTraseroizquierdo_PWM = 7;
int motTraseroderecho_PWM = 8;

// Declaracion de pines de direccion en sentido horario*/
int motFrontalizquierdo_A0 = 22;
int motFrontalderecho_A0 = 24;
int motTraseroizquierdo_A0 = 26;
int motTraseroderecho_A0 = 28;

// Declaracion de pines para direccion en sentido antihorario*/
int motFrontalizquierdo_A1 = 30;
int motFrontalderecho_A1 = 31;
int motTraseroizquierdo_A1 = 32;
int motTraseroderecho_A1 = 33;

ros::NodeHandle nh;

void velCallback(const k_model::vel_motors& msg)
{
  m1.setSpeed(msg.vel_1);
  m2.setSpeed(msg.vel_2);
  m3.setSpeed(msg.vel_3);
  m4.setSpeed(msg.vel_4);
}

ros::Subscriber<k_model::vel_motors> sub("/cmd_vel", velCallback);

void setup()
{
  m1.connectMotor( 5, motFrontalizquierdo_A0 , motFrontalizquierdo_A1);
  m2.connectMotor( 6, motFrontalderecho_A0, motFrontalderecho_A1);
  m3.connectMotor( 7, motTraseroizquierdo_A0 , motTraseroizquierdo_A1);
  m4.connectMotor( 8, motTraseroderecho_A0, motTraseroderecho_A1);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}