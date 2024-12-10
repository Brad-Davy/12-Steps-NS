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

std::array<std::array<double, 100>, 100> createZeroArray()
{
    std::array<std::array<double, 100>, 100> arr = {0};
    return arr;
}

std::array<std::array<double, 100>, 100> createInitial2DArray()
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
    return arr;
}

std::array<std::array<double, 100>, 100> stepForward(std::array<std::array<double, 100>, 100> arr)
{
    std::array<std::array<double, 100>, 100> arr_new = {0};
    double c = 1;
    double dh = 2.0 / 100;
    double dt = 0.001;

    for (int i = 1; i < 99; i++)
    {
        for (int j = 1; j < 99; j++)
        {
            if (i == 0 || i == 99 || j == 0 || j == 99)
            {
                arr_new[i][j] = 0; // dirichlet boundary condition
            }
            else
            {
                // logic for finite difference code
                arr_new[i][j] = arr[i][j] + ((c * dt / dh) * (arr[i - 1][j] + arr[i][j - 1] - (4 * arr[i][j]) + arr[i][j + 1] + arr[i + 1][j]));
            }
        }
    }
    return arr_new;
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

int main(int argc, char *argv[])
{
    std::array<std::array<double, 100>, 100> initial_array = createInitial2DArray();

    write2DArrayToNumpy(initial_array, "initial_array.npy");
    int numberOfTimeSteps = std::atoi(argv[1]);

    for (int i = 0; i < numberOfTimeSteps; i++)
    {
        initial_array = stepForward(initial_array);
    }

    write2DArrayToNumpy(initial_array, "final_array.npy");
    return 0;
}