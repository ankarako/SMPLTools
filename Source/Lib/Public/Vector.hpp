#ifndef	__LIB_PUBLIC_VECTOR_HPP__
#define __LIB_PUBLIC_VECTOR_HPP__

namespace smpl {
///	\struct Vector
///	\brief a simple templated vector
///	\tparam	N			The vector's dimensionality
///	\tparam	DataType	The data type of the vector's components
template <unsigned int N, typename DataType>
struct Vector { };
///
template <typename DataType>
struct Vector<2, DataType>
{
	DataType x;
	DataType y;
};	///	!struct Vector
///
template <typename DataType>
struct Vector<3, DataType>
{
	DataType x;
	DataType y;
	DataType z;
};	///	!struct Vector
///
template <typename DataType>
struct Vector<4, DataType>
{
	DataType x;
	DataType y;
	DataType z;
	DataType w;
};	///	!struct Vector
/// typedefs
using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;
using Vector4f = Vector<4, float>;
using Vector2d = Vector<2, double>;
using Vector3d = Vector<3, double>;
using Vector4d = Vector<4, double>;
using Vector2i = Vector<2, int>;
using Vector3i = Vector<3, int>;
using Vector4i = Vector<4, int>;
using Vector2ui = Vector<2, unsigned int>;
using Vector3ui = Vector<3, unsigned int>;
using Vector4ui = Vector<4, unsigned int>;
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_VECTOR_HPP__