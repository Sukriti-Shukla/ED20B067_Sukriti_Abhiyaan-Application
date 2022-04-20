#include "ros/ros.h"
#include "std_msgs/String.h"
#include "bits/stdc++.h"
using namespace std;

std_msgs::String s;
std_msgs::String str2;
std_msgs::String str_rev(std_msgs::String str)
{
 std_msgs::String temp;
 temp.data = str.data;
 for(int i=0;i<temp.data.length();++i)
 {
    str.data[i]=temp.data[temp.data.length()-i-1];
 }
 return str;
 }
 
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
 
 s.data=msg->data.c_str();
 std_msgs::String str; str2.data="";
 str.data="";
 str2=str_rev(s);
 
} 

int main(int argc, char **argv)
{
ros::init(argc, argv, "listener2");
 ros::NodeHandle n;
 ros::Subscriber sub = n.subscribe("team_abhiyaan", 1, chatterCallback);
 //
 ros::Publisher chatter_pub2 = n.advertise<std_msgs::String>("/naayihba_maet",1);

 ros::Rate loop_rate(1);
 while(ros::ok())
 {
 
 ROS_INFO("%s", str2.data.c_str());
 chatter_pub2.publish(str2);
 ros::spinOnce();
 loop_rate.sleep();
 }
 //
 ros::spin();
 return 0;
 }
