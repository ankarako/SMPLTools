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
	/// populate the mesh's control points (i.e. the mesh's vertices)
	lMesh->InitControlPoints(model.Vertices.size());
	FbxVector4* lControlPoints = lMesh->GetControlPoints();
	unsigned int vCounter = 0;
	for (int vpos = 0; vpos < model.Vertices.size(); ++vpos)
	{
		lControlPoints[vpos] = FbxVector4(
			model.Vertices[vpos].x, 
			model.Vertices[vpos].y, 
			model.Vertices[vpos].z);
	}
	/// populate the mesh's faces
	for (int pos = 0; pos < model.Faces.size(); ++pos)
	{
		lMesh->BeginPolygon();
		lMesh->AddPolygon(model.Faces[pos].x);
		lMesh->AddPolygon(model.Faces[pos].y);
		lMesh->AddPolygon(model.Faces[pos].z);
		lMesh->EndPolygon();
	}
	/// add the skeleton?

	/// Export the scene
	lExporter->Export(lScene);
	/// cleanup
	lScene->Destroy();
	lExporter->Destroy();
	lSdkManager->Destroy();
}
}	///	!namespace smpl