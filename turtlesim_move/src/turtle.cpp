/* Section A task 3 */
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "iostream"
#include "cmath"
#include "cstdlib"

float turtle1_x, turtle1_y, turtle2_x, turtle2_y;

void turtle1_pose(const turtlesim::Pose::ConstPtr& pos)
{
  //getting x,y from topic turtle1/pose
  turtle1_x = pos->x;
  turtle1_y = pos->y;
  
}

void turtle2_pose(const turtlesim::Pose::ConstPtr& pos)
{
  //getting x,y from topic turtle2/pose
  turtle2_x = pos->x;
  turtle2_y = pos->y;
  
  
}

int main(int argc, char **argv)
{
  float m1 = 0, m2 = 0;float x1,x2,y1,y2;
  std::cout << "Enter mass of turtle 1 : "; 
  std::cin >> m1;
  std::cout << "Enter x coordinate of turtle 1 : ";
  std::cin >> x1;
  std::cout << "Enter y coordinate of turtle 1 : ";
  std::cin >> y1;
  std::cout << "Enter mass of turtle 2: "; 
  std::cin >> m2;
  std::cout << "Enter x coordinate of turtle 2 : ";
  std::cin >> x2;
  std::cout << "Enter y coordinate of turtle 2 : ";
  std::cin >> y2;
  
  ros::init(argc, argv, "turtle");

  ros::NodeHandle n;
  //creating variables for publishing velocity of turtle 1 and 2 
  ros::Publisher turtle2_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 100);
  ros::Publisher turtle1_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);
  //creating variables for subscribing to get turtle 1 & 2 postion
  ros::Subscriber turtel1_pose_sub = n.subscribe<turtlesim::Pose>("/turtle1/pose", 100, turtle1_pose);
  ros::Subscriber turtel2_pose_sub = n.subscribe<turtlesim::Pose>("/turtle2/pose", 100, turtle2_pose);

  ROS_INFO("%f %f : %f %f", x1,y1,x2,y2);
  ros::Rate loop_rate(10);
  while (ros::ok())
  { 
  /* In this solution we have assumed initial velocity of turtle 1 and 2 to be 0, and G=1
     r1 is the distance of turtle1 from COM of both turtles
     r2 is the distance of turtle2 from COM of both turtles,
     r1x r2x r1y r2y are x and y components of the distances
     Now the COM of the system will remain stationary and both turtles will revolve around it 
     with radius r1 and r2.
     Hence, by using gravitation concepts I have calculated the value of tangential and angular velocity for 
     both the turtles while revolving around COM */
     
    float r1x,r1y,r2x,r2y,r1,r2;
    geometry_msgs::Twist vel;
    geometry_msgs::Twist vel1;
    r1x=(m2/(m1+m2))*abs(x1-x2);
    r1y=(m2/(m1+m2))*abs(y1-y2);
    r2x=(m1/(m1+m2))*abs(x1-x2);
    r2y=(m1/(m1+m2))*abs(y1-y2);
    r1=sqrt(r1x*r1x+r1y*r1y);
    r2=sqrt(r2x*r2x+r2y*r2y);
    vel.linear.y=sqrt(r1*m2/(pow((r1+r2),2)));
    vel.linear.x=0;
    vel1.linear.y=-1*sqrt(r2*m1/(pow((r1+r2),2)));
    vel1.linear.x=0;
    
    vel.linear.z = 0.0;
    vel.angular.x = 0.0;
    vel.angular.y = 0.0;
    vel.angular.z = -1*sqrt(r1*m2/(pow((r1+r2),2)))/r1;
    vel1.linear.z = 0.0;
    vel1.angular.x = 0.0;
    vel1.angular.y = 0.0;
    vel1.angular.z = -1*sqrt(r2*m1/(pow((r1+r2),2)))/r2;
    ROS_INFO("%f %f ", vel.angular.z,vel.angular.z);
    turtle1_vel_pub.publish(vel);
    turtle2_vel_pub.publish(vel1);

    ros::spinOnce();

    loop_rate.sleep();
  }

}

