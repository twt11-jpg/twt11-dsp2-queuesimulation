/***************************************************************
  Student Name: Wanda Tran
  File Name: simulation.hpp
  Assignment number 2

  Handles the test files: running text files test1 and test2, then printing results.
***************************************************************/

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "event.hpp"
#include "heap.hpp"

class Simulation {
    private:
        double lambda, mu;
        int M, numEvents;

        Heap priorityQue;
        std::deque<double> fifoQue;
        std::vector<bool> servers;

        double totalWaitTime, totalServiceTime, idleTime;
        int customersWaited;

        double getNextInterval(double avg);

    public:
        Simulation(double lamb, double mu, int M, int eventNum);

        void run();
        void printResults();
};

#endif //SIMULATION_HPP