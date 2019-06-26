#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Passenger.h"
using std::string;
using std::map;

namespace AirlineReservation
{
	class Flight
	{
	public:
		Flight();
		Flight(int flightNo, string airline, string origin, string destination, string departDate,
			string departTime, string arrivalDate, string arrivalTime);
		~Flight();
		void AddPassengerToSeatChart(string seatNumber, PlanePassenger& planePassenger);
		bool IsSeatReserved(string seatNumber);
		void DisplayFlightInfo();
		void DisplayAvailableSeats();
		bool IsSeatAvailable(string seatIn);
		void DisplayPassengers(); 
		PlanePassenger FindPassenger(PlanePassenger& searchPassenger);

		string mAirline;
		string mOrigin;
		string mDestination;
		string mDepartureDate;
		string mDepartureTime;
		string mArrivalDate;
		string mArrivalTime;
		int mFlightNo = -1;
		std::vector<string> mSeats; // vector of seats available on each flight
		map<string, PlanePassenger> mSeatChart; // map of seat as key, PlanePassenger as value		
	};
}