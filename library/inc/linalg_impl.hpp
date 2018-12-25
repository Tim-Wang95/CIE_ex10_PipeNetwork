/*
 * Although we are not using templates we implement trivial
 * functions inline if they are called very often, such that
 * the compiler can optimize these function calls. The conse-
 * quence is that when we change something in this file we
 * have to recompile everything that includes linalg.hpp.
 */

namespace cie
{
namespace linalg
{

inline double& Matrix::operator()( int i, int j )
{
     return data_[i * size_ + j];
}

inline const double& Matrix::operator()( int i, int j ) const
{
     return data_[i * size_ + j];
}

inline int Matrix::size( ) const
{
    return size_;
}

} // namespace linalg
} // namespace cie
