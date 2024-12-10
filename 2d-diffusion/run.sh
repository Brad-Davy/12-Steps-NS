numberOfTimeSteps=$1
echo $numberOfTimeSteps
g++ main.cpp cnpy/cnpy.cpp -Icnpy -std=c++11 -lz -o main
./main $numberOfTimeSteps
python3 plotting.py
