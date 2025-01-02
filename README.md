# 12 Steps to Navier-Stokes in C++

This project is a re-implementation of the "12 Steps to Navier-Stokes" code, originally written in Python, now translated into C++. The goal of this project is to provide a more performant version of the original code while maintaining the educational value and clarity of the original implementation.

## Overview

The Navier-Stokes equations describe the motion of fluid substances such as liquids and gases. These equations are fundamental in the field of fluid dynamics and are used in various engineering and scientific applications. The "12 Steps to Navier-Stokes" project breaks down the complex Navier-Stokes equations into manageable steps, making it easier to understand and implement.

## Project Structure

The project is organized into the following steps:

1. **Step 1: Linear Convection**
2. **Step 2: Nonlinear Convection**
3. **Step 3: Diffusion**
4. **Step 4: Burgers' Equation**
5. **Step 5: 2D Linear Convection**
6. **Step 6: 2D Nonlinear Convection**
7. **Step 7: 2D Diffusion**
8. **Step 8: Laplace Equation**
9. **Step 9: Poisson Equation**
10. **Step 10: Cavity Flow**
11. **Step 11: Channel Flow**
12. **Step 12: Navier-Stokes Equation**

Each step is implemented in a separate C++ file, with detailed comments and explanations to facilitate understanding.

## Requirements

To compile and run the code, you will need:

- A C++ compiler (e.g., g++, clang++)
- CMake (optional, for building the project)
- A text editor or IDE (e.g., Visual Studio Code, CLion)

## Compilation and Execution

To compile and run the code, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/12-Steps-NS-Cpp.git
    cd 12-Steps-NS-Cpp
    ```

2. Compile the code using a C++ compiler:
    ```sh
    g++ -o step1 step1.cpp
    ./step1
    ```

3. Alternatively, you can use CMake to build the project:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ./step1
    ```

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

This project is based on the original "12 Steps to Navier-Stokes" code written in Python by Lorena A. Barba and her students. Special thanks to them for their educational contributions to the field of computational fluid dynamics.
