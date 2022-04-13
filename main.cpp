#include "Matrix.hpp"

using namespace zich{

int main()
{
    std::vector<double> a = {1,2,3,4,5,6,7,8,9};
    Matrix mat1(a,3,3);

    std::vector<double> b = {1,2,3,4,5,6,7,8,9};
    Matrix mat2(b,3,3);
    cout<<mat1<<endl;
}
};