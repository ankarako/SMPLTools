#include <Animation.hpp>

namespace smpl {
///	\brief Compute the joint positions given the vertex positions and J_regressor
///	\param	model	The SMPL model
///	\return The joint positions
std::vector<Vector3d> ComputeJointPositions(const SMPLModel& model)
{
	std::vector<Vector3d> jointPositions(model.JointNames.size());
	for (int jpos = 0; jpos < model.JRegressor.size(); ++jpos)
	{
		jointPositions[jpos] = smpl::Vector3d{ 0.0, 0.0, 0.0 };
		for (int vpos = 0; vpos < model.Vertices.size(); ++vpos)
		{
			jointPositions[jpos].x += model.JRegressor[jpos][vpos] * model.Vertices[vpos].x;
			jointPositions[jpos].y += model.JRegressor[jpos][vpos] * model.Vertices[vpos].y;
			jointPositions[jpos].z += model.JRegressor[jpos][vpos] * model.Vertices[vpos].z;
		}
	}
	return jointPositions;
}
}	///	!namespace smpl