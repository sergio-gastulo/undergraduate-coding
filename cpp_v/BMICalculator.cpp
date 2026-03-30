#include<iostream>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<filesystem>

#define AVG_BMI 22.5
#define MIN_HEIGHT_CM 54.6
#define MAX_NAME_LENGTH 20

using namespace std;


struct Student {
    string name;
    double height;
    double weight;
    string gender;
    double bmi;
};


void sortArray(double* pt, const int& dim) {
    double tmp;
    for (int j = 0; j < dim - 1; j++)
        if (*(pt + j) > *(pt + j + 1))
        {
            tmp = *(pt + j);
            *(pt + j) = *(pt + j + 1);
            *(pt + j + 1) = tmp;
        }
}


double getAverageArray(double* pt, const int& dim) {
    double res = 0;
    for (int i = 0; i < dim; i++)
        res += *(pt + i);
    return res / dim;
}


double getMedianArray(double* pt, const int& dim) {
    sortArray(pt, dim);
    double res;
    if (dim % 2 == 0){
        double left = *(pt + dim / 2);
        double right = *(pt + dim / 2 + 1);
        res = (left + right) / 2;
    } else {
        res = *(pt + dim / 2);
    }
    delete[] pt;
    return res;
}


void validateGender(string& str){
    while (str != "M" && str != "F")
    {
        cout << "For educational purposes, only F and M are valid genders";
        cin >> str;
        // https://stackoverflow.com/a/17793588/29272030
        for (auto & c: str) c = toupper(c);
    }
}


void validateHeight(double& height) {
    while (height < MIN_HEIGHT_CM)
    {
        cout    << "Only values greater than " << MIN_HEIGHT_CM 
                << "cm (the smallest man in history) are allowed." << endl;
        cin     >> height;
    }    
}


double calculateBMI(const double& heightCM, const double& weight) {
    double heightM = heightCM / 100;
    return weight / (heightM * heightM);
}


struct ColWidth {
    static const int height         = 15;
    static const int weight         = 15;
    static const int gender         = 06;
    static const int bmi            = 12;
    static const int name           = 20;
    // 7: number of cols + 1
    // why +1? idk it works
    static const int buffer_size    = height + weight + gender + bmi + name + 7;
};


ostringstream printStudents(Student** pt, const int& dim) {
    ostringstream oss;
    ColWidth col;
    ostringstream line;
    line << setw(col.buffer_size) << setfill('-') << "\n";
    string str_line = line.str();
    oss << str_line
        << "|" << right << setw(col.height) << "Height (cm)"
        << "|" << right << setw(col.weight) << "Weight (kg)"
        << "|" << right << setw(col.gender)  << "Gender"
        << "|" << right << setw(col.bmi) << "BMI"
        << "|" << right << setw(col.name) << "Name" 
        << "|" << endl
        << str_line;

    for (int i = 0; i < dim; i++)
        oss << "|" << right << setw(col.height) << pt[i]->height 
            << "|" << right << setw(col.weight) << pt[i]->weight
            << "|" << right << setw(col.gender)  << pt[i]->gender
            << "|" << right << setw(col.bmi) << pt[i]->bmi
            << "|" << right << setw(col.name) << pt[i]->name
            << "|" << endl
            << str_line;
    return oss;
}


Student** readStudentsFromFile(const string& filename, const int& dim) {
    Student** students = new Student*[dim];
    int i = 0;

    ifstream file(filename);
    char delimiter = ',';
    string line;
    
    while (getline(file, line)) {
        Student* s = new Student;
        
        stringstream ss(line);
        string token;
        int col = 0;
        while(getline(ss, token, delimiter)){
            switch (col) {
                case 0: s->name = token;             break;
                case 1: s->height = stod(token);     break;
                case 2: s->weight = stod(token);     break;
                case 3: s->gender = token;           break;
            }
            col++;
            s->bmi = calculateBMI(s->height, s->weight);
        }
        students[i++] = s;
    }
    return students;
}



int main(int argc, char* argv[]){
    
    // number of students
    int dim = 10;

    if (argc < 1){
        cout << "A filename must be provided.";
        return 1;
    }
    
    // Import students from file and print BMI.
    
    // check if file is valid
    ifstream file(argv[1]);
    if (!file.is_open()){
        cerr << "File not found" << argv[1] << endl;
        return 1;
    }

    // get students 
    Student** students = new Student*[dim];
    students = readStudentsFromFile(argv[1], dim);

    // print list of students
    ostringstream oss = printStudents(students, dim);
    cout << oss.str();

    // Print BMI statistics.
    double* bmi_array = new double[dim];
    for(int i = 0; i < dim; i++)
        bmi_array[i] = students[i]->bmi;

    double median = getMedianArray(bmi_array, dim);
    cout << "The median of the BMI of the students is \t" << median << endl;
    
    double mean = getAverageArray(bmi_array, dim);
    cout << "The average of the BMI of the students is \t" << mean << endl;
    
    // cleaning after program finishes
    for (int i = 0; i < dim; i++)
        delete students[i];
    delete[] students;
    delete[] bmi_array;

    return 0;
}