#include <Load.hpp>
#include <Save.hpp>
#include <iostream>

static const char* g_Filepath = "D:\\_dev\\_PhD\\Resources\\SMPLX\\models\\models_smplx_v1_0\\models\\smplx\\SMPLX_FEMALE.pkl";

int main(int argc, char* argv[])
{
	std::cout << "Loading SMPL-X model from: " << g_Filepath << std::endl;
	std::cout << std::endl;
	smpl::SMPLModel model = smpl::LoadSMPLX(g_Filepath);
	///========================
	/// Print Vertex Properties
	///========================
	size_t vertexCount = model.Vertices.size();
	std::cout << "Number of Vertices: " << vertexCount << std::endl;
	size_t faceCount = model.Faces.size();
	std::cout << "Number of Faces   : " << faceCount << std::endl;
	std::cout << std::endl;
	/// print joint names
	std::cout << "===========\n";
	std::cout << "Joint Names\n";
	std::cout << "===========\n";
	for (auto& j : model.JointNames)
	{
		std::cout << j.first << " : " << j.second << std::endl;
	}
	std::cout << std::endl;
	/// print part names
	std::cout << "===========\n";
	std::cout << "Part Names\n";
	std::cout << "===========\n";
	for (auto& j : model.PartNames)
	{
		std::cout << j.first << " : " << j.second << std::endl;
	}
	std::cout << std::endl;
	return 0;
}