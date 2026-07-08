#include <iostream>
#include <sstream>

using namespace std;

class Matrix
{
    private:
        int rows_, columns_;
        int** matrix_;

    public:

        Matrix()
        {
            cout << "Enter the number of rows for your matrix\n";
            cin >> rows_;

            matrix_ = new int*[rows_];
            cout << "Enter the number of columns for your matrix\n";
            cin >> columns_;

            for (int row = 0; row < rows_; row++)
            {
                matrix_[row] = new int[columns_];
                for (int column = 0; column < columns_; column++)
                {
                    cout << "A[" << row << "," << column << "] = ";
                    cin >> matrix_[row][column];
                }
            }
        }

        
        enum class PrintMode
        {
            ByRow,
            ByColumn,
            FullMatrix
        };


        void printMatrix(PrintMode mode) const 
        {
            switch (mode)
            {
                case PrintMode::ByRow:
                {
                    ostringstream oss;
                    oss << "Printing Matrix pivoted by row.\n";
                    for (int row = 0; row < rows_; row++)
                    {
                        oss << "row " << row << " : [";
                        for (int col = 0; col < columns_ - 1; col++)
                            oss << matrix_[row][col] << ", ";
                        oss << matrix_[row][columns_ - 1] << "]" << endl;
                    }
                    cout << oss.str();
                    break;
                }
                
                case PrintMode::ByColumn:
                {
                    ostringstream oss;
                    oss << "Printing matrix pivoted by column.\n";
                    for (int col = 0; col < columns_; col++)
                    {
                        oss << "col " << col << ": [\n";
                        for (int row = 0; row < rows_ - 1; row++)
                            oss << "\t" << matrix_[row][col] << ",\n";
                        oss << "\t" << matrix_[rows_ - 1][col] << "\n]\n";
                    }
                    cout << oss.str();
                    break;
                }
                
                case PrintMode::FullMatrix:
                {
                    ostringstream oss;
                    oss << "Full matrix will be printed below.\n";
                    oss << "[\n";
                    for (int row = 0; row < rows_; row++)
                    {
                        oss << "\t[";
                        for (int col = 0; col < columns_; col++)
                        {
                            oss << matrix_[row][col];
                            if (col == columns_ - 1)
                                oss << "], \n";
                            else 
                                oss << ", ";
                        }
                    }
                    oss << "]\n";
                    cout << oss.str();
                    break;
                }

                default:
                    cout << "Wrong PrintMode chosen." << endl;
                    break;
            }

        }


        ~Matrix()
        {
            for (int i = 0; i < rows_; i++)
                delete[] matrix_[i];
            delete[] matrix_;           
        }

};


int main(int argc, char** argv){

    Matrix myMatrix;

    myMatrix.printMatrix(Matrix::PrintMode::ByRow);
    myMatrix.printMatrix(Matrix::PrintMode::ByColumn);
    myMatrix.printMatrix(Matrix::PrintMode::FullMatrix);

    return 0;
}

