#include <Save.hpp>
#include <Animation.hpp>
#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>
#include <algorithm>

namespace smpl {
namespace detail {
static const std::map<unsigned int, FbxSkeleton::EType> k_SkeletonTypes =
{
	{0, FbxSkeleton::eRoot },
	{1, FbxSkeleton::eLimb },
	{2, FbxSkeleton::eLimb },
	{3, FbxSkeleton::eLimb },
	{4, FbxSkeleton::eLimb },
	{5, FbxSkeleton::eLimb },
	{6, FbxSkeleton::eLimb },
	{7, FbxSkeleton::eLimb },
	{8, FbxSkeleton::eLimb },
	{9, FbxSkeleton::eLimb },
	{10, FbxSkeleton::eLimb },
	{11, FbxSkeleton::eLimb },
	{12, FbxSkeleton::eLimb },
	{13, FbxSkeleton::eLimb },
	{14, FbxSkeleton::eLimb },
	{15, FbxSkeleton::eLimb },
	{16, FbxSkeleton::eLimb },
	{17, FbxSkeleton::eLimb },
	{18, FbxSkeleton::eLimb },
	{19, FbxSkeleton::eLimb },
	{20, FbxSkeleton::eLimb },
	{21, FbxSkeleton::eLimb },
	{22, FbxSkeleton::eLimb },
	{23, FbxSkeleton::eLimb },
	{24, FbxSkeleton::eLimb },
	{25, FbxSkeleton::eLimb },
	{26, FbxSkeleton::eLimb },
	{27, FbxSkeleton::eLimb },
	{28, FbxSkeleton::eLimb },
	{29, FbxSkeleton::eLimb },
	{30, FbxSkeleton::eLimb },
	{31, FbxSkeleton::eLimb },
	{32, FbxSkeleton::eLimb },
	{33, FbxSkeleton::eLimb },
	{34, FbxSkeleton::eLimb },
	{35, FbxSkeleton::eLimb },
	{36, FbxSkeleton::eLimb },
	{37, FbxSkeleton::eLimb },
	{38, FbxSkeleton::eLimb },
	{39, FbxSkeleton::eLimb },
	{40, FbxSkeleton::eLimb },
	{41, FbxSkeleton::eLimb },
	{42, FbxSkeleton::eLimb },
	{43, FbxSkeleton::eLimb },
	{44, FbxSkeleton::eLimb },
	{45, FbxSkeleton::eLimb },
	{46, FbxSkeleton::eLimb },
	{47, FbxSkeleton::eLimb },
	{48, FbxSkeleton::eLimb },
	{49, FbxSkeleton::eLimb },
	{50, FbxSkeleton::eLimb },
	{51, FbxSkeleton::eLimb },
	{52, FbxSkeleton::eLimb },
	{53, FbxSkeleton::eLimb },
	{54, FbxSkeleton::eLimb },
	{55, FbxSkeleton::eLimb },
};
/// \brief Get a node's default position
///	\param	pNode	the node to get its position
///	\note recursively traverses the node hierarchy to get the position
FbxAMatrix GetGlobalDefaultPosition(FbxNode* pNode)
{
	FbxAMatrix lLocalPosition;
	FbxAMatrix lGlobalPosition;
	FbxAMatrix lParentGlobalPosition;

	lLocalPosition.SetT(pNode->LclTranslation.Get());
	lLocalPosition.SetR(pNode->LclRotation.Get());
	lLocalPosition.SetS(pNode->LclScaling.Get());

	if (pNode->GetParent())
	{
		lParentGlobalPosition = GetGlobalDefaultPosition(pNode->GetParent());
		lGlobalPosition = lParentGlobalPosition * lLocalPosition;
	}
	else
	{
		lGlobalPosition = lLocalPosition;
	}
	return lGlobalPosition;
}
///
void SetGlobalDefaultPosition(FbxNode* pNode, const FbxAMatrix& pGlobalPosition)
{
	FbxAMatrix lLocalPosition;
	FbxAMatrix lParentGlobalPosition;

	if (pNode->GetParent())
	{
		lParentGlobalPosition = GetGlobalDefaultPosition(pNode->GetParent());
		lLocalPosition = lParentGlobalPosition.Inverse() * pGlobalPosition;
	}
	else
	{
		lLocalPosition = pGlobalPosition;
	}
	pNode->LclTranslation.Set(lLocalPosition.GetT());
	pNode->LclRotation.Set(lLocalPosition.GetR());
	pNode->LclScaling.Set(lLocalPosition.GetS());
}
///	\brief Map the model's geometry data
///	\param	model	The SMPL model to map
///	\param	mesh	The fbx mesh to map the geometry to
void MapGeometry(const SMPLModel& model, FbxMesh* mesh)
{
	/// initialize the mesh's control points (i.e. its vertex positions)
	mesh->InitControlPoints(model.Vertices.size());
	FbxVector4* lControlPoints = mesh->GetControlPoints();
	/// assign the model's vertex positions
	for (unsigned int vpos = 0; vpos < model.Vertices.size(); ++vpos)
	{
		lControlPoints[vpos] = FbxVector4(
			model.Vertices[vpos].x,
			model.Vertices[vpos].y,
			model.Vertices[vpos].z
		);
	}
	/// populate the mesh's face indices
	for (unsigned int fpos = 0; fpos < model.Faces.size(); ++fpos)
	{
		mesh->BeginPolygon();
		mesh->AddPolygon(model.Faces[fpos].x);
		mesh->AddPolygon(model.Faces[fpos].y);
		mesh->AddPolygon(model.Faces[fpos].z);
		mesh->EndPolygon();
	}
}
/// \brief Set the model's skeleton in the fbx format
///	\param	model		The SMPL model
///	\param	meshNode	The fbx mesh node
void MapSkeleton(const SMPLModel& model, FbxScene* scene, FbxNode* meshNode, FbxMesh* mesh)
{
	/// Get the position of each joint
	std::vector<Vector3d> jointPositions = smpl::ComputeJointPositions(model);
	/// first it's better to create all the skeletons (joints or bones)
	///	and then connect them to create the skeleton tree
	std::vector<FbxSkeleton*> fbxJoints;
	std::vector<FbxNode*> fbxNodes;
	std::vector<FbxCluster*> fbxClusters;
	for (auto it = model.JointNames.begin(); it != model.JointNames.end(); ++it)
	{
		/// create the skeleton (bone) and the scene node
		FbxSkeleton* skelJoint = FbxSkeleton::Create(scene, it->second.c_str());
		FbxNode* skelNode = FbxNode::Create(scene, it->second.c_str());
		/// set the skeletong type
		skelJoint->SetSkeletonType(detail::k_SkeletonTypes.at(it->first));
		skelNode->SetNodeAttribute(skelJoint);
		/// the fbx scene tree node
		fbxJoints.emplace_back(skelJoint);
		fbxNodes.emplace_back(skelNode);
		meshNode->AddChild(skelNode);

		std::string name = it->second + "Cluster";
		FbxCluster* cluster = FbxCluster::Create(scene, name.c_str());
		cluster->SetLink(skelNode);
		cluster->SetLinkMode(FbxCluster::eTotalOne);
		fbxClusters.emplace_back(cluster);
	}
	///////////////////////
	for (int cpos = 0; cpos < fbxClusters.size(); ++cpos)
	{
		for (int vpos = 0; vpos < model.SkinningWeights.size(); ++vpos)
		{
			fbxClusters[cpos]->AddControlPointIndex(vpos, model.SkinningWeights[vpos][cpos]);
		}
	}
	for (auto it = model.KinematicTree.begin(); it != model.KinematicTree.end(); ++it)
	{
		if (it->second != UINT_MAX)
		{
			fbxNodes[it->second]->AddChild(fbxNodes[it->first]);
		}
	}
	int jpos = 0;
	for (auto& node : fbxNodes)
	{
		FbxVector4 skelPos(jointPositions[jpos].x, jointPositions[jpos].y, jointPositions[jpos].z);
		FbxAMatrix transform;
		transform.SetT(skelPos);
		transform.SetR(FbxVector4(0.0, 0.0, 0.0));
		SetGlobalDefaultPosition(node, transform);
		jpos++;
	}
	FbxSkin* skin = FbxSkin::Create(scene, "Skin");
	mesh->AddDeformer(skin);
	for (int cpos = 0; cpos < fbxClusters.size(); ++cpos)
	{
		FbxAMatrix lMatrix;
		lMatrix.SetIdentity();
		fbxClusters[cpos]->SetTransformMatrix(lMatrix);
		skin->AddCluster(fbxClusters[cpos]);
	}
	
}
}	///	!namespace detail
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
	FbxNode* lMeshNode = FbxNode::Create(lScene, "SMPL-X");
	FbxMesh* lMesh = FbxMesh::Create(lScene, "SMPLMeshGeometry");
	lMeshNode->SetNodeAttribute(lMesh);
	lRootNode->AddChild(lMeshNode);
	/// map the mesh's geometry
	detail::MapGeometry(model, lMesh);
	/// map the skeleton
	detail::MapSkeleton(model, lScene, lMeshNode, lMesh);
	/// Export the scene
	if (!lExporter->Export(lScene))
	{
		std::string errorstr = "Failed to export file: " + filepath + ". Error: " + std::string(lExporter->GetStatus().GetErrorString());
		throw std::runtime_error(errorstr);
	}
	/// cleanup
	lScene->Destroy();
	lExporter->Destroy();
	lSdkManager->Destroy();
}
}	///	!namespace smpl