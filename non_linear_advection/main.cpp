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

std::array<double, 100> createZeroArray()
{
    std::array<double, 100> arr = {0};
    return arr;
}

std::array<double, 100> createInitialArray()
{
    std::array<double, 100> arr;
    size_t arraySize = arr.size();
    for (int i = 0; i < arraySize; i++)
    {
        if (25 < i && i < 50)
            arr[i] = 1;
        else
            arr[i] = 0;
    }

    return arr;
}

std::array<double, 100> stepForward(std::array<double, 100> arr)
{
    std::array<double, 100> arr_new = {0};
    double c = 1;
    double dx = 2.0 / 100;
    double dt = 0.00000001;

    for (int i = 0; i < 100; i++)
    {
        if (i == 0 || i == 99)
            arr_new[i] = 0; // direchlet boundary conditions
        else
            arr_new[i] = arr[i] + ((arr[i - 1] - (2 * arr[i]) + arr[i + 1]));
    }

    return arr_new;
}

void writeArrayToNumpy(std::array<double, 100> arr, std::string filename)
{
    std::vector<double> vec(arr.begin(), arr.end());
    cnpy::npy_save(filename, vec, "w");
}

int main(int argc, char *argv[])
{
    std::array<double, 100> initial_array = createInitialArray();
    writeArrayToNumpy(initial_array, "initial_array.npy");
    int numberOfTimeSteps = std::atoi(argv[1]);
    for (int i = 0; i < numberOfTimeSteps; i++)
    {
        std::cout << initial_array[50] << std::endl;
        initial_array = stepForward(initial_array);
    }

    writeArrayToNumpy(initial_array, "final_array.npy");
    return 0;
}