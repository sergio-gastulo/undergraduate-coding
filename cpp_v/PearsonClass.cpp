#include<iostream>
#include<sstream>
#include<iomanip>
#define SETW_SIZE 20

using namespace std;

class Pearson 
{
    private:
        string name, address, gender;
        int age;
    public:
        Pearson(string _name, string _address, string _gender, int _age) : 
            name(_name), address(_address), gender(_gender), age(_age)
            {}
        ostringstream stringPearson() {
            ostringstream oss;
            oss << left << setw(SETW_SIZE) << "Name:" << name << endl; 
            oss << left << setw(SETW_SIZE) << "Address:" << address << endl; 
            oss << left << setw(SETW_SIZE) << "Gender:" << gender << endl; 
            oss << left << setw(SETW_SIZE) << "Age:" << age << endl; 
            return oss;
        }
        void printPearson() {
            ostringstream oss = this->stringPearson();
            cout << oss.str();
        }
        Pearson duplicatePearson() {
            return Pearson(name, address, gender, age);
        }
        friend string getName(Pearson& p) {
            return p.name;
        }
        ~Pearson(){}
};

class Student: virtual public Pearson {
    private:
        double avgGPA;
        string college;
    public:
        Student(
            string _name, string _address, string _gender,  int _age,
            double _avgGPA, string _college) :
            Pearson(_name, _address, _gender, _age), 
            avgGPA(_avgGPA), college(_college) 
            {}
        Student(Pearson _p, double _avgGPA, string _college) :
            Pearson(_p), avgGPA(_avgGPA), college(_college)
            {}
        ostringstream stringStudent(){
            ostringstream oss;
            oss << left << setw(SETW_SIZE) << "Average GPA:" << avgGPA << endl;
            oss << left << setw(SETW_SIZE) << "College:" << college << endl;
            return oss;
        }
        void printStudent(){
            ostringstream oss = this->stringPearson();
            oss << left << setw(SETW_SIZE) << (this->stringStudent()).str();
            cout << oss.str();
        }
        ~Student(){}
};

class Employee: virtual public Pearson {
    private: 
        double salary;
        string enterprise;
    public:
        Employee(
            string _name, string _address, string _gender,  int _age,
            double _salary, string _enterprise) :
            Pearson(_name, _address, _gender, _age), 
            salary(_salary), enterprise(_enterprise) 
            {}
        Employee(Pearson p, double _salary, string _enterprise) :
            Pearson(p), salary(_salary), enterprise(_enterprise)
            {}
        ostringstream stringEmployee(){
            ostringstream oss;
            oss << left << setw(SETW_SIZE) << "Salary:" << salary << endl;
            oss << left << setw(SETW_SIZE) << "Enterprise:" << enterprise << endl;
            return oss;
        }
        void printEmployee(){
            ostringstream oss = this->stringPearson();
            oss << left << setw(SETW_SIZE) << (this->stringEmployee()).str();
            cout << oss.str();
        };
        ~Employee(){}

};

class EmployedStudent : public Student, public Employee {
    private:
        bool isFinalYear;
    public:
        EmployedStudent(
            string _name, string _address, string _gender,  int _age,
            double _avgGPA, string _college,
            double _salary, string _enterprise,
            bool _isFinalYear) :
            Pearson(_name, _address, _gender, _age), 
            Student(_name, _address, _gender, _age, _avgGPA, _college),
            Employee(_name, _address, _gender, _age, _salary, _enterprise),
            isFinalYear(_isFinalYear)
            {}
        EmployedStudent(
            Student s, double _salary, 
            string _enterprise, bool _isFinalYear) : 
            Pearson(s),
            Student(s),
            Employee(s, _salary, _enterprise),
            isFinalYear(_isFinalYear)
            {}
        ostringstream stringEmployedStudent() {
            ostringstream oss = this->Pearson::stringPearson();
            oss << left << setw(SETW_SIZE) << (this->stringStudent()).str();
            oss << left << setw(SETW_SIZE) << (this->stringEmployee()).str();
            oss << left << setw(SETW_SIZE) << "Final Year?" << ((isFinalYear) ? "yes" : "no") << endl;
            return oss;
        }
        void printEmployedStudent() {
            ostringstream oss = this->stringEmployedStudent();
            cout << oss.str();
        }
        ~EmployedStudent(){}
};

int main(void) {

    // Panchis is a 18yo guy
    Pearson panchis = Pearson("Panchis", "Sao Paulo", "Masculine", 18);
    
    // After studying so hard, he finally made it into Harvard
    Student panchisStudent = Student(panchis, 3.6, "Harvard");
    
    // However, he had problems and was forced to work as well.
    EmployedStudent panchisEmployedStudent = EmployedStudent(
        panchisStudent, 1800.0, "Faber Castell", false
    );
    
    // See the current Panchis status
    panchisEmployedStudent.printEmployedStudent();
    return 0;
}