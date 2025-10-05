// Task 1
// Author: Pranav Jagdish Koli
#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>

int main() {
   
    double robot_x_position{};
    double robot_y_position{};
    double robot_orientation_deg{};
    const double pi{3.14159};
    int choice{};
    double distance{};
    double deg{};
    double dx{};
    double dy{};
    double robot_orientation_rad{};
   
    while (choice!= 6 ) {
    std::cout << "--- Robot Menu ---\n";
    std::cout << "1.Move Forward \n";
    std::cout << "2.Move Backward \n";
    std::cout << "3.Turn Left \n";
    std::cout << "4.Turn Right \n";
    std::cout << "5.Get Robot Status \n";
    std::cout << "6.Exit \n";
    std::cout << "---------------\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    // The while loop will only end when exit is chosen.
    // Only positive input will be accepted. If an input contains a double along with some characters in succession, it will not be accepted.
    // I have used the peek function to check for any characters after the number. For eg. '10gf' input will be declined.
 
        while (std::cin.fail() || choice < 1 || choice > 6 || std::cin.peek() != '\n') {
            std::cout << "Invalid choice. Please enter a number between 1 and 5. \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // To ignore any false input.
            std::cout << "--- Robot Menu ---\n";
            std::cout << "1.Move Forward \n";
            std::cout << "2.Move Backward \n";
            std::cout << "3.Turn Left \n";
            std::cout << "4.Turn Right \n";
            std::cout << "5.Get Robot Status \n";
            std::cout << "6.Exit \n";
            std::cout << "---------------\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
        }
    switch (choice) {
            case 1:
                std::cout << "Enter distance to move forward: ";
                std::cin >> distance;
                while (std::cin.fail() || distance < 0 || std::cin.peek() != '\n') {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Invalid distance. Please enter a positive number: \n";
                    std::cout << "Enter distance to move forward: ";
                    std::cin >> distance;
                    }
                robot_orientation_rad = ( pi * robot_orientation_deg ) / 180.00; // Converted into radians.
                dx = distance * cos(robot_orientation_rad);
                dy = distance * sin(robot_orientation_rad);
                robot_x_position +=  dx;
                robot_y_position +=  dy;
                std::cout << "Robot moved " << distance << " meters ahead. \n";
                std::cout << std::fixed << std::setprecision(2) << "New Position: (" << robot_x_position << ", " << robot_y_position << ") \n \n";
                break;
            case 2:
                std::cout << "Enter distance to move backward: ";
                std::cin >> distance;
                while (std::cin.fail() || distance < 0  || std::cin.peek() != '\n') {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Invalid distance. Please enter a positive number: \n";
                    std::cout << "Enter distance to move backward: ";
                    std::cin >> distance;
                    }
                robot_orientation_rad = ( pi * robot_orientation_deg ) / 180.00;
                dx = distance * cos(robot_orientation_rad);
                dy = distance * sin(robot_orientation_rad);
                robot_x_position -=  dx;
                robot_y_position -=  dy;
                std::cout << "Robot moved back " << distance << " meters. \n";
                std::cout << std::fixed << std::setprecision(2) << "New Position: (" << robot_x_position << ", " << robot_y_position << ") \n \n";
                break;
            case 3:
                std::cout << "Enter angle to turn left in degrees: ";
                std::cin >> deg;
                while (std::cin.fail() || deg < 0 || deg > 360 || std::cin.peek() != '\n') {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Invalid input. Please enter a valid degree between 0 and 360: \n";
                    std::cout << "Enter angle to turn left in degrees: ";
                    std::cin >> deg;
                    }
                if ((deg + robot_orientation_deg) > 360) {
                    robot_orientation_deg = deg + robot_orientation_deg - 360;
                } else {
                robot_orientation_deg += deg;
                }
                std::cout << "\nRobot turned left by " << deg << " degrees. \n";
                std::cout << std::fixed << std::setprecision(2) << "New Orientation: " << robot_orientation_deg << " degrees \n \n";
                break;
            case 4:
                std::cout << "Enter angle to turn right in degrees: ";
                std::cin >> deg;
                while (std::cin.fail() || deg < 0 || deg > 360 || std::cin.peek() != '\n') {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Invalid input. Please enter a valid degree between 0 and 360: \n";
                    std::cout << "Enter angle to turn right in degrees: ";
                    std::cin >> deg;
                    }
                if (deg > robot_orientation_deg) {
                    robot_orientation_deg = 360 - deg + robot_orientation_deg;
                } else {
                robot_orientation_deg -= deg;}
                std::cout << "\nRobot turned right by " << deg << " degrees. \n";
                std::cout << std::fixed << std::setprecision(2) << "New Orientation: " << robot_orientation_deg << " degrees \n \n";
                break;
            case 5:
                std::cout << "Robot Status: \n";
                std::cout << std::fixed << std::setprecision(2) << "Position: (" << robot_x_position << ", " << robot_y_position << ") \n";
                std::cout << std::fixed << std::setprecision(2) << "Orientation: " << robot_orientation_deg << " degrees \n \n";
                break;
            case 6:
                std::cout << "Exiting Robot Simulator. Goodbye \n";
                break;
            default:
                break;
               
        }
    }
}

