/***************************************************************
  Student Name: Wanda Tran
  File Name: event.hpp
  Assignment number 2

  Defines Arrival and Departure of events in order of time for priority queue simulation.
***************************************************************/

#ifndef EVENT_HPP
#define EVENT_HPP

enum EventType { Arrival, Departure };

struct Event {
    double time;
    EventType type;
    Event(double t = 0.0, EventType eventType = Arrival) : time(t), type(eventType) {}  //default constructor
    bool operator<(const Event& other) const {
        return time < other.time;       //return true: event happens earlier than other event
                                        //return false: event happens later
    }
};


#endif // EVENT.HPP