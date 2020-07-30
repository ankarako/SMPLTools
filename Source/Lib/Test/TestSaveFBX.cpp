#include <Load.hpp>
#include <Save.hpp>

static const char* g_Filename = "D:\\_dev\\_PhD\\Resources\\SMPLX\\models\\models_smplx_v1_0\\models\\smplx\\SMPLX_FEMALE.pkl";

int main(int argc, char* argv[])
{
	smpl::SMPLModel model = smpl::LoadSMPLX(g_Filename);
	smpl::SaveFBX("D:\\_dev\\_PhD\\myMesh.fbx", model);
	return 0;
}