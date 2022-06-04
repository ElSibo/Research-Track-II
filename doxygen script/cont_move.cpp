/**
* \file cont_move.cpp
* \brief this script it makes the robot change speed or turn 
* \brief (left or right) according to the data it receives from the /vel cont
* \author Bouazza   EL Moutaouakil
* \version 1.0
* \date 14\05\2022
*
* \details
*
* \param a,b,z Global variable for registered velocity,(z) and activate (or not) assistent control
*
* Publisher: <BR>
*	
*   ros::Publisher pub1;
* 
* \param pub1 publishing on /cdm_vel
*
* Subscriber: <BR>
*	
*   ros::Subscriber sub2
* 
* \param sub2 receving data from /vel_cont abot velocity
*
* ° ros::Subscriber sub
*
* \param sub receving data from /scan (laser_scaner) about distance from the obstacle
*
*
*
* Description:
*
*this node is a communication bridge between 
*the simulator (/ gazebo), sending the speed 
*continuously and receiving the distance 
*from the otacles with the laser scaner,
*and node / navi_rob_goal, which is the user interface node
*
**/



#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Point32.h"
#include "geometry_msgs/Twist.h"


using namespace std;
float a, b,z;
ros::Publisher pub1;

/**
* \brief callback function for read velocity desidered
* \param msg registered the data from /vel_cont
* \void function 
*
* Description:
* This function read the velocity of the robot, 
* his orientation that user are imposed and 
* if he are turn on/off assistant control  
*
**/
void vel(const geometry_msgs::Point32::ConstPtr& msg){

	a=msg->x;
	b=msg->y;
	z=msg->z;
}
/**
* \brief callback function for setting velocity
* \param msg registered the data from /scan
* \param pub pulishing the data to /cmd_vel 
* \void function 
*
* Description:
* This function after reading the data from laser 
* set the velocity of the robot, and if the case 
* assistent controll are activate stop the robot 
* in the direction of the obstacle if it's close
* to the obstacle 
*
**/
void assistContr(const sensor_msgs::LaserScan::ConstPtr& msg){
	float Rt=0,ft=0,Lt=0;
	
	
	
	for(int i=0;i<260;i++){ Rt = Rt + msg->ranges[i]; }
	//do the average for all right data
	Rt= Rt/260;
	//cout<<"right : "<<Rt<<endl;
	
	for(int i=280;i<440;i++){ ft = ft + msg->ranges[i]; }
	//do the average for all front data
	ft= ft/200;
	//cout<<"front :        "<<ft<<endl;
	
	for(int i=460;i<720;i++){ Lt = Lt + msg->ranges[i]; }
	//do the average for all left data
	Lt= Lt/260;
	//cout<<"left :  "<<Lt<<endl;
	
	if(z>=2.0){
	if (ft<0.5 & a>0){ a=0; }
	if (Rt<0.7 & b>0){ b=0; }	//attivation of assistent controller
	if (Lt<0.7 & b<0){ b=0; }}
	if(z>0){
	geometry_msgs::Twist my_vel;
	my_vel.linear.x =a;
	my_vel.angular.z = b;  	//publication on cdm_vell the velocity(linear and angular) of the robot
	pub1.publish(my_vel);}		//if z<0 that mean the go_to_point active



}


ros::Publisher pub; //declared the pulisher for the same reason 
/**
* \brief main function
* 
* \param argc
* \param argv
* \param init defined the node contmove_rob
* \param nn2 defined the nodehandler 
* \param pub1 defined the publisher
* \param sub2, sub defined the publisher
*
*
* \return always 0
*
* Description:
* the main function initializes the node,
* the publisher, the subscriber and start 
* a endless loop that read continusly the choise
* of the user and publishing it on /cmd_vel  
**/

int main(int argc, char **argv){ //main
	
	
	
	ros::init(argc,argv,"contmove_rob"); // defined the node contmove_rob
	ros::NodeHandle nn2;	//defined the nodehandler  
	pub1 = nn2.advertise<geometry_msgs::Twist>("/cmd_vel",1);//defined the pulisher
	
	while(ros::ok()){
	
	ros::Subscriber sub2 = nn2.subscribe("/vel_cont",1,vel); //defined and callingthe subscriber
	ros::Subscriber sub = nn2.subscribe("/scan",1,assistContr);
	ros::spin();
	}
	
	return 0;
	
}

