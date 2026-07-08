#include<iostream>
using namespace std;

class Complex{
	private:
		// r: Real
		// i: Imaginary
		double r, i;
	
	public:

		Complex(double real = 0, double imaginary = 0) : r(real), i(imaginary){}
		
		void printComplex() const {
			
			if( i >= 0){
				cout << r << " + " <<  i << "i" << endl;				
			} else {
				cout << r << " - " << -i << "i" << endl;
			}
		}	

		Complex Sum(const Complex& complex) const {
			return Complex(r + complex.r, i + complex.i);
		}

		Complex Multiplication(const Complex& complex) const {
			return Complex(
				(- complex.i * i) + (complex.r * r),
				(  complex.r * i) + (complex.i * r) 
			);
		}

		Complex Conjugate() const {
			return Complex( r, -i);
		}

		~Complex(){}

		friend istream& operator>>(istream& in, Complex& complex){
			cout << "Enter real and imaginary parts \n";
			in >> complex.r >> complex.i;
			return in;
		}

};

int main(){

	Complex complex1, complex2;
	
	cin >> complex1;
	cin >> complex2;

	cout << "First complex number: \n";
	complex1.printComplex();

	cout << "Second complex number: \n";
	complex2.printComplex();

	cout << "Sum of complex1 and complex2 \n";
	complex1.Sum(complex2).printComplex();

	cout << "Multiplication of complex1 and complex2 \n";
	complex1.Multiplication(complex2).printComplex();
	
	cout << "Conjugate of complex1 \n";
	complex1.Conjugate().printComplex();
	
	return 0;

}
