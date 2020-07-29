#include <Load.hpp>
#include <Animation.hpp>

static const char* g_Filepath = "D:\\_dev\\_PhD\\Resources\\SMPLX\\models\\models_smplx_v1_0\\models\\smplx\\SMPLX_FEMALE.pkl";

int main(int argc, char* argv[])
{
	smpl::SMPLModel model = smpl::LoadSMPLX(g_Filepath);
	std::vector<smpl::Vector3d> joints = smpl::ComputeJointPositions(model);
}