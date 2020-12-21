#ifndef __BB_ASSET_H__
#define __BB_ASSET_H__

namespace BlueBell
{
	class Asset
	{
	public:

		enum Assets
		{
			Texture,
			Shader
		};

		Asset(Assets assetType) { m_assetType = assetType; }
		virtual ~Asset() {}

		Assets& GetAssetType() { return m_assetType; }
		void SetAssetType(Assets& assetType) { m_assetType = assetType; }

	private:
		Assets m_assetType;
	};
}

#endif // !__BB_ASSET_H__
