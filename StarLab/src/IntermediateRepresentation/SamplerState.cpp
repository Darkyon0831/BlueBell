#include "SamplerState.h"

StarLab::SamplerState::SamplerState()
	: m_name("")
	, m_filter(MIN_MAG_MIP_LINEAR)
	, m_addressU(Clamp)
	, m_addressV(Clamp)
	, m_addressW(Clamp)
	, m_minLod(-FLT_MAX)
	, m_maxLod(FLT_MAX)
	, m_mipLodBias(0.0f)
	, m_maxAnisotropy(1)
	, m_comparisonFunc(Never)
{
}

void StarLab::SamplerState::SetFilterFromString(const std::string& string)
{
	if (string == "MIN_MAG_MIP_POINT")
		m_filter = MIN_MAG_MIP_POINT;
	else if (string == "MIN_MAG_POINT_MIP_LINEAR")
		m_filter = MIN_MAG_POINT_MIP_LINEAR;
	else if (string == "MIN_POINT_MAG_LINEAR_MIP_POINT")
		m_filter = MIN_POINT_MAG_LINEAR_MIP_POINT;
	else if (string == "MIN_POINT_MAG_MIP_LINEAR")
		m_filter = MIN_POINT_MAG_MIP_LINEAR;
	else if (string == "MIN_LINEAR_MAG_MIP_POINT")
		m_filter = MIN_LINEAR_MAG_MIP_POINT;
	else if (string == "MIN_LINEAR_MAG_POINT_MIP_LINEAR")
		m_filter = MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	else if (string == "MIN_MAG_LINEAR_MIP_POINT")
		m_filter = MIN_MAG_LINEAR_MIP_POINT;
	else if (string == "MIN_MAG_MIP_LINEAR")
		m_filter = MIN_MAG_MIP_LINEAR;
	else if (string == "ANISOTROPIC")
		m_filter = ANISOTROPIC;
	else if (string == "COMPARISON_MIN_MAG_MIP_POINT")
		m_filter = COMPARISON_MIN_MAG_MIP_POINT;
	else if (string == "COMPARISON_MIN_MAG_POINT_MIP_LINEAR")
		m_filter = COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
	else if (string == "COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT")
		m_filter = COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
	else if (string == "COMPARISON_MIN_POINT_MAG_MIP_LINEAR")
		m_filter = COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
	else if (string == "COMPARISON_MIN_LINEAR_MAG_MIP_POINT")
		m_filter = COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
	else if (string == "COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR")
		m_filter = COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	else if (string == "COMPARISON_MIN_MAG_LINEAR_MIP_POINT")
		m_filter = COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	else if (string == "COMPARISON_MIN_MAG_MIP_LINEAR")
		m_filter = COMPARISON_MIN_MAG_MIP_LINEAR;
	else if (string == "COMPARISON_ANISOTROPIC")
		m_filter = COMPARISON_ANISOTROPIC;
	else if (string == "MINIMUM_MIN_MAG_MIP_POINT")
		m_filter = MINIMUM_MIN_MAG_MIP_POINT;
	else if (string == "MINIMUM_MIN_MAG_POINT_MIP_LINEAR")
		m_filter = MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
	else if (string == "MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT")
		m_filter = MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
	else if (string == "MINIMUM_MIN_POINT_MAG_MIP_LINEAR")
		m_filter = MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
	else if (string == "MINIMUM_MIN_LINEAR_MAG_MIP_POINT")
		m_filter = MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
	else if (string == "MAXIMUM_ANISOTROPIC")
		m_filter = MAXIMUM_ANISOTROPIC;
	else if (string == "MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR")
		m_filter = MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	else if (string == "MINIMUM_MIN_MAG_LINEAR_MIP_POINT")
		m_filter = MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
	else if (string == "MAXIMUM_MIN_MAG_MIP_LINEAR")
		m_filter = MAXIMUM_MIN_MAG_MIP_LINEAR;
	else if (string == "MINIMUM_MIN_MAG_MIP_LINEAR")
		m_filter = MINIMUM_MIN_MAG_MIP_LINEAR;
	else if (string == "MINIMUM_ANISOTROPIC")
		m_filter = MINIMUM_ANISOTROPIC;
	else if (string == "MAXIMUM_MIN_MAG_MIP_POINT")
		m_filter = MAXIMUM_MIN_MAG_MIP_POINT;
	else if (string == "MAXIMUM_MIN_MAG_POINT_MIP_LINEAR")
		m_filter = MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
	else if (string == "MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT")
		m_filter = MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
	else if (string == "MAXIMUM_MIN_POINT_MAG_MIP_LINEAR")
		m_filter = MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
	else if (string == "MAXIMUM_MIN_LINEAR_MAG_MIP_POINT")
		m_filter = MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
	else if (string == "MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR")
		m_filter = MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	else if (string == "MAXIMUM_MIN_MAG_LINEAR_MIP_POINT")
		m_filter = MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
	else
		m_filter = MIN_MAG_MIP_LINEAR;
}

void StarLab::SamplerState::SetAddressModeFromString(const std::string& string, AddressMode& address)
{
	if (string == "Wrap")
		address = Wrap;
	else if (string == "Mirror")
		address = Mirror;
	else if (string == "Clamp")
		address = Clamp;
	else if (string == "Border")
		address = Border;
	else if (string == "MirrorOnce")
		address = MirrorOnce;
	else
		address = Clamp;
}

void StarLab::SamplerState::SetComparisonFuncFromString(const std::string& string)
{
	if (string == "Never")
		m_comparisonFunc = Never;
	else if (string == "Less")
		m_comparisonFunc = Less;
	else if (string == "Equal")
		m_comparisonFunc = Equal;
	else if (string == "LessEqual")
		m_comparisonFunc = LessEqual;
	else if (string == "Greater")
		m_comparisonFunc = Greater;
	else if (string == "NotEqual")
		m_comparisonFunc = NotEqual;
	else if (string == "GreaterEqual")
		m_comparisonFunc = GreaterEqual;
	else if (string == "Always")
		m_comparisonFunc = Always;
	else
		m_comparisonFunc = Never;
}
