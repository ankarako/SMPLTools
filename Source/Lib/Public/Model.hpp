#ifndef __LIB_PUBLIC_MODEL_HPP__
#define __LIB_PUBLIC_MODEL_HPP__

#include <Vector.hpp>
#include <vector>

namespace smpl {
///	\struct Model
///	\brief a 3d model
struct Model
{
	std::vector<Vector3f> 	Vertices;
	std::vector<Vector3ui> 	Faces;
};	///	!struct Model
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_MODEL_HPP__