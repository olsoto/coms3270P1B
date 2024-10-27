# coms3270P1B
Author : Thomas Olson -olsoto@iastate.edu
Part B - Advanced Point Cloud Data Processor

************************
KNOWN ERROR: Segmentation fault (likely memory leak) that I have been unable to identify... The code works correctly and performs the operations but segmentation failure occurs after attempting to free memory.

Description
This project is an extension of Part A, focusing on additional features for visualizing point cloud data. The application reads data from an ASCII file, processes it to compute height statistics, and visualizes it as a grayscale bitmap image, with intensity levels representing height variations.

Features
Height Statistics Calculation: Computes minimum, maximum, and average heights.
Grayscale Image Generation: Outputs a bitmap image where grayscale values correlate with height.
Dynamic List Management: Manages point cloud data dynamically, optimizing memory usage.

Files and Structure
display.c: Main file that initializes and calls functions to read, process, and visualize data.
pointcloud.c: Implements core functionality, including point cloud reading, statistics calculation, and image generation.
pointcloud.h: Contains structure definitions and function declarations for point cloud processing.
util.c/util.h: Implements utility functions for dynamic data storage and retrieval.

Compilation and Execution
Compile the project:
make

Run the program:
./stat <filename>

<filename>: Path to a .xyz file with point cloud data formatted as x y z.

Example File
The project includes a sample file (test.xyz) for testing purposes. This file contains point cloud data that can be visualized as a grayscale bitmap.

Output
The program outputs out.gif, a bitmap image representing point cloud data. Each pixel’s intensity corresponds to height, providing a visual map of elevation.

Dependencies
stdio.h, stdlib.h, float.h: Standard libraries for basic operations.
bmp.h: External library for bitmap handling, included for creating and saving the grayscale image.

Future Improvements
Add support for more image formats and color gradients to improve visualization.
Extend to support interactive manipulation or 3D visualization for complex point cloud datasets.