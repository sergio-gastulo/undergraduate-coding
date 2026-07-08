#include<iostream>
#include<sstream>
#include<string>

using namespace std;


/// @brief Prompts the user for an integer input until it is valid and within the specified bounds.
/// @param integer Reference to the integer variable where the input will be stored.
/// @param lowerBound Exclusive lower limit (input must be greater than this).
/// @param upperBoud Exclusive upper limit (input must be less than this).
/// @param sentence Prompt message shown to the user before each input attempt.
void validateInputInteger(int& integer, const int& lowerBound, const int& upperBoud, const string& sentence){
	
	string line; 
	istringstream iss(line);

	while (true)
	{
		cout << sentence << endl;
		getline(cin, line);

		iss.clear();
		iss.str(line);
		
		if (iss >> integer && iss.eof())
		{
			if (integer >= upperBoud || integer <= lowerBound)
				cout << "'" << integer << "' lies outside given bounds.\n";
			else
			{
				cout << "Bounds checked, input accepted.\n";
				break;
			}
		}
		else
			cout << "Invalid input. Make sure an integer is enterred.\n";
	}
}

class TimeObject 
{
	private:
		int seconds_, minutes_, hours_;
	
	public:
		TimeObject(int s, int m, int h): seconds_(s), minutes_(m), hours_(h) {}
		TimeObject()
		{
			validateInputInteger(seconds_, 0, 60, "Enter the seconds.");
			validateInputInteger(minutes_, 0, 60, "Enter the minutes.");
			validateInputInteger(hours_, 0, 24, "Enter the hours.");
		}
		
		void Print()
		{
			ostringstream oss;
			oss << "Seconds: \t\t"	<< seconds_ << "\n" ;
			oss << "Minutes: \t\t"	<< minutes_ << "\n" ;
			oss << "Hour: \t\t\t"		<< hours_ 	<< "\n" ;
			cout << oss.str();
		}

		TimeObject Add(int, int, int); 
		TimeObject Add(TimeObject); 

		TimeObject Copy()
		{
			return TimeObject(seconds_, minutes_, hours_);
		}

		void Reset(){
			hours_		=	0;
			minutes_	=	0; 
			seconds_	=	0;
			cout << "Time has been reset.\n";
			this->Print();
		}
		
		~TimeObject() { }
};


/// @brief Adds the given time values to the current `TimeObject`. 
/// @details Yes, it normalizes overflow (e.g., 90 seconds -> 1 minute 30 seconds).
/// @param seconds Number of seconds to add.
/// @param minutes Number of minutes to add.
/// @param hours   Number of hours to add.
/// @return A new `TimeObject` with the added time.
TimeObject TimeObject::Add(int seconds, int minutes, int hours)
{
	TimeObject result = this->Copy();
	
	// seconds
	result.seconds_ += seconds;
	minutes += result.seconds_ / 60;
	result.seconds_ %= 60;

	// minutes
	result.minutes_ += minutes;
	hours += result.minutes_ / 60;
	result.minutes_ %= 60;

	// hours
	result.hours_ += hours;

	cout << "Time has been added:\n";
	result.Print();
	return result;

}

/// @brief Adds the given `TimeObject` to the current `TimeObject`. 
/// @details Yes, it normalizes overflow (e.g., 90 seconds -> 1 minute 30 seconds).
/// @param tObj The `TimeObject` that will be passed to `this`.
/// @return A new `TimeObject` with the added time.
TimeObject TimeObject::Add(TimeObject tObj)
{
	return this->Add(tObj.seconds_, tObj.minutes_, tObj.hours_);
}


int main()
{

	TimeObject inputTime;
	cout << "Printing original time enterred.\n"; 
	inputTime.Print();

	TimeObject addTime 
	{
		20, 	// seconds
		13, 	// minutes
		9 		// hours
	};

	cout << "Printing time to be added:\n";
	addTime.Print(); 

	inputTime.Add(addTime);
	
	cout << "*-*-*-*\n";
	inputTime.Reset();
	
	return 0;

}
