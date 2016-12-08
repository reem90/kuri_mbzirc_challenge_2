#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/PointCloud.h>





void center_cloud_cb(const sensor_msgs::PointCloud::ConstPtr& inMsg)
{

   
     if (inMsg->points.size()>0)
     {
ros::Time now = ros::Time(0);
    sensor_msgs::PointCloud cloud_in;
    cloud_in.header.stamp = inMsg->header.stamp;
    cloud_in.header.frame_id = inMsg->header.frame_id;
    cloud_in.points=inMsg->points;
 



         //center_cloud.points.resize(sifted_centroid_list.size()); 
         //one_centroid=sifted_centroid_list[0];
         std::cout<<"centroids are:"<<std::endl;
         std::cout<<inMsg->points[0].x<<std::endl;   
         tf::StampedTransform transform; 
         tf::TransformListener listener; 

         
         //ros::Time now = ros::Time::now();


         ros::Duration(2).sleep();


         listener.waitForTransform("/base_link","/velodyne",now,ros::Duration(0.0));
         listener.lookupTransform("/base_link","/velodyne",now,transform);
         sensor_msgs::PointCloud gobal;
         
         //cloud_in=*inMsg;
         try {
        //listener.transformPointCloud("/base_link",cloud_in, gobal);

        listener.transformPointCloud("/base_link",now,cloud_in, "/velodyne",gobal);

        std::cout<<"New centroids are:"<<std::endl;
        std::cout<<gobal.points[0].x<<std::endl;
                 } catch (tf2::ExtrapolationException &ex){
               
//std::cout<<ex.msg<<std::endl;
//continue;
        }
 








     }






}


int main(int argc, char** argv){
  ros::init(argc, argv, "tf_listener");

  ros::NodeHandle node;
  ros::Subscriber input=node.subscribe("center_cloud",10, center_cloud_cb);




  tf::StampedTransform transform; 
  tf::TransformListener listener;
   
  //listener.lookupTransform("/velodyne","/bask_link",ros::Time(0),transform);
  //std::cout << transform.stamp << std::endl; 


  //ros::Rate rate(10.0);
  ros::spin();
  return 0;
};
