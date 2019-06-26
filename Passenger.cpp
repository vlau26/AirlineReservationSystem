#include "Passenger.h"
#include <string>
using std::cout;
using std::endl;
using namespace AirlineReservation;

PlanePassenger::PlanePassenger(){}

PlanePassenger::PlanePassenger(string& firstName, string& lastName, string& birthDate, char& gender, string& emailAddress)
{
	this->mFirstName = firstName;
	this->mLastName = lastName;
	this->mBirthDate = birthDate;
	this->mGender = gender;
	this->mEmailAddress = emailAddress;
}

AirlineReservation::PlanePassenger::PlanePassenger(string& firstName, string& lastName, string& emailAddress)
{
	this->mFirstName = firstName;
	this->mLastName = lastName;
	this->mEmailAddress = emailAddress;
}

bool AirlineReservation::PlanePassenger::operator==(const PlanePassenger& planePassenger) const
{
	return planePassenger.mFirstName.compare(this->mFirstName) == 0 &&
		planePassenger.mLastName.compare(this->mLastName) == 0 &&
		planePassenger.mEmailAddress.compare(this->mEmailAddress) == 0;
}

void AirlineReservation::PlanePassenger::DisplayPassengerInfo()
{
	cout << "Passenger: " << this->GetFirstName() << " " << this->GetLastName() << endl;
	cout << "Date of Birth: " << this->GetBirthDate() << endl;
	cout << "Gender: " << this->GetGender() << endl;
	cout << "Email address: " << this->GetEmail() << endl;
}

