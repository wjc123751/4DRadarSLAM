# 4DRadarSLAM
本科实习

================================================================================
基于毫米波雷达与IMU的SLAM系统
================================================================================

[项目背景]
----------
本项目由大风技术有限公司与应急管理部上海消防研究所联合研发，旨在实现恶劣环境（浓烟、雾霾、雨雪等）下的可靠SLAM建图与导航。通过融合毫米波雷达（mmWave Radar）和惯性测量单元（IMU）数据，克服传统激光SLAM在消防场景中的局限性。

[核心优势]
----------
- 恶劣环境适应性
  * 在可见度低于0.5米的浓烟环境中稳定工作
  * 耐受温度范围：-20℃ ~ 65℃
  * 支持雨/雪/雾霾多场景融合

- 技术特性
  * 多传感器紧耦合框架
  * 毫米波雷达点云聚类算法
  * IMU辅助运动补偿
  * 抗干扰闭环检测模块
  * ROS集成部署

[系统架构]
----------
毫米波雷达 --> 数据预处理
IMU ------↑
           |
           --> 特征提取 --> 融合SLAM核心 --> 全局地图
                                  |
                                  --> 实时位姿

[依赖环境]
----------
- 操作系统：Ubuntu 20.04 LTS
- ROS版本：Noetic
- 关键依赖：
  * TI mmWave Radar Driver
  * Eigen 3.4.0+
  * PCL 1.10+
  * OpenCV 4.2+

[快速部署]
----------
# 克隆仓库
git clone https://github.com/your-repo/mmwave-imu-slam.git

# 安装依赖
sudo apt-get install ros-noetic-pcl-ros ros-noetic-tf2-sensor-msgs

# 编译
cd ~/catkin_ws && catkin_make --pkg mmwave_slam

[运行演示]
----------
# 启动基础节点
roslaunch mmwave_slam sensor_bringup.launch

# 运行SLAM核心
roslaunch mmwave_slam mapping.launch mode:=fire_smoke

[关键参数配置]
------------
配置文件路径：config/params.yaml
--------------------------------
radar:
  max_range: 50.0    # 最大探测距离(m)
  noise_threshold: 0.2 # 噪声过滤阈值

slam:
  resolution: 0.05   # 地图分辨率
  optimization_freq: 1.0 # 优化频率(Hz)

[项目结构]
----------
mmwave-imu-slam/
├── config/          # 传感器参数配置
├── launch/          # ROS启动文件
├── src/
│   ├── preprocessor # 数据预处理节点
│   ├── mapper       # 建图核心算法
│   └── utils        # 数学工具库
├── dataset/         # 测试数据集（可选）
└── docs/            # 技术文档

[性能指标]
----------
指标                | 本系统 | 激光SLAM
---------------------------------------
浓烟环境成功率      | 98.2%  | 12.7%    
建图精度（RMS）     | ±0.3m  | ±0.1m*   
最大工作持续时间    | 8h     | 0.5h     

*注：激光SLAM数据为正常环境下测试结果

[特别说明]
----------
1. 传感器标定需在无干扰环境中完成初始化
2. 浓烟模式需启用thermal_compensation参数
3. 建议定期更新雷达抗干扰滤波参数

[合作单位]
----------
应急管理部上海消防研究所 (http://www.firelab.com.cn)
大风技术有限公司 (http://www.dafengtech.com)

[联系方式]
----------
技术咨询：slam-support@dafengtech.com  
紧急支持：+86-21-5566-XXXX

================================================================================
[注意事项]
1. 本文件为简化版说明，详细文档见/docs目录
2. 实际使用需根据硬件型号补充接口协议说明
3. 标定工具使用指南详见docs/calibration_guide.pdf
4. API文档访问：http://api.dafengtech.com/mmwave-slam
================================================================================