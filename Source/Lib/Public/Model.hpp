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
	std::map<std::string, unsigned int> PartNames;
	std::vector<std::vector<float>>		SkinningWeights;
	std::vector<std::vector<float>>		JRegressor;
	std::vector<std::vector<std::vector<float>>>	ShapeDirections;
	std::vector<std::vector<float>>		HandsComponentsL;
	std::vector<std::vector<float>>		HandsComponentsR;
	std::vector<std::vector<float>>		HandCoefficientsL;
	std::vector<std::vector<float>>		HandCoefficientsR;
	std::vector<std::vector<unsigned int>> DynamicLMKFacesIdx;
};	///	!struct Model
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_MODEL_HPP__