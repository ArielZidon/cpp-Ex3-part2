#include "Matrix.hpp"

using namespace std;

namespace zich{
Matrix::Matrix(const std::vector<double> &list,int col,int row)
{
     if(row<=0 || col<=0)
    {
         throw std::invalid_argument("received negative value");
    }

       if((int)list.size()!=col*row)
    {
        throw std::invalid_argument("the matrix size and the vector are not equal");
    } 

    this->_list = list;
    this->_col = (unsigned int)col;
    this->_row = (unsigned int)row;
}

void Matrix::posSize() const
{
    if(_row<=0 || _col<=0)
    {
         throw std::invalid_argument("received negative value");
    }
}

void Matrix::sameSize(const Matrix &mat1) const
{
    if(mat1._row!=_row || mat1._col!=_col)
    {
        throw std::invalid_argument("the matrix's didnt have the same size");
    }
    
}

int Matrix::sum() const
{
    unsigned int length = this->_row*this->_col;
    int sum = 0;
    for(size_t i = 0;i<length;i++)
    {
        sum+=this->_list[i];
    }
    return sum;
}

// void Matrix::print()
// {
//     unsigned int length = this->_row*this->_col;
//     std::cout<<"[";
//     for(size_t i = 0;i<length;i++)
//     {   
//         if(((unsigned int)(i))%this->_row==0 && i!=0)
//         {
//             std::cout<<"]\n[";
//         }
//         else if(i!=0)
//             std::cout<<" ";

//         std::cout<<this->_list[i];
//     }
//     std::cout<<"]";
// }

Matrix Matrix::operator+(const Matrix & mat)
{
    if(mat._row!=this->_row || mat._col!=this->_col)
    {
        throw std::invalid_argument("the matrix's didnt have the same size");
    }
    sameSize(mat);
    unsigned int length = this->_row*this->_col;
    std::vector<double> res;
    res.resize((size_t)(length));
    for(size_t i=0;i<length;i++)
    {
        res[i]= mat._list[i]+this->_list[i];
    }
    
    return Matrix(res,(int)_col,(int)_row);
}

Matrix &Matrix::operator+=(const Matrix & mat)
{
    sameSize(mat);
   *this=(*this)+mat;
   return *this;
}

Matrix &Matrix::operator++()
{
    posSize(); 
    unsigned int length = this->_row*this->_col;
    for(size_t i=0;i<length;i++)
    {
        this->_list[i]+=1;
    }
    return *this;
}

Matrix Matrix::operator++(const int temp)
{
    Matrix copy = *this;
    this->operator++();
    return copy;
}

Matrix operator+(Matrix &mat)
{
    return mat;
    
}

Matrix Matrix::operator-(const Matrix & mat)
{
    sameSize(mat);
    unsigned int length = this->_row*this->_col;
    std::vector<double> res;
    res.resize((size_t)length);
    for(size_t i=0;i<length;i++)
    {
        res[i]= this->_list[i]-mat._list[i];
    }
    return Matrix(res,(int)_col,(int)_row);
}
Matrix &Matrix::operator-=(const Matrix & mat)
{
    sameSize(mat);
    *this=(*this)-mat;
    return *this;
}

Matrix &Matrix::operator--()
{
    posSize(); 
    unsigned int length = this->_row*this->_col;
    for(size_t i=0;i<length;i++)
    {
        this->_list[i]-=1;
    }
    return *this;
}

Matrix Matrix::operator--(const int temp)
{
    posSize();
    Matrix copy = *this;
    this->operator--();
    return copy;
}

// ########################################################################### < > >= <= == !=

bool Matrix::operator>(const Matrix & mat)
{
    sameSize(mat);
    return this->sum()>mat.sum();
    
}

bool Matrix::operator>=(const Matrix & mat)
{
    sameSize(mat);
    return this->sum()>=mat.sum();
        
}
bool Matrix::operator==(const Matrix & mat)
{
    sameSize(mat);
    unsigned int length = _col*_row;
    for(size_t i = 0;i<length;i++)
    {
        if(mat._list[i]!=this->_list[i])
        {
            return false;
        }
    }
    return true;
}
bool Matrix::operator<=(const Matrix & mat)
{
    sameSize(mat);
    return this->sum()<=mat.sum();
}

bool Matrix::operator<(const Matrix & mat)
{
    sameSize(mat);
    return this->sum()<mat.sum();
}

bool Matrix::operator!=(const Matrix & mat)
{
    sameSize(mat);
    unsigned int length = _col*_row;
    for(size_t i = 0;i<length;i++)
    {
        if(mat._list[i]!=this->_list[i])
        {
            return true;
        }
    }
    return false;
}
// ########################################################################### * *= 
double Matrix::kefel(const int Row, const Matrix & mat, const int Col)
{
    double sum = 0;
    for (size_t i = 0; i < this->_row; i++)
    {
        sum += this->_list[(size_t)(this->_row * (unsigned int)Row) + i] * mat._list[(size_t)mat._row * i +(size_t)Col];
    }
    return sum;
}

Matrix Matrix::operator*(const Matrix & mat)
{   
    if(this->_row!=mat._col)
    {
        throw runtime_error("cant make the multiplication");
    }

    vector<double> res;
    unsigned int l= _col*mat._row;
    res.resize((size_t)l);
    double mul =0;
    
      for (size_t i = 0; i <_col; i++)
        {
            for (size_t j = 0; j < mat._row; j++)
            {
                res[i * (size_t)mat._row + j] = kefel(i, mat, j); 
            }
        }

    return Matrix(res,(int)_col,(int)mat._row);   
}

Matrix Matrix::operator*=(const Matrix & mat)
{
    *this = *this * mat;
    return *this;
}

Matrix Matrix::operator*(const double mul)
{
    unsigned int length = this->_row*this->_col;
    vector<double> res;
    res.resize((size_t)length);

    for(size_t i=0;i<length;i++)
    {
        if(this->_list[i]!=0)
        {
            res[i] = this->_list[i]*mul;
        }
    }
    return Matrix(res,(int)_col,(int)_row);   
}

Matrix Matrix::operator*=(const double mul)
{
    unsigned int length = _col*_row;
    for(size_t i = 0;i<length;i++)
    {
        if(this->_list[i]!=0)
        {
            this->_list[i]*=mul;
        }
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////////// >> <<

ostream &operator<<(ostream &os, const Matrix &mat)
{
    size_t ind = 0;
    int i = 0;
    int j = 0;
    
    for (i = 0; i < mat._col-1; i++)
    {
        os << '[';
        for (j = 0; j < mat._row - 1; j++)
        {
            os << mat._list[ind++] << " ";
        }
        os << mat._list[ind++] << "]" << endl;
    }
    os << '[';
    // finel loop
    for (j = 0; j < mat._row - 1; j++)
    {
        os << mat._list[ind++] << " ";
    }
    os << mat._list[ind++] << "]";

    return os;
}


istream &operator>>(istream &os, Matrix &mat)
{
    vector<string> list = space(stringIt(os), ',');
    size_t c = list.size();
    size_t r = space(list[0], ' ').size();
    size_t index = 0;
    size_t j = 1;
    size_t i = 0;
    vector<double> matrix;
    matrix.resize(c * r);

    while(i<c)
    {
        if (i > 0)
        {
            if (list[i][0] != ' ')
            {
                throw runtime_error("sumthing get wrong");
            }   
            list[i].erase(0, 1);
 
        }

        vector<string> rowLine = space(list[i], ' ');

        if (rowLine.size() != r)
        {
            throw runtime_error("not the same size!!");
        }

        if (rowLine[0][0] != '[' || rowLine[rowLine.size() - 1].at(1) != ']')
        {
            throw runtime_error("must open and close with '[' and ']'");
        }
        rowLine[0].erase(0, 1);
        matrix[index++] = stod(rowLine[0]);
        
        while(j < rowLine.size() - 1) 
        {
            j++;
            matrix[index++] = stod(rowLine[j]);
        }

        string &finel= rowLine[j];
        finel.pop_back();
        matrix[index++] = stod(finel);
        i++;
    }

    mat = Matrix(matrix, c, r);
    return os;
}


vector<string> space(const string &str, const char c) // just get around the char c.. 
    {
        vector<string> res;
        res.resize(str.size()); 
        size_t length = 0;
        size_t i = 0;

        for (i = 0; i < res.size(); i++)
        {
            if (str[i] == c)
            {
                ++length;
            }
            else
            {
                res[length] += str[i];
            }
        }
        ++length;
        res.resize(length);
        return res;
    }

    string stringIt(istream &os)  // know how to take over the \n because student 2... just read the os until get \n to know what the size..
    {
        char c = 0;
        string res;
        while (c != '\n')
        {
            c = os.get();
            res += c;
        }
        res.pop_back();
        return res;
    }


/////////////////////////////////////////////////////////////////////////////////////////

bool operator==(const Matrix &mat1, const Matrix &mat2)
{
    if(mat1._col!=mat2._col || mat1._row!=mat2._row)
    {
        throw std::invalid_argument("the matrix didnt have the same size");
    }

    unsigned int length = mat1._row*mat1._col;
    for(size_t i=0;i<length;i++)
    {
        if(mat1._list[i]!=mat2._list[i])
        {
            return false;
        }
    }
    return true;
}

Matrix operator*(const double val, Matrix &mat)
{
    return mat * val;
}

Matrix operator-(Matrix &mat)
{
    return mat * -1;
}

}


