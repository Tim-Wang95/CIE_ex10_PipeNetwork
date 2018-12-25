#include <stdexcept>
#include <cmath>
#include <numeric>
#include <iomanip>

#include "linalg.hpp"

#define LINALG_RUNTIME_CHECK( expr, message ) \
    if( expr )                                \
    {                                         \
         throw std::runtime_error{ message }; \
    }

namespace cie
{
namespace linalg
{

Matrix::Matrix( int n ) :
    Matrix( n, 0.0 )
{
}

Matrix::Matrix( int n, double value ) :
    size_( n ),
    data_( n * n, value )
{
}

Matrix::Matrix( const std::vector<Vector>& data ) :
    size_( data.size( ) ),
    data_( size_ * size_ )
{
    for( int i = 0; i < size_; ++i )
    {
        LINALG_RUNTIME_CHECK( static_cast<int>( data[i].size( ) ) != size_,
                              "Inconsistent input data!" )

        for( int j = 0; j < size_; ++j )
        {
            (*this)( i, j ) = data[i][j];
        }
    }
}

namespace linalghelper
{
    template<typename VectorType>
    void writeRow( const VectorType& vector, int size, std::ostream& out, int digits )
    {
        auto precision = out.precision( );

        out << std::setprecision( digits - 4 );

        for( int i = 0; i < size; ++i )
        {
            out << std::setw( digits ) << vector( i );
        }

        out << std::endl << std::setprecision( precision );
    }
}

void write( const Vector& vector, std::ostream& out )
{
    linalghelper::writeRow( [&]( int i ){ return vector[i]; }, vector.size( ), out, 12 );
}

void write( const Matrix& matrix, std::ostream& out )
{
    int size = matrix.size( );

    for( int i = 0; i < size; ++i )
    {
        linalghelper::writeRow( [&]( int j ){ return matrix( i, j ); }, size, out, 12 );
    }
}

double norm( const Vector& vector )
{
    return std::sqrt( std::inner_product( std::begin( vector ),
                                             std::end( vector ),
                                          std::begin( vector ), 0.0 ) );
}

double norm( const Matrix& matrix )
{
    double result = 0.0;

    for( int i = 0; i < matrix.size( ); ++i )
    {
        for( int j = 0; j < matrix.size( ); ++j )
        {
            result += matrix( i, j ) * matrix( i, j );
        }
    }

    return std::sqrt( result );
}

// Gaussian elimination A x = bb
Vector solve( const Matrix& matrix,
              const Vector& rhs )
{
    int n = matrix.size( );

    LINALG_RUNTIME_CHECK( matrix.size( ) != static_cast<int>( rhs.size( ) ),
                          "Matrix and vector sizes don't match!" )

    Matrix tmp = matrix;

    double tolerance = 1e-10 * norm( matrix );

    // LU decomposition without pivoting
    for( int k = 0; k < n - 1; k++)
    {
        LINALG_RUNTIME_CHECK( ( std::abs( tmp( k, k ) ) < tolerance ), "Pivot is zero!" )

        for( int i = k + 1; i < n; i++ )
        {
            tmp( i, k ) /= tmp( k, k );

            for( int j = k + 1; j < n; j++)
            {
                tmp( i, j ) -= tmp( i, k ) * tmp(k, j);
            }
        }
    }

    LINALG_RUNTIME_CHECK( ( std::abs( tmp( n - 1, n - 1 ) ) < tolerance ), "Pivot is zero!"  )

    Vector x = rhs;

    // forward substitution for L y = rhs
    for( int i = 1; i < n; i++ )
    {
        for( int j = 0; j < i; j++ )
        {
            x[i] -= tmp( i, j ) * x[j];
        }
    }

    // back substitution for U x = y
    for( int i = n - 1; i >= 0; i-- )
    {
        for( int j = i + 1; j < n; j++ )
        {
            x[i] -= tmp( i, j ) * x[j];
        }

        x[i] /= tmp( i, i );
    }

    return x;
}

} // namespace linalg
} // namespace cie

