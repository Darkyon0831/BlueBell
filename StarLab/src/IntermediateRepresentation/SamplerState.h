#ifndef __SL_SAMPLERSTATE_H__
#define __SL_SAMPLERSTATE_H__

#include <string>

namespace StarLab
{
	class SamplerState
	{
	public:

		friend class IntermediateRepresentation;

		enum Filter
		{
			MIN_MAG_MIP_POINT = 0,
			MIN_MAG_POINT_MIP_LINEAR = 0x1,
			MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,
			MIN_POINT_MAG_MIP_LINEAR = 0x5,
			MIN_LINEAR_MAG_MIP_POINT = 0x10,
			MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
			MIN_MAG_LINEAR_MIP_POINT = 0x14,
			MIN_MAG_MIP_LINEAR = 0x15,
			ANISOTROPIC = 0x55,
			COMPARISON_MIN_MAG_MIP_POINT = 0x80,
			COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,
			COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
			COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,
			COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,
			COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
			COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,
			COMPARISON_MIN_MAG_MIP_LINEAR = 0x95,
			COMPARISON_ANISOTROPIC = 0xd5,
			MINIMUM_MIN_MAG_MIP_POINT = 0x100,
			MINIMUM_MIN_MAG_POINT_MIP_LINEAR = 0x101,
			MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x104,
			MINIMUM_MIN_POINT_MAG_MIP_LINEAR = 0x105,
			MINIMUM_MIN_LINEAR_MAG_MIP_POINT = 0x110,
			MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x111,
			MINIMUM_MIN_MAG_LINEAR_MIP_POINT = 0x114,
			MINIMUM_MIN_MAG_MIP_LINEAR = 0x115,
			MINIMUM_ANISOTROPIC = 0x155,
			MAXIMUM_MIN_MAG_MIP_POINT = 0x180,
			MAXIMUM_MIN_MAG_POINT_MIP_LINEAR = 0x181,
			MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x184,
			MAXIMUM_MIN_POINT_MAG_MIP_LINEAR = 0x185,
			MAXIMUM_MIN_LINEAR_MAG_MIP_POINT = 0x190,
			MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x191,
			MAXIMUM_MIN_MAG_LINEAR_MIP_POINT = 0x194,
			MAXIMUM_MIN_MAG_MIP_LINEAR = 0x195,
			MAXIMUM_ANISOTROPIC = 0x1d5,
		};

		enum AddressMode
		{
			Wrap = 1,
			Mirror = 2,
			Clamp = 3,
			Border = 4,
			MirrorOnce = 5,
		};

		enum ComparisonFunc
		{
			Never = 1,
			Less = 2,
			Equal = 3,
			LessEqual = 4,
			Greater = 5,
			NotEqual = 6,
			GreaterEqual = 7,
			Always = 8,
		};

		SamplerState();

		const Filter& GetFilter() const { return m_filter; }
		const AddressMode& GetAddressU() const { return m_addressU; }
		const AddressMode& GetAddressV() const { return m_addressV; }
		const AddressMode& GetAddressW() const { return m_addressW; }
		const float& GetMipLodBias() const { return m_mipLodBias; }
		const float& GetMaxAnisotropy() const { return m_maxAnisotropy; }
		const ComparisonFunc& GetComparisonFunc() const { return m_comparisonFunc; }
		const float& GetMaxLod() const { return m_maxLod; }
		const float& GetMinLod() const { return m_maxLod; }
		const std::string& GetName() const { return m_name; }

	private:

		void SetFilterFromString(const std::string& string);
		void SetAddressModeFromString(const std::string& string, AddressMode& address);
		void SetComparisonFuncFromString(const std::string& string);

		std::string m_name;
		Filter m_filter;
		AddressMode m_addressU;
		AddressMode m_addressV;
		AddressMode m_addressW;
		float m_mipLodBias;
		unsigned int m_maxAnisotropy;
		ComparisonFunc m_comparisonFunc;
		float m_minLod;
		float m_maxLod;

		// TODO: implement border color
	};
}

#endif // !__SL_SAMPLERSTATE_H__
