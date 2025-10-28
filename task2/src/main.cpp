/**
 * @file main.cpp
 * @author Pranav Jagdish Koli
 * @brief TODO Add a description
 * @version 1.0
 * @date 10-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sensor_types.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>

int main() {


  // Quality tracking variables
  const std::unordered_map<std::string, int> initial_counts{{"LIDAR", 0},
                                                            {"Camera", 0}};
  std::unordered_map<std::string, int> valid_readings{initial_counts};
  std::unordered_map<std::string, int> total_readings{initial_counts};

  // Variables for calculating summary statistics
  double total_lidar_avg_distance{0.0};
  double total_camera_brightness{0.0};
  int total_obstacles_detected{0};
  int day_mode_count{0};
  int night_mode_count{0};

  std::cout << "=== ROBOT DUAL-SENSOR SYSTEM ===\n\n";

  // ========================================================================
  // Step 1: Data Generation and Storage
  // ========================================================================
  // Random number generator
  std::random_device rd;
  std::mt19937 gen{rd()};

  // Sensor Distribution Rules
  std::uniform_real_distribution<double> lidar_dis(lidar_min_range, lidar_max_range);
  std::uniform_int_distribution<int> rgb_dis(rgb_min, rgb_max);
  std::uniform_real_distribution<double> imu_dis(imu_min_rotation, imu_max_rotation);

  // Storage for all sensor data across timestamps & preallocating memory for timestamps
  std::vector<TimestampData> sensor_readings;
  sensor_readings.reserve(num_timestamps);

  // Main Generation Loop
  for (int i{0}; i < num_timestamps; ++i)
    {   
      std::vector<double> Lidar_Data_Temp{};
      Lidar_Data_Temp.reserve(lidar_readings_count);
      for (int j{0}; j < lidar_readings_count; ++j)
      {
        Lidar_Data_Temp.push_back(lidar_dis(gen));
      }
      std::tuple<int,int,int> Camera_Data_Temp{rgb_dis(gen), rgb_dis(gen), rgb_dis(gen)};
      std::tuple<double,double,double> IMU_Data_Temp{imu_dis(gen), imu_dis(gen), imu_dis(gen)};
      
      // Assemble and Store
      TimestampData current_readings {
        Lidar_Data_Temp,
        Camera_Data_Temp,
        IMU_Data_Temp,
        i,
      };
      sensor_readings.push_back(current_readings);
    }
  // ========================================================================
  // Step 2: Data Processing Loop
  // ========================================================================
  for (const auto& data : sensor_readings) {
    std::cout << "Processing Timestamp: " << data.timestamp << '\n';
    
  }
  // ========================================================================
  // Step 3: Sensor-Specific Processing
  // ========================================================================

  // ========================================================================
  // Step 4: Quality Assessment and Status Determination
  // ========================================================================

  // ========================================================================
  // STEP 5: Summary Statistics and Display
  // ========================================================================
  std::cout << "=== SUMMARY STATISTICS ===\n";

}