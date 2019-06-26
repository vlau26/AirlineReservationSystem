#pragma once
#include <iostream>
#include <map>
#include <ctime>
#include <string>

using std::string;

namespace AirlineReservation
{
	class PlanePassenger
	{
	public:
		PlanePassenger();
		PlanePassenger(string& firstName, string& lastName, string& birthDate, char& gender, string& emailAddress);		
		PlanePassenger(string& firstName, string& lastName, string& emailAddress);

		string GetFirstName() { return mFirstName; };
		string GetLastName() { return mLastName; };
		string GetBirthDate() { return mBirthDate; };
		char GetGender() { return mGender; };
		string GetEmail() { return mEmailAddress; };
		bool operator == (const PlanePassenger& planePassenger) const;
		void DisplayPassengerInfo();


	private: 
		string mFirstName;
		string mLastName;
		string mBirthDate; 
		char mGender = NULL;
		string mEmailAddress;		
	};
}