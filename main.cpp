/***************************************************************
  Student Name: Wanda Tran
  File Name: main.cpp
  Assignment number 2

  Handles the test files: running text files test1 and test2, then printing results.
***************************************************************/

#include <iostream>
#include <fstream>



int main() {
    double lambda, mu;  //(arrival rate, service rate)
    int M, numEvents;   //(num of servers, num events)

    //read input files test1, test2
    std::string fileName;
    std::cout << "Enter the input file name: test1.txt or test2.txt: \n";
    std::cin >> fileName;

    std::ifstream infile(fileName);
    //check existence
    if(!infile) {
        std::cerr << "File " << fileName << " was not found.\n";
        return 1;
    }

    infile >> lambda >> mu >> M >> numEvents;
    infile.close();

    Simulation sim(lambda, mu, M, N);
    sim.run();
    sim.printResults();

    return 0;
}