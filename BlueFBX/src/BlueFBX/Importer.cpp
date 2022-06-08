#include "Importer.h"

namespace BlueFBX
{
	Importer::Importer()
	{
	}

	void Importer::Import(const std::string& filePath, Scene& scene)
	{
		m_textureNames = BlueBell::Vector<std::string>(0, scene.m_allocator);

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

		GetAllTexturesNames(filePath, scene.m_allocator);

		FbxNode* rootNode = myScene->GetRootNode();

		size_t childCount = rootNode->GetChildCount();

		BlueBell::Vector<FbxMesh*> meshes(0, scene.m_allocator);

		for (int i = 0; i < childCount; i++)
		{
			FbxNode* node = rootNode->GetChild(i);

			if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
				meshes.PushBack(node->GetMesh());
		}

		scene.InitMeshes(meshes.GetSize());

		for (int i = 0; i < meshes.GetSize(); i++)
		{
			FbxMesh* mesh = meshes.At(i);

			FbxStringList uvSetNames;
			mesh->GetUVSetNames(uvSetNames);

			const size_t polygonCount = mesh->GetPolygonCount();
			const size_t vertexCount = mesh->GetControlPointsCount();
			const size_t numTextures = m_textureNames.GetSize();
			const size_t uVSetsCount = uvSetNames.GetCount();

			size_t meshSize = sizeof(Mesh);

			Mesh* sMesh = scene.AddMesh(polygonCount, numTextures, uVSetsCount, vertexCount);

			for (int j = 0; j < polygonCount; j++)
			{
				size_t polygonSize = mesh->GetPolygonSize(j);

				Polygon* polygon = sMesh->AddPolygon(polygonSize);

				FbxLayerElementArrayTemplate<FbxVector4>* meshBinormals;
				mesh->GetBinormals(&meshBinormals, 0);
				size_t binormalCount = meshBinormals->GetCount();

				for (int n = 0; n < polygonSize; n++)
				{
					int vertexIndex = mesh->GetPolygonVertex(j, n);

					FbxVector4 sdkMeshNormal;
					Vector3D meshNormal;
					mesh->GetPolygonVertexNormal(j, n, sdkMeshNormal);
					meshNormal = { static_cast<float>(sdkMeshNormal.mData[0]), static_cast<float>(sdkMeshNormal.mData[1]), static_cast<float>(sdkMeshNormal.mData[2]) };

					polygon->SetIndex(n, mesh->GetPolygonVertex(j, n));
					polygon->SetNormal(n, meshNormal);
				}
			}

			int d = 0;
		}
	}

	void Importer::GetAllTexturesNames(const std::string& filePath, BlueBell::IAllocator* allocator)
	{
		char* filePathNoExt = reinterpret_cast<char*>(allocator->Allocate(filePath.size() + 1 - 4, alignof(char)));
		const char* filepathCStr = filePath.c_str();

		memcpy(filePathNoExt, filepathCStr, filePath.size() - 4);
		memset(&filePathNoExt[filePath.size() - 3], 0x0, 1);

		std::stringstream dirPath;
		dirPath << filePathNoExt << ".fbm" << "/";

		allocator->Deallocate(reinterpret_cast<void**>(&filePathNoExt));

		DIR* di;
		char* ptr1, *ptr2;
		int retn;
		struct dirent* dir;
		di = opendir(dirPath.str().c_str()); //specify the directory name
		if (di)
		{
			while ((dir = readdir(di)) != NULL)
			{
				ptr1=strtok(dir->d_name,".");
				ptr2=strtok(NULL,".");
				if(ptr2!=NULL)
				{
					retn=strcmp(ptr2,"dds");
					if(retn==0)
					{
						m_textureNames.PushBack(std::string(ptr1));
					}
				}
			}
			closedir(di);
		}
	}
}
