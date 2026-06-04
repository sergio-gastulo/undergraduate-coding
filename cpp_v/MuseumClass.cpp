#include<string>
#include<sstream>
#include<iomanip>
#include<iostream>
#include<memory>
#include<random>

#define DEFAULT_SETW_SIZE 20


// https://stackoverflow.com/a/60198074/29272030
namespace uuid {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }
}


class Printable {
public:
    virtual std::ostringstream tostr(int padding) = 0;
    void print(int padding) {
        std::ostringstream oss = tostr(padding);
        std::cout << oss.str();
    }
};


class Pearson : public Printable {
protected:
    std::string _name;
    std::string _id;
    int _age;
public:
    Pearson(std::string name, int age) : 
        _name(name), _id(uuid::generate_uuid_v4()), _age(age) {}

    std::ostringstream tostr(int padding) {
        std::ostringstream oss;
        oss << std::left    << std::setw(padding) 
            << "Name: "     << _name << std::endl
            << std::left    << std::setw(padding) 
            << "ID: "       << _id   << std::endl;
        return oss;
    }
    virtual ~Pearson() = default;
};


class Employee : virtual public Pearson {
protected:
    std::string _employee_id;
public:
    Employee(const Pearson& p) :
        Pearson(p), _employee_id(uuid::generate_uuid_v4()) {}

    std::ostringstream tostr(int padding) {
        std::ostringstream oss = Pearson::tostr(padding);
        oss << std::left      << std::setw(padding) 
            << "EmployeeID: " << _employee_id << std::endl;
        return oss;
    }
    virtual ~Employee() = default;
};


class Visitor : virtual public Pearson {
protected:
    // ISO format btw
    std::string _first_visit;
    std::string _last_visit;
    int _count;
public:
    Visitor(const Pearson& p, std::string first_visit):
        Pearson(p), _first_visit(first_visit), 
        _count(1), _last_visit(first_visit) {}

    std::ostringstream tostr(int padding) {
        std::ostringstream oss = Pearson::tostr(padding);
        oss << std::left << std::setw(padding) 
            << "First visit: " << _first_visit << std::endl
            << std::left << std::setw(padding)
            << "Last visit: " << _last_visit  << std::endl
            << std::left << std::setw(padding)
            << "Number of visits: " << _count << std::endl; 
        return oss;
    }

    void visit(std::string date) { 
        _count++;
        if (date > _last_visit)
            _last_visit = date;
    }
    
    virtual ~Visitor() = default;
};


class Student : virtual public Visitor {
private:
    std::string _student_id;
    std::string _college;
public:

    Student(const Visitor& v, std::string college) : 
        Pearson(v), Visitor(v),
        _college(college), _student_id(uuid::generate_uuid_v4()) 
        {}

    bool getDiscount() {
        int min_visits_for_discount = 5;
        return (_count > min_visits_for_discount);
    }

    ~Student(){}
};


int main () {
    
    // Pepe is a 19yo guy
    auto pepe = std::make_unique<Pearson>("Pepe Cartagena", 19);
    
    // He went to a museum on October 15th 2023
    pepe = std::make_unique<Visitor>(*pepe, "2023-10-15");
 
    // He went for a visit to a museum two days later
    pepe->print(DEFAULT_SETW_SIZE);
    return 0;

}