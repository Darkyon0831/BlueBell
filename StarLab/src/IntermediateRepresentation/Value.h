#ifndef __SF_VALUE_H__
#define __SF_VALUE_H__

#include <string>

namespace StarLab 
{
	enum Type
	{
		SLUnknown = -1,
		SLFloat,
		SLFloat2,
		SLFloat3,
		SLFloat4,
		SLInt,
		SLFloat4x4
	};

	class Value
	{
	public:
		
		friend class IntermediateRepresentation;

		const Type& GetType() const { return type; } 
		const std::string& GetName() const { return name; }
		const std::string& GetSemantic() const { return semantic; }

	private:

		Type type;
		std::string name;
		std::string semantic;
	};
}

#endif // !__SF_VALUE_H__
