#include <Save.hpp>
#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>

namespace smpl {
///	\brief Save an SMPLModel as an FBX file
///	\param	filepath	The path to save the fbx file
///	\param	model		The smpl model to save
void SaveFBX(const std::string& filepath, const SMPLModel& model)
{
	/// Initialize the FBX manager
	FbxManager* lSdkManager = FbxManager::Create();
	/// Create fbx io settings
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	/// Create the exporter
	FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
	const char* fpath = filepath.c_str();
	if (!lExporter->Initialize(fpath, -1, lSdkManager->GetIOSettings()))
	{
		std::string errorstr = "Failed to initialize the FBXSDK Exporter: " + std::string(lExporter->GetStatus().GetErrorString());
		throw std::runtime_error(errorstr);
	}
	/// Create our Fbx Scene
	FbxScene* lScene = FbxScene::Create(lSdkManager, "SMPLXScene");
	FbxNode* lRootNode = lScene->GetRootNode();
	///=================
	/// Scene Population
	///=================
	FbxNode* lMeshNode = FbxNode::Create(lScene, "SMPLMeshNode");
	FbxMesh* lMesh = FbxMesh::Create(lScene, "SMPLMesh");
	lMeshNode->SetNodeAttribute(lMesh);
	lRootNode->AddChild(lMeshNode);
	std::vector<FbxVector4> meshVertices(model.Vertices.size());
	/// Convert SMPL's vertices to fbx vertices
	for (int pos = 0; pos < model.Vertices.size(); ++pos)
	{
		meshVertices[pos] 
			= FbxVector4(model.Vertices[pos].x, model.Vertices[pos].y, model.Vertices[pos].z);
	}
	/// Convert faces to control points
	lMesh->InitControlPoints(model.Faces.size());
	FbxVector4* lControlPoints = lMesh->GetControlPoints();
	for (int pos = 0; pos < model.Faces.size(); ++pos)
	{
		lControlPoints[pos] = meshVertices[model.Faces[pos].x];
	}
	/// Export the scene
	lExporter->Export(lScene);
	/// cleanup
	lScene->Destroy();
	lExporter->Destroy();
	lSdkManager->Destroy();
}
}	///	!namespace smpl