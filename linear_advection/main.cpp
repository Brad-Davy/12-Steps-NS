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

std::array<double, 100> createZeroArray()
{
    std::array<double, 100> arr = {0};
    return arr;
}

std::array<double, 100> createInitialArray()
{
    std::array<double, 100> arr;
    for (int i = 0; i < 100; i++)
    {
        if (i < 50)
            arr[i] = 1;
        else
            arr[i] = 0;
    }
    return arr;
}

int main()
{
    std::array<double, 100> initial_array = createInitialArray();
    std::cout << "initial_array: " << initial_array[20] << std::endl;
    return 0;
}