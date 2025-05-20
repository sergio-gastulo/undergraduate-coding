#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    string line;
    int i;

    cout << "Enter an integer: "; 
    getline(cin, line);

    istringstream iss(line);

    if (iss >> i && iss.eof())
    {
        cout << "Successfull" << endl;
        cout << i+1 << endl;
    }
    else
    {
        cout << "Invalid" << endl;
    }
    
    return 0;
}