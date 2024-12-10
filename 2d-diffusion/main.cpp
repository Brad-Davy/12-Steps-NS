/**
 * @file main.cpp
 * @brief This script solves the linear advection problem, adapted from the "12 Steps to Navier-Stokes" tutorial, but using C++.
 *
 * The program initializes an array with a step function and prints a value from the initial array.
 *
 * Functions:
 * - createZeroArray: Creates and returns an array initialized to zero.
 * - createInitialArray: Creates and returns an array initialized with a step function.
 *
 * The main function demonstrates the creation of the initial array and prints a specific value from it.
 */
#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <hdf5.h>
#include <cnpy.h>

class velocityField
{
public:
    std::array<std::array<double, 100>, 100> v_x = {0};
    std::array<std::array<double, 100>, 100> v_y = {0};

    std::array<std::array<double, 100>, 100> initiateVelocityField()
    {
        std::array<std::array<double, 100>, 100> arr = {0};

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (25 < i && i < 50 && 25 < j && j < 50)
                    arr[i][j] = 1;
                else
                    arr[i][j] = 0;
            }
        }
        v_x = arr;
        v_y = arr;
        return arr;
    }

    void write2DArrayToNumpy(std::array<std::array<double, 100>, 100> arr, std::string filename)
    {
        std::vector<double> vec;

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                vec.push_back(arr[i][j]);
            }
        }
        cnpy::npy_save(filename, vec, "w");
    }

    void writeArraysToNumpy(std::string filename)
    {
        std::string vxFileName = filename + "_vx.npy";
        std::string vyFileName = filename + "_vy.npy";
        write2DArrayToNumpy(v_x, vxFileName);
        write2DArrayToNumpy(v_y, vyFileName);
    }

    void timeStep()
    {
        std::array<std::array<double, 100>, 100> temporaryVxArray = {0};
        std::array<std::array<double, 100>, 100> temporaryVyArray = {0};
        double c = 1;
        double dh = 2.0 / 100;
        double dt = 0.001;

        for (int i = 1; i < 99; i++)
        {
            for (int j = 1; j < 99; j++)
            {
                if (i == 0 || i == 99 || j == 0 || j == 99)
                {
                    temporaryVxArray[i][j] = 0; // dirichlet boundary condition
                    temporaryVyArray[i][j] = 0; // dirichlet boundary condition
                }
                else
                {
                    // logic for finite difference code
                    temporaryVxArray[i][j] = v_x[i][j] + ((c * dt / dh) * (v_x[i - 1][j] + v_x[i][j - 1] - (4 * v_x[i][j]) + v_x[i][j + 1] + v_x[i + 1][j]));
                    temporaryVyArray[i][j] = v_y[i][j] + ((c * dt / dh) * (v_y[i - 1][j] + v_y[i][j - 1] - (4 * v_y[i][j]) + v_y[i][j + 1] + v_y[i + 1][j]));
                }
            }
        }
        v_x = temporaryVxArray;
        v_y = temporaryVxArray;
    }
};

int main(int argc, char *argv[])
{
    // initialise the class and the velocity field
    velocityField v;
    v.initiateVelocityField();

    // write the initial array to a numpy file
    v.writeArraysToNumpy("initial");

    // get the number of time steps from the command line
    int numberOfTimeSteps = std::atoi(argv[1]);

    // main loop
    for (int i = 0; i < numberOfTimeSteps; i++)
    {
        v.timeStep();
    }

    // write the final array to a numpy file
    v.writeArraysToNumpy("final");

    return 0;
}