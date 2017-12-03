
#include "Matrix.hpp"
#include "Vector.hpp"

int main(int argc, char* argv[])
{

    Vector new_vector(5);
    Matrix new_matrix(1,3);
    Vector test= asVector(new_matrix);
    return 0;
}
