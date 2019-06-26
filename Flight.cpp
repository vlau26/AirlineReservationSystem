#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include "Passenger.h"
#include "Flight.h"

using namespace AirlineReservation;

Flight::Flight()
{
}

Flight::Flight(int flightNo, string airline, string origin, string destination, string departDate,
	string departTime, string arrivalDate, string arrivalTime) :
	mFlightNo(flightNo), mAirline(airline), mOrigin(origin), mDestination(destination), mDepartureDate(departDate),
	mDepartureTime(departTime), mArrivalDate(arrivalDate), mArrivalTime(arrivalTime)
{}

Flight::~Flight(){}

void Flight::AddPassengerToSeatChart(string seatNumber, PlanePassenger& planePassenger)
{
	mSeatChart[seatNumber] = planePassenger;	
	for (unsigned int i = 0; i < mSeats.size(); i++)
	{
		if (mSeats[i] == seatNumber)
		{
			mSeats.erase(mSeats.begin() + i);
		}
	}	
}

bool Flight::IsSeatReserved(string seatNumber)
{
	return mSeatChart.find(seatNumber) != mSeatChart.end();
}

void Flight::DisplayFlightInfo()
{
	std::cout << std::setw(5) << mFlightNo << "  " << mAirline << "\t" << mOrigin << "-->" << mDestination << 
		"\tDeparts " << mDepartureDate << " at " << mDepartureTime << "\tArrives " << mArrivalDate << " at " <<
		mArrivalTime << std::endl; 		
}

void Flight::DisplayAvailableSeats()
{
	std::cout << "Available Seats: ";
	for (unsigned int i = 0; i < mSeats.size(); i++)
	{
		if (mSeatChart.find(mSeats[i]) == mSeatChart.end())
		{
			std::cout << mSeats[i];
			if (i < mSeats.size() - 1)
			{
				std::cout << ", ";
			}
		}
	}
}

bool Flight::IsSeatAvailable(string seatIn)
{
	for (unsigned int i = 0; i < mSeats.size(); i++)
	{
		if (seatIn == mSeats[i])
		{
			if (mSeatChart.find(mSeats[i]) != mSeatChart.end())
			{
				std::cout << "This seat is taken, please choose a different seat." << std::endl;
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	std::cout << "This is an invalid seat number" << std::endl; 
	return false;
}

void Flight::DisplayPassengers()
{
	for (auto i = mSeatChart.begin(); i != mSeatChart.end(); i++)
	{
		std::cout << "Seat No. " << i->first << " - Passenger: " << i->second.GetFirstName()
			<< " " << i->second.GetLastName() << "\t |  Date of Birth: " << i->second.GetBirthDate()
			<< "\t |  " << i->second.GetGender() << "\t |  " << i->second.GetEmail() << '\n';
	}
}

PlanePassenger Flight::FindPassenger(PlanePassenger& searchPassenger)
{
	for (auto itr = mSeatChart.begin(); itr != mSeatChart.end(); ++itr)
	{
		if (itr->second == searchPassenger)
		{
			return itr->second;
		}				
	}
	return searchPassenger;
}