#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace zich{

class Matrix
{
    std::vector<double> _list;
    unsigned int _col;
    unsigned int _row;
    
    int sum() const;
    void posSize() const;
    void sameSize(const Matrix &mat1) const;

    public:

    Matrix(const std::vector<double> &list,int col,int row);
    Matrix operator+(const Matrix & mat);
    Matrix &operator+=(const Matrix & mat);
    Matrix &operator++();
    Matrix operator++(const int temp);

    Matrix operator-(const Matrix & mat);
    Matrix &operator-=(const Matrix & mat);
    Matrix &operator--();
    Matrix operator--(const int temp);

    bool operator>(const Matrix & mat);
    bool operator>=(const Matrix & mat);
    bool operator==(const Matrix & mat);
    bool operator<=(const Matrix & mat);
    bool operator<(const Matrix & mat);
    bool operator!=(const Matrix & mat);

    Matrix operator*(const Matrix & mat);
    Matrix operator*=(const Matrix & mat);
    Matrix operator*(const double mul);
    Matrix operator*=(const double mul);
    

    friend std::ostream &operator<<(ostream &os, const Matrix &mat);
    friend std::istream &operator>>(std::istream &os, Matrix &mat);
    friend Matrix operator+(Matrix &mat);
    friend Matrix operator*(const double val, Matrix &mat);
    friend Matrix operator-(Matrix &mat);
    friend bool operator==(const Matrix &mat1, const Matrix &mat2);

    void print();
    double kefel(const int Row, const Matrix & mat, const int Col);

};
vector<string> space(const string &str, const char c);
string stringIt(istream &os);
};