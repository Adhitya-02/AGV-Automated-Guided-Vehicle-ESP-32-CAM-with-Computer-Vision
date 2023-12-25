# AGV (Automated Guided Vehicle) ESP-32 CAM with Computer Vision

## Overview

This project implements an Automated Guided Vehicle (AGV) system using ESP-32 CAM equipped with a camera and computer vision capabilities. The ESP32 CAM streams video using the Real-Time Streaming Protocol (RTSP), which is accessed via a Python script through Visual Studio Code (VS Code). The objective is to calculate the position of an object in the camera frame based on the error of the x and y-axis values relative to the center point. Subsequently, these calculated x and y values are sent to an ESP32 DevKit, allowing precise control of the AGV's motors to navigate towards the object.

[![Watch the Project in Action](https://img.youtube.com/vi/shZ0XA6sdwA/0.jpg)](https://youtu.be/shZ0XA6sdwA)

## Features

- **ESP32 CAM RTSP Streaming:** The ESP32 CAM serves as the AGV's eyes, streaming real-time video through RTSP, providing a live feed of its surroundings.

- **Computer Vision Processing:** The Python script running in VS Code processes the video feed, calculates the position of a specified object, and determines the error in the x and y-axis values relative to the center point.

- **Dynamic Motor Control:** The calculated x and y values are transmitted to the ESP32 DevKit, enabling dynamic and precise motor control to navigate the AGV towards the desired object.

## Getting Started

To begin using this project, follow these steps:

1. **Install Dependencies:** Ensure that you have all the required dependencies installed, including the necessary libraries for ESP32 CAM and computer vision processing. Detailed instructions can be found in the project documentation.

2. **Upload Code to ESP32 CAM:** Upload the provided code to your ESP32 CAM, configuring it to stream video over RTSP.

3. **Run Python Script:** Execute the Python script in VS Code to process the video feed and calculate the object's position based on the x and y-axis errors.

4. **Transmit Values to ESP32 DevKit:** Implement the communication between the Python script and the ESP32 DevKit to transmit the calculated x and y values for motor control.

5. **Observe AGV Navigation:** Watch the AGV dynamically adjust its movement based on the calculated values, demonstrating the effectiveness of the computer vision-guided navigation system.

## Project Structure

- **/src:** Contains the source code for ESP32 CAM RTSP streaming and the Python script for computer vision processing.

- **/docs:** Project documentation, including setup instructions and usage guidelines.

## Contributing

If you'd like to contribute to this project, please follow our [contribution guidelines](CONTRIBUTING.md). We welcome feedback, bug reports, and feature requests.

## License

This project is licensed under the [MIT License](LICENSE.md).

Feel free to reach out if you have any questions or need assistance with the project.
