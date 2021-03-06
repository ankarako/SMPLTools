#ifndef __LIB_PUBLIC_MODEL_HPP__
#define __LIB_PUBLIC_MODEL_HPP__

#include <Vector.hpp>
#include <vector>
#include <map>
#include <string>

namespace smpl {
///	\struct Model
///	\brief a 3d model
struct SMPLModel
{
	std::vector<Vector3f> 							Vertices;
	std::vector<Vector3ui> 							Faces;
	std::vector<Vector3f>							JointPositions;
	std::map<unsigned int, std::string>				JointNames;
	std::map<unsigned int, std::string>				PartNames;
	std::vector<std::vector<double>>				SkinningWeights;
	std::vector<std::vector<double>>				JRegressor;
	std::vector<std::vector<std::vector<double>>>	ShapeDirections;
	std::vector<std::vector<std::vector<double>>>	PoseDirections;
	std::vector<std::vector<double>>				HandsComponentsL;
	std::vector<std::vector<double>>				HandsComponentsR;
	std::vector<std::vector<double>>				HandCoefficientsL;
	std::vector<std::vector<double>>				HandCoefficientsR;
	std::vector<std::vector<unsigned int>>			DynamicLMKFacesIdx;
	std::vector<std::vector<Vector3d>>				DynamicLMKBaryCoords;
	std::vector<double>								HandsMeanL;
	std::vector<double>								HandsMeanR;
	std::vector<unsigned int>						LMKFacesIdx;
	std::vector<Vector3d>							LMKBaryCoords;
	std::map<unsigned int, unsigned int>			KinematicTree;
};	///	!struct Model
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_MODEL_HPP__