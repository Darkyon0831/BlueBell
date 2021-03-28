#include "Importer.h"

namespace BlueFBX
{
	void Importer::Import(const std::string& filePath)
	{
		FbxManager* sdkManager = FbxManager::Create();

		FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
		sdkManager->SetIOSettings(ios);

		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_MATERIAL, true);
		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_TEXTURE, true);
		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_LINK, false);
		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_SHAPE, false);
		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_GOBO, false);
		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_ANIMATION, true);
		sdkManager->GetIOSettings()->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);

		FbxImporter* importer = FbxImporter::Create(sdkManager, "");

		importer->Initialize(filePath.c_str(), -1, sdkManager->GetIOSettings());

		FbxScene* myScene = FbxScene::Create(sdkManager, "myScene"); 
		importer->Import(myScene);

		importer->Destroy();

		FbxNode* rootNode = myScene->GetRootNode();

		size_t childCount = rootNode->GetChildCount();

		for (int i = 0; i < childCount; i++)
		{
			FbxNode* node = rootNode->GetChild(i);

			if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				FbxMesh* mesh = node->GetMesh();

				FbxStringList strList;
				mesh->GetUVSetNames(strList);

				const char* meshName = mesh->GetName();

				size_t controlPointCount = mesh->GetControlPointsCount();
				size_t polygonCount = mesh->GetPolygonCount();

				size_t polygonSize = mesh->GetPolygonSize(0);

				int controlPointIndex = mesh->GetPolygonVertex(0, 2);

				FbxLayerElementArrayTemplate<FbxVector4>* normals;
				mesh->GetNormals(&normals);

				size_t numNormals = normals->GetCount();

				FbxVector4 vertex1 = mesh->GetControlPointAt(mesh->GetPolygonVertex(1, 0));
				FbxVector4 vertex2 = mesh->GetControlPointAt(mesh->GetPolygonVertex(1, 1));
				FbxVector4 vertex3 = mesh->GetControlPointAt(mesh->GetPolygonVertex(1, 2));

				FbxVector2 uv1;
				FbxVector2 uv2;
				FbxVector2 uv3;

				bool temp;

				mesh->GetPolygonVertexUV(1, 0, strList.GetItemAt(0)->mString, uv1, temp);
				mesh->GetPolygonVertexUV(1, 1, strList.GetItemAt(0)->mString, uv2, temp);
				mesh->GetPolygonVertexUV(1, 2, strList.GetItemAt(0)->mString, uv3, temp);

				FbxVector4 controlPointPos = mesh->GetControlPointAt(controlPointIndex);

				int d = 0;
			}
		}
	}
}
