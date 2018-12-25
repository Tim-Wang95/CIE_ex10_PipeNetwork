#ifndef PIPENETWORK_CIE_LINALG_HPP
#define PIPENETWORK_CIE_LINALG_HPP

#include <vector>
#include <iostream>

namespace cie
{
namespace linalg
{

// Represents a full double vector
using Vector = std::vector<double>;

// Represents a full double square matrix
class Matrix
{
public:
    Matrix( ) = default;

    explicit Matrix( int n );

    Matrix( int n, double value );
    Matrix( const std::vector<Vector>& data );

    int size( ) const;

    double& operator()( int i, int j );
    const double& operator()( int i, int j ) const;

private:
    int size_;
    std::vector<double> data_;
};

// Write to an ostream, default argument is std::cout
void write( const Vector& vector, std::ostream& out = std::cout );
void write( const Matrix& matrix, std::ostream& out = std::cout );

// Euclidean norms
double norm( const Vector& vector );
double norm( const Matrix& matrix );

// Solve linear system of equations
Vector solve( const Matrix& matrix,
              const Vector& vector );


} // namespace linalg
} // namespace cie


#include "linalg_impl.hpp"

#endif // PIPENETWORK_CIE_LINALG_HPP
