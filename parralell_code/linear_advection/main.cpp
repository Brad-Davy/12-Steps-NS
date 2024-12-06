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
#include <mpi.h>

int arraySize = 100;

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
std::vector<double, 100> stepForward(std::vector<double> arr, int chunk_size)
{
    std::vector<double> arr_new(chunk_size, 0);
    double c = 1;
    double dx = 2.0 / 100;
    double dt = 0.01;

    for (int i = 0; i < chunk_size; i++)
    {
        if (i == 0 || i == chunk_size - 1)
            arr_new[i] = 0; // direchlet boundary conditions
        else
            arr_new[i] = arr[i] - c * dt / dx * (arr[i] - arr[i - 1]);
    }

    return arr_new;
}

void writeArrayToTxt(std::array<double, 100> arr, std::string filename)
{
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < 100; i++)
    {
        file << arr[i] << std::endl;
    }
    file << "\n";
    file.close();
}

int main()
{
    MPI_Init(NULL, NULL);
    int rank, size;
    int numberOfTimeSteps = 100;
    std::array<double, 100> initial_array = createInitialArray();
    size_t chunk_size = 100 / size;
    std::vector<double> local_data(chunk_size, 0);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout << "Hello from rank " << rank << " of " << size << std::endl;

    if (rank == 0)
    {
        writeArrayToTxt(initial_array, "initial_array.txt");
    }

    for (int i = 0; i < numberOfTimeSteps; i++)
    {
        initial_array = stepForward(local_data);
    }

    if (rank == 0)
    {
        writeArrayToTxt(initial_array, "final_array.txt");
    }
    writeArrayToTxt(initial_array, "final_array.txt");
    MPI_Finalize();
    return 0;
}