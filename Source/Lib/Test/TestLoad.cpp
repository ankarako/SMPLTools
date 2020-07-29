#include <Load.hpp>
#include <Save.hpp>

int main(int argc, char* argv[])
{
	smpl::SMPLModel model = smpl::LoadSMPLX("D:\\_dev\\_PhD\\Resources\\SMPLX\\models\\models_smplx_v1_0\\models\\smplx\\SMPLX_FEMALE.pkl");
	smpl::SaveFBX("D:\\_dev\\_PhD\\myFirst.fbx", model);
	return 0;
}