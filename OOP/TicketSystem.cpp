#include<string>
#include<iomanip>
#include<iostream>
#include<sstream>


class Ticket {
private:
    int _children, _adult, _aged;
    const double children_ticket_price = 15;
    const double adult_ticket_price    = 20;
    const double aged_ticket_price     = 10;
    const std::string currency      = "$";
public:
    Ticket(int children = 0, int adult = 0, int aged = 0) : 
        _children(children), _adult(adult), _aged(aged) 
        {}
    
    void set(int children, int adult, int aged) {
        this->_children    = children;
        this->_adult       = adult;
        this->_aged        = aged;
    }

    void print() {
        int precision   = 2;        // only two decimals for printing currency
        int print_length = 25;      // length of string
        int offset       = 12;      // alignment2
        char sep        = '*';

        double  total =     _adult * adult_ticket_price;
                total +=    _children * children_ticket_price; 
                total +=    _aged * aged_ticket_price;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << "Ticket Selling Machine TSM" << std::endl;
        
        oss << std::left << std::setw(print_length)
            << "Adult tickets sold: " << _adult
            << std::right << std::setw(offset)
            << " = " << currency  << _adult * adult_ticket_price 
            << std::endl 

            << std::left << std::setw(print_length)
            << "Children tickets sold: " << _children 
            << std::right << std::setw(offset)
            << " = " << currency  << _children * children_ticket_price 
            << std::endl
            
            << std::left << std::setw(print_length)
            << "Aged man tickets sold: " << _aged 
            << std::right << std::setw(offset)
            << " = " << currency 
            << _aged * aged_ticket_price 
            << std::endl
            
            << std::setw(print_length + offset) 
            << std::setfill(sep) << '\n'
            
            << std::left << std::setw(print_length)
            << "TOTAL PRICE"
            << std::right << std::setw(offset) 
            << " = " << currency << total << std::endl;
        
        std::cout << oss.str();
    }

    friend std::istream& operator>>(std::istream& in, Ticket& ticket) {
        std::cout << "Enter the number of tickets per type." << std::endl;
        std::cout << "Children: \t";    std::cin >> ticket._children;
        std::cout << "Adults: \t";      std::cin >> ticket._adult;
        std::cout << "Aged men: \t";    std::cin >> ticket._aged;
        return in;
    }

    ~Ticket(){}
};


int main(int argc, char* argv[]) {
    
    Ticket ticket;

    if (argc == 4) {
        ticket.set(
            std::strtol(argv[1], NULL, 10), 
            std::strtol(argv[2], NULL, 10), 
            std::strtol(argv[3], NULL, 10)
        );
    } else {
        std::cout 
            << "One can specify the number of tickets beforehand:" << std::endl 
            << "    [a.exe] [children] [adult] [aged]" << std::endl; 
        std::cin >> ticket;
    }
    ticket.print();
    return 0;
}