#ifndef __LIB_PUBLIC_ANIMATION_HPP__
#define __LIB_PUBLIC_ANIMATION_HPP__

#include <Model.hpp>

namespace smpl {
///	\brief Compute the joint positions given the vertex positions and J_regressor
///	\param	model	The SMPL model
///	\return The joint positions
std::vector<Vector3d> ComputeJointPositions(const SMPLModel& model);
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_ANIMATION_HPP__