#include <Load.hpp>
#include <Save.hpp>

static const char* g_Filename = "E:\\_dev\\_PhD\\SMPL\\SMPLX\\models_smplx_v1_0\\models\\smplx\\SMPLX_FEMALE.pkl";

int main(int argc, char* argv[])
{
	smpl::SMPLModel model = smpl::LoadSMPLX(g_Filename);
	smpl::SaveFBX("E:\\_dev\\_PhD\\myMesh.fbx", model);
	return 0;
}