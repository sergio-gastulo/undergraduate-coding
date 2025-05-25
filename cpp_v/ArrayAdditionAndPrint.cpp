/*
    From ejemplo4.cpp 
*/

#include<iostream>
#include<sstream>
#include<stdexcept>
#include<initializer_list>

using namespace std;

class Array
{
    private: 
        int dim_;
        double* array_;

    public:
        Array()
        {
            cout << "Enter dimension\n";
            cin >> dim_;
            array_ = new double[dim_];
            for (int index = 0; index < dim_; index++)
            {
                cout << "Enter '"<< index <<"' position: ";
                cin >> array_[index];
            }
        }

        Array(int dim, double arr[]) : dim_(dim), array_(arr) {}

        Array(int dim): dim_(dim)
        {
            array_ = new double[dim_];
        }

        Array(initializer_list<double> list) : dim_(list.size())
        {
            array_ = new double[dim_];
            int index = 0;
            for (auto val: list)
                array_[index++] = val;
        }

        void Print()
        {
            ostringstream oss;
            oss << "[";
            for (int index = 0; index < dim_ - 1; index++)
                oss << array_[index] << ", ";
            oss << array_[dim_ - 1] << "]";
            cout << oss.str() << endl;
        }

        Array operator+ (const Array& secondArray) const
        {
            Array result(dim_);
            if (dim_ == secondArray.dim_)
            {
                for (int index = 0; index < dim_; index++)
                    result.array_[index] = array_[index] + secondArray.array_[index];
                return result;
            }
            else
            {
                throw length_error("Different dimensions!");
            }
        }

        ~Array() { delete[] array_; } 

};

int main()
{
    Array myPrintArray;
    
    cout << "Array printed:\n";
    myPrintArray.Print();

    Array addArray{1.1, 1.2, 1.3, 1.4, 1.5};
    cout << "Sumation array:\n"; 
    addArray.Print();

    try
    {
        cout << "Result array:\n";
        (myPrintArray + addArray).Print();
    }
    catch(const length_error& e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}