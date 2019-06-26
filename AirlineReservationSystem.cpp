#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include "Flight.h"

using namespace std;
using namespace AirlineReservation;

enum
{
	eEXIT_PROGRAM = 0,
	eVIEW_FLIGHT_SCHEDULE,
	eRESERVE_SEAT,
	eVIEW_PASSENGER_INFO,
	eVIEW_FLIGHT_DETAILS,
	eVIEW_PASSENGER_TICKET
};

enum
{
	eFLIGHT_STR = 0,
	eFLIGHT_NUMBER,
	eAIRLINE,
	eORIGIN, 
	eDESTINATION,
	eDEPARTURE_DATE, 
	eDEPARTURE_TIME,
	eARRIVAL_DATE, 
	eARRIVAL_TIME
};

void DisplayMenu();
void InitFlights(string filePath, vector<Flight>& flights);
void DisplayFlightSchedule(vector<Flight> flights);
void DisplayFlightDetails(vector<Flight> flights);
void ReserveSeat(vector<Flight>& flights);
void DisplayFlightPassengers(vector<Flight> flights);
void GetTicketInfo(vector<Flight> flights);
void ConvertToUpper(string& string);

int main(void)
{
	int selection;
	vector<Flight> flights;
	InitFlights("flight_schedule.txt", flights);

	while (true)
	{
		DisplayMenu();
		cin >> selection;

		switch (selection)
		{
		case eEXIT_PROGRAM:
			return 0;
		case eVIEW_FLIGHT_SCHEDULE:
			DisplayFlightSchedule(flights);
			break;
		case eRESERVE_SEAT:
			ReserveSeat(flights);
			break;
		case eVIEW_PASSENGER_INFO:
			DisplayFlightPassengers(flights);
			break;
		case eVIEW_FLIGHT_DETAILS:
			DisplayFlightDetails(flights);
			break;
		case eVIEW_PASSENGER_TICKET:
			GetTicketInfo(flights);
			break;
		default:
			cerr << "Invalid selection, please try again." << endl;
			break;
		}
	}
}

void DisplayMenu(void)
{
	cout << "*** Welcome to the Airline Reservation System *** \n" << endl;
	cout << "Please choose from the following menu:" << endl;
	cout << "1. View flight schedule" << endl;
	cout << "2. Reserve a seat" << endl;
	cout << "3. View passenger information" << endl;
	cout << "4. View flight details" << endl;
	cout << "5. View passenger ticket information" << endl;
	cout << "0. Exit the program" << endl;
	cout << endl;
}

void InitFlights(string fileName, vector<Flight>& flights)
{
	ifstream file(fileName.c_str());
	regex flightRgx("(.*)@(.*)@(.*)@(.*)@(.*)@(.*)@(.*)@(.*)");
	smatch flightInfo;
	string flightStr;
	smatch seatInfo;
	string seatStr;

	if (!file)
	{
		cerr << "Unable to load flight database: " << fileName << endl;		
	}
	else
	{
		int i = 0;
		while (getline(file, flightStr))
		{			
			getline(file, seatStr);
			seatStr.erase(0, (sizeof("AvailableSeats:") -1));
			if (regex_search(flightStr, flightInfo, flightRgx))
			{
				Flight newFlight(stoi((flightInfo[eFLIGHT_NUMBER]), nullptr, 10), (flightInfo[eAIRLINE]), (flightInfo[eORIGIN]), (flightInfo[eDESTINATION]),
					(flightInfo[eDEPARTURE_DATE]), (flightInfo[eDEPARTURE_TIME]), (flightInfo[eARRIVAL_DATE]),
					(flightInfo[eARRIVAL_TIME]));

				flights.push_back(newFlight);

				string delimiter = ",";
				size_t pos = 0;
				string seatNo;
				while ((pos = seatStr.find(delimiter)) != string::npos)
				{
					seatNo = seatStr.substr(0, pos);
					seatStr.erase(0, pos + delimiter.length());
					flights[i].mSeats.push_back(seatNo);
				}
				i++;
			}
		}
	}
}

void DisplayFlightSchedule(vector<Flight> flights)
{
	for (unsigned int i = 0; i < flights.size(); i++)
	{
		flights[i].DisplayFlightInfo();
	}
	cout << '\n';
}

void DisplayFlightDetails(vector<Flight> flights)
{
	int flightNo;
	cout << "Please enter the flight number to view details" << endl;
	cin >> flightNo;
	for (unsigned int i = 0; i < flights.size(); i++)
	{
		while(flights[i].mFlightNo == flightNo)
		{
			flights[i].DisplayFlightInfo();
			flights[i].DisplayAvailableSeats();
			cout << '\n' << endl;
			return;
		}
	}
	cout << "Not a valid flight. Returning to main menu.\n" << endl;
	return;
}

void ReserveSeat(vector<Flight>& flights)
{
	int flightSelection;
	string seatSelection;
	cout << "Please enter the flight number of the flight you would like to reserve a seat (numerical values only):" << endl;
	cin >> flightSelection;
	cout << '\n';

	for (unsigned int i = 0; i < flights.size(); i++)
	{
		if (flights[i].mFlightNo == flightSelection)
		{
			flights[i].DisplayFlightInfo();
			flights[i].DisplayAvailableSeats();
			cout << '\n' << endl;
			while(true)
			{
				cout << "Which seat would you like to reserve? (example: enter '2A' or '4B', no spaces)" << endl;
				cin >> seatSelection;
				if (flights[i].IsSeatAvailable(seatSelection) == true)
				{
					string passengerFirstName;
					string passengerLastName;
					string passengerBirthDate;
					string GenderInput;
					char passengerGender;
					string passengerEmail;
					cout << "Enter passenger's first name: " << endl;
					cin >> passengerFirstName;
					cout << "Enter passenger's last name: " << endl;
					cin >> passengerLastName;
					cout << "Enter passenger's date of birthdate (mm/dd/yyyy): " << endl;
					cin >> passengerBirthDate; 
					cout << "Enter passenger's gender (F for female, M for male): " << endl;
					cin >> GenderInput;
					passengerGender = GenderInput.front();
					cout << "Enter passenger's email address for contact information: " << endl;
					cin >> passengerEmail;

					ConvertToUpper(passengerFirstName);
					ConvertToUpper(passengerLastName);
					passengerGender = toupper(passengerGender);
					ConvertToUpper(passengerEmail);

					PlanePassenger planePassenger(passengerFirstName, passengerLastName, passengerBirthDate, passengerGender, passengerEmail);
					flights[i].AddPassengerToSeatChart(seatSelection, planePassenger);
					cout << "\nReservation complete. Returning to main menu." << endl;
					cout << "----------------------------------------------" << endl;
					return;
				}
			} 
		}	
	}
	cout << "Not a valid flight. Returning to main menu." << endl;
}

void DisplayFlightPassengers(vector<Flight> flights)
{
	int flightSelection;
	cout << "\n Please enter the flight number of the flight to view current passengers on that flight (numerical values only): " << endl;
	cin >> flightSelection;
	
	for (unsigned int i = 0; i < flights.size(); i++)
	{
		if (flights[i].mFlightNo == flightSelection)
		{
			cout << endl;
			flights[i].DisplayFlightInfo();
			while(true)
			{
				flights[i].DisplayPassengers();
				cout << endl;
				return;
			} 			
		}
	}
	cout << "Not a valid flight. Returning to main menu." << endl;
	return;		
}

void GetTicketInfo(vector<Flight> flights)
{

	string passengerFirstName;
	string passengerLastName;
	string passengerEmail;
	string seatResult;
	cout << "SEARCH FOR A PASSENGER \nEnter passenger's first name:" << endl;
	cin >> passengerFirstName;
	cout << "Enter passenger's last name:" << endl;
	cin >> passengerLastName;
	cout << "Enter passenger's email: " << endl;
	cin >> passengerEmail;
	cout << '\n' << endl;

	ConvertToUpper(passengerFirstName);
	ConvertToUpper(passengerLastName);
	ConvertToUpper(passengerEmail);

	PlanePassenger passenger(passengerFirstName, passengerLastName, passengerEmail);
	Flight passengerInfoFlight;
	for (unsigned int i = 0; i < flights.size(); i++)
	{		
		passenger = flights[i].FindPassenger(passenger);
		if (!passenger.GetBirthDate().empty())
		{
			passengerInfoFlight = flights[i];
			break;
		}
	}	
	if (!passenger.GetBirthDate().empty())
	{
		passenger.DisplayPassengerInfo();
		passengerInfoFlight.DisplayFlightInfo();
		cout << "---------------------------------------" << endl;
	}
	else
	{
		cout << "Passenger not found." << endl;
	}
}

void ConvertToUpper(string& string)
{
	transform(string.begin(), string.end(), string.begin(), toupper);
}



