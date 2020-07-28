#ifndef __LIB_PUBLIC_MODEL_HPP__
#define __LIB_PUBLIC_MODEL_HPP__

#include <Vector.hpp>
#include <vector>
#include <map>
#include <string>

namespace smpl {
///	\struct Model
///	\brief a 3d model
struct Model
{
	std::vector<Vector3f> 				Vertices;
	std::vector<Vector3ui> 				Faces;
	std::vector<Vector3f>				JointPositions;
	std::map<std::string, unsigned int>	JointNames;
};	///	!struct Model
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_MODEL_HPP__