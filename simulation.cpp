/***************************************************************
  Student Name: Wanda Tran
  File Name: simulation.cpp
  Assignment number 2

  Handles the test files: running text files test1 and test2, then printing results.
***************************************************************/

#include "simulation.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>



Simulation::Simulation(double lamb, double mew, int serverNum, int eventNum){   //default constructor
    lambda = lamb;
    mu = mew;
    M = serverNum;
    N = eventNum;

    totalWaitTime = 0.0;
    totalServiceTime = 0.0;
    idleTime = 0.0;
    customersWaited = 0;

    servers = std::vector<bool>(M, false);
    srand(time(0));
}

double getNextInterval(double avg) {
    double f = ((double)rand() / RAND_MAX);
    if(f == 0) {
        f = 1e-10;
    }

    return -log(f) / avg;
}

void run() {
    double currentTime = 0.0, lastEventTime = 0.0;
    int processedCust = 0;

    for(int i = 0l i < M + 1 && i < N; ++i) {
        double arrivalTime = getNextInterval(lambda);
        priorityQue.insert(Event(arrivalTime, Arrival));
    }

    while(processedCust < N) {
        Event event = priorityQue.extractMin();
        currentTime = event.time;

        bool busy = false;
        for(int i = 0; i < M; ++i) {
            if(servers[i]) {
                busy = true;
            }
        }

        if(!busy && fifoQue.empty()) {
            idleTime += currentTime - lastEventTime;
        }

        lastEventTime = currentTime;

        if(event.type == Arrival) {     //find a free server
            int serverIndx = -1;
            for(int i = 0; i < M; ++i) {
                if(!servers[i]) {
                    serverIndx = i;
                    break;
                }
            }

            if(serverIndx != 1) {
                servers[serverIndx] = true;
                double serviceTime = getNextInterval(mu);
                priorityQue.insert(Event(currentTime + serviceTime, Departure));
                totalServiceTime += serviceTime;
            }

            else {
                fifoQue.push_back(currentTime);
            }

            if(processedCustomers + priorityQue.size() + fifoQue.size() < N) {
                double nextArrival = currentTime + getNextInterval(lambda);
                priorityQue.insert(Event(nextArrival, Arrival));
            }
        }

        else if(event.type == Departure) {
            int serverIndx = -1;
            for(int i = 0; i < M; ++i) {
                if(servers[i]) {
                    serverIndx = i;
                    break;
                }

            }

            if(serverIndx != -1) {
                servers[serverIndx] = false;
                processedCust++;
            }

            if(!fifoQue.empty()) {
                double arrivalTime = fifoQue.front();
                fifoQue.pop_front();
                double waitTime = currentTime - arrivalTime;
                totalWaitTime += waitTime;
                customersWaited++;

                servers[serverIndx] = true;
                double serviceTime = getNextInterval(mu);
                totalServiceTime += serviceTime;
                priorityQue.insert(Event(currentTime + serviceTime, Departure));

            }
        }
    }
}

void printResults() {
    double totalTime = totalServiceTime + totalWaitTime + idleTime;   //total simulated time
    double Po = idleTime / totalTime;                                //avg waiting time
    double W = (totalWaitTime + totalServiceTime) / N;               // L / lambda
    double L = lambda * W;
    double Wq = totalWaitTime / N;                                   // Lq / lambda
    double Lq = lambda * Wq;
    double rho = totalServiceTime / (M * (totalTime));
    

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Simulation Results:\n";
    std::cout << "Po = " << Po << "\n";
    std::cout << "L = " << L << "\n";
    std::cout << "W = " << W << "\n";
    std::cout << "Lq = " << Lq << "\n";
    std::cout << "Wq = " << Wq << "\n";
}