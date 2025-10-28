/**
 * @file main.cpp
 * @author Pranav Jagdish Koli
 * @brief TODO A random generator providing random sensor data which is processed to validate the results.
 * @version 1.0
 * @date 10-10-2025
 * 
 * @copyright Copyright (c) 2025
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
#include <cmath>

int main() {


  // Quality tracking variables
  const std::unordered_map<std::string, int> initial_counts{{"LIDAR", 0}, {"Camera", 0}, {"IMU", 0}};
  std::unordered_map<std::string, int> valid_readings{initial_counts};
  std::unordered_map<std::string, int> total_readings{initial_counts};

  // Variables for calculating summary statistics
  double total_lidar_avg_distance{0.0};
  double total_camera_brightness{0.0};
  double total_imu_rotation{0.0};
  int total_obstacles_detected{0};
  int day_mode_count{0};
  int night_mode_count{0};
  int stable_mode_count{0};
  int unstable_mode_count{0};

  std::cout << "\n=== ROBOT TRIPLE-SENSOR SYSTEM ===\n\n";
  std::cout << "Generating sensor data for " << num_timestamps << " timestamps...\n\n";
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
      std::vector<double> lidar_data_temp{};
      lidar_data_temp.reserve(lidar_readings_count);
      for (int j{0}; j < lidar_readings_count; ++j)
      {
        lidar_data_temp.push_back(lidar_dis(gen));
      }
      std::tuple<int,int,int> camera_data_temp{rgb_dis(gen), rgb_dis(gen), rgb_dis(gen)};
      std::tuple<double,double,double> imu_data_temp{imu_dis(gen), imu_dis(gen), imu_dis(gen)};
      
      // Assemble and Store
      TimestampData current_readings {
        lidar_data_temp,
        camera_data_temp,
        imu_data_temp,
        i,
      };
      sensor_readings.push_back(current_readings);
    }
  // ========================================================================
  // Step 2: Data Processing Loop
  // ========================================================================
  for (const auto& data : sensor_readings) {
    std::cout << "Processing Timestamp: " << data.timestamp << '\n';

    // ========================================================================
    // Step 3.1: Sensor-Specific Processing of Lidar
    // ========================================================================

    std::cout << " -LIDAR: [";
    for (size_t k{0}; k < lidar_readings_count; ++k)
    {
      std::cout << std::fixed << std::setprecision(2) << data.lidar_readings[k];
      if (k < lidar_readings_count - 1)
      {
        std::cout << ", ";
      } else {
        std::cout << "] \n";
      }
    }
    
    double sum{std::accumulate(data.lidar_readings.begin(), data.lidar_readings.end(), 0.00)};
    double lidar_avg{sum / lidar_readings_count};
    std::cout << "\tAvg: " << lidar_avg << "m, ";
    total_lidar_avg_distance += lidar_avg;

    int obstacle_count{0};
    for (size_t l{0}; l < lidar_readings_count; ++l)
    {
      if (data.lidar_readings[l] < obstacle_threshold)
      {
        obstacle_count += 1;
      }
    }
    std::cout << "Obstacles: " << obstacle_count << ", ";
    total_obstacles_detected += obstacle_count;

    // ========================================================================
    // Step 4.1: Quality Assessment and Status Determination of Lidar
    // ========================================================================
    int lidar_reading_valid{0};
    for (size_t m{0}; m < lidar_readings_count; ++m){
      if (data.lidar_readings[m] > lidar_min_valid)
      {
        lidar_reading_valid++;
      } 
    }

    if (lidar_reading_valid == lidar_readings_count){
      std::cout << "Status: GOOD\n";
      valid_readings["LIDAR"]++;
    } else {
      std::cout << "Status: POOR\n";
    }
    
    total_readings["LIDAR"]++;
    // For the LIDAR data, since there are 8 readings, all readings can be displayed & validated for status and obstacle count in a single for loop to decrease the length of the code.
    // To increase the readability as per the provide step-wise information for this assignment, I have created 3 different for loops.

    // ========================================================================
    // Step 3.2: Sensor-Specific Processing of Camera
    // ========================================================================

    const auto [r, g, b] = data.camera_readings;
    double brightness{(r+ g+ b) / 3.0};
    total_camera_brightness += brightness;
    
    std::cout << " -Camera: RGB(" << std::get<0>(data.camera_readings) << ", " << std::get<1>(data.camera_readings) << ", " << std::get<2>(data.camera_readings) << "), ";
    std::cout << "Brightness: " << brightness << ", ";
    
    if (brightness > day_night_threshold) {
      std::cout << "Mode: DAY, ";
      day_mode_count++;
    } 
    else {
      std::cout << "Mode: Night, "; 
      night_mode_count++;
    }
    
    // ========================================================================
    // Step 4.2: Quality Assessment and Status Determination of Camera
    // ========================================================================
    
    if (brightness > brightness_threshold)
    {
      std::cout << "Status: GOOD\n";
      valid_readings["Camera"]++;
    } else {
      std::cout << "Status: POOR\n";
    }
    
    total_readings["Camera"]++;

    // ========================================================================
    // Step 3.3: Sensor-Specific Processing of IMU
    // ========================================================================

    const auto [roll, pitch, yaw] = data.imu_readings;
    double rotation_mag = std::sqrt(std::pow(roll, 2) + std::pow(pitch, 2) + std::pow(yaw, 2));
    total_imu_rotation += rotation_mag;
    
    std::cout << " -IMU: RPY(" << std::get<0>(data.imu_readings) << ", " << std::get<1>(data.imu_readings) << ", " << std::get<2>(data.imu_readings) << "), ";
    std::cout << "Total Rotation: " << rotation_mag << " deg, ";
    if ((abs(roll) < imu_stability_threshold) && (abs(pitch) < imu_stability_threshold) && (abs(yaw) < imu_stability_threshold)) {
      std::cout << "Mode: STABLE, ";
      stable_mode_count++;
    } 
    else {
      std::cout << "Mode: UNSTABLE, "; 
      unstable_mode_count++;
    }

    // ========================================================================
    // Step 4.3: Quality Assessment and Status Determination of IMU
    // ========================================================================
    
    if ((abs(roll) >= imu_min_rotation && abs(roll) <= imu_max_rotation) && 
        (abs(pitch) >= imu_min_rotation && abs(pitch) <= imu_max_rotation) && 
        (abs(yaw) >= imu_min_rotation && abs(yaw) <= imu_max_rotation))
    {
      std::cout << "STATUS: GOOD\n\n";
      valid_readings["IMU"]++; 
    } else {
      std::cout << "STATUS: POOR\n\n";
    }
    
    total_readings["IMU"]++;

  }
  
  // ========================================================================
  // STEP 5: Summary Statistics and Display
  // ========================================================================
  std::cout << "=== SUMMARY STATISTICS ===\n";
  
  int total_readings_count{total_readings["LIDAR"] + total_readings["Camera"] + total_readings["IMU"]};
  std::cout << "Total Readings Processed: " << total_readings_count << '\n';

  int valid_readings_count{valid_readings["LIDAR"] + valid_readings["Camera"] + valid_readings["IMU"]};
  std::cout << "Valid Readings: " << valid_readings_count << "(" << (valid_readings_count / total_readings_count) * 100 << "%) \n\n";

  std::cout << "Sensor Readability Report:\n";

  std::cout << " -LIDAR:  " << valid_readings["LIDAR"] << "/" << num_timestamps;
  std::cout << " (" << (valid_readings["LIDAR"] / num_timestamps) * 100 << "%) \n";

  std::cout << " -Camera: " << valid_readings["Camera"] << "/" << num_timestamps;
  std::cout << " (" << (valid_readings["Camera"] / num_timestamps) * 100 << "%) \n";

  std::cout << " -IMU:  " << valid_readings["IMU"] << "/" << num_timestamps;
  std::cout << " (" << (valid_readings["IMU"] / num_timestamps) * 100 << "%) \n\n";

  std::cout << "Operational Statistics:\n";

  std::cout << " -Average LIDAR Distance: " << total_lidar_avg_distance / num_timestamps << "m\n";
  std::cout << "   -Total Obstacles Detected: " << total_obstacles_detected << '\n';

  std::cout << " -Average Camera Brightness: " << total_camera_brightness / num_timestamps << '\n';
  std::cout << "   -Day Mode Detections: " << day_mode_count << '\n';
  std::cout << "   -Night Mode Detections: " << night_mode_count << '\n';

  std::cout << " -Average IMU Total Rotation: " << total_imu_rotation / num_timestamps << " deg\n";
  std::cout << "   -Stable Mode Detections: " << stable_mode_count << '\n';
  std::cout << "   -Unstable Mode Detections: " << unstable_mode_count << "\n\n";

  std::cout << "=== END OF PROGRAM ===\n\n";

  // The results are mostly accurate, since the random value generated is uniformly distributed and there's less probability of the value be less than the threshold.
  // So, results cannot be controlled, which is similar to real life applications.
  // Here, some results can be manipulated to get mixed results within iterations, but I didn't do it for the assignment.
  // That's it.
}