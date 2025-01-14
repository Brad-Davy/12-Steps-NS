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
#include <cnpy.h>
#include <cmath>

class velocityField
{
public:
    std::array<std::array<double, 100>, 100> v_x = {0};
    std::array<std::array<double, 100>, 100> v_y = {0};
    std::array<std::array<double, 100>, 100> p = {0};

    std::array<std::array<double, 100>, 100> initiateVelocityField()
    {
        std::array<std::array<double, 100>, 100> arr = {0};

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (25 < i && i < 50 && 25 < j && j < 50)
                    arr[i][j] = 0;
                else
                    arr[i][j] = 0;
            }
        }
        v_x = arr;
        v_y = arr;
        return arr;
    }

    std::array<std::array<double, 100>, 100> combineArrays(std::array<std::array<double, 100>, 100> arr1, std::array<std::array<double, 100>, 100> arr2)
    {
        std::array<std::array<double, 100>, 100> arr = {0};
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                arr[i][j] = std::sqrt((arr1[i][j] * arr1[i][j] + arr2[i][j] * arr2[i][j]));
            }
        }
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
        std::string vFileName = filename + "_v.npy";
        std::string pFileName = filename + "_p.npy";
        write2DArrayToNumpy(combineArrays(v_x, v_y), vFileName);
        write2DArrayToNumpy(p, pFileName);
    }

    float computeSum(std::array<std::array<double, 100>, 100> arr)
    {
        float sum = 0;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                sum += arr[i][j];
            }
        }
        return sum;
    }

    std::array<std::array<double, 100>, 100> computeB()
    {
        std::array<std::array<double, 100>, 100> b = {0};
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                b[i][j] = v_x[i + 1][j] - v_x[i - 1][j] + v_y[i][j + 1] - v_y[i][j - 1] - ((v_x[i + 1][j] - v_x[i - 1][j]) * (v_x[i + 1][j] - v_x[i - 1][j]) + 2 * (v_x[i][j + 1] - v_x[i][j - 1]) * (v_y[i + 1][j] - v_y[i - 1][j]) - (v_y[i][j + 1] - v_y[i][j - 1]) * (v_y[i][j + 1] - v_y[i][j - 1]));
            }
        }
        return b;
    }

    void iteratePressureTerm()
    {
        double residual = 5;
        double difference = 10;
        int index = 0;
        std::array<std::array<double, 100>, 100> temporaryPArray = {0};
        std::array<std::array<double, 100>, 100> b = computeB();
        while (std::abs(difference) > residual)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if (i == 0)
                    {
                        temporaryPArray[i][j] = temporaryPArray[i + 1][j];
                    }
                    else if (i == 99)
                    {
                        temporaryPArray[i][j] = 0;
                    }
                    else if (j == 0)
                    {
                        temporaryPArray[i][j] = temporaryPArray[i][j + 1];
                    }
                    else if (j == 99)
                    {
                        temporaryPArray[i][j] = temporaryPArray[i][j - 1];
                    }
                    else
                    {
                        temporaryPArray[i][j] = 0.25 * (temporaryPArray[i - 1][j] + temporaryPArray[i][j - 1] + temporaryPArray[i][j + 1] + temporaryPArray[i + 1][j] - b[i][j]);
                    }
                }
            }
            index++;
            difference = computeSum(p) - computeSum(temporaryPArray);
            p = temporaryPArray;
        }
    }

    void timeStep()
    {
        std::array<std::array<double, 100>, 100> temporaryVxArray = {0};
        std::array<std::array<double, 100>, 100> temporaryVyArray = {0};
        double c = 1;
        double diffusionCoefficient = 5;
        double pressureCoefficient = 1;
        double dh = 2.0 / 100;
        double dt = 0.002;

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (i == 0)
                {
                    temporaryVxArray[i][j] = 1; // dirichlet boundary condition
                    temporaryVyArray[i][j] = 1; // dirichlet boundary condition
                }
                else if (i == 99 || j == 0 || j == 99)
                {
                    temporaryVxArray[i][j] = 0; // dirichlet boundary condition
                    temporaryVyArray[i][j] = 0; // dirichlet boundary condition
                }
                else
                {
                    // logic for finite difference code
                    temporaryVxArray[i][j] = v_x[i][j] + ((c * dt / dh) * (-(v_x[i][j] * (v_x[i][j] - v_x[i - 1][j])) - (v_y[i][j] * (v_x[i][j] - v_x[i][j - 1])) -
                                                                           pressureCoefficient * (p[i][j] - p[i][j + 1]) +
                                                                           diffusionCoefficient * (v_x[i - 1][j] + v_x[i][j - 1] - (4 * v_x[i][j]) + v_x[i][j + 1] + v_x[i + 1][j])));

                    temporaryVyArray[i][j] = v_y[i][j] + ((c * dt / dh) * (-(v_x[i][j] * (v_y[i][j] - v_y[i - 1][j])) - (v_y[i][j] * (v_y[i][j] - v_y[i][j - 1])) -
                                                                           pressureCoefficient * (p[i][j] - p[i + 1][j]) +
                                                                           diffusionCoefficient * (v_y[i - 1][j] + v_y[i][j - 1] - (4 * v_y[i][j]) + v_y[i][j + 1] + v_y[i + 1][j])));
                }
            }
        }
        v_x = temporaryVxArray;
        v_y = temporaryVyArray;
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
        std::cout << "Time step: " << i << std::endl;
        v.timeStep();
        v.iteratePressureTerm();
    }

    // write the final array to a numpy file
    v.writeArraysToNumpy("final");

    return 0;
}