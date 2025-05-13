#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

// 全局变量，用于存储接收到的IMU数据
sensor_msgs::Imu imu_msg;
// 标志位，用于判断是否接收到新的IMU数据
bool new_imu_data = false;

// 回调函数，处理接收到的IMU数据
void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    // 复制接收到的IMU数据
    imu_msg = *msg;
    // 修改frame_id
    imu_msg.header.frame_id = "imu_link";
    // 设置标志位，表示接收到新的数据
    new_imu_data = true;
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "vectornav");
    // 创建ROS节点句柄
    ros::NodeHandle nh;

    // 创建订阅者，订阅/mavros/imu/data话题
    ros::Subscriber imu_sub = nh.subscribe("/mavros/imu/data", 1000, imuCallback);
    // 创建发布者，发布/vectornav/imu话题，队列长度为10
    ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("/vectornav/imu", 1000);

    // 设置发布频率为40Hz
    ros::Rate rate(40);

    while (ros::ok())
    {
        // 处理ROS回调
        ros::spinOnce();

        // 如果接收到新的IMU数据
        if (new_imu_data)
        {
            // 发布修改后的IMU数据
            imu_pub.publish(imu_msg);
            // 重置标志位
            new_imu_data = false;
        }

        // 按照设定的频率休眠
        rate.sleep();
    }

    return 0;
}

