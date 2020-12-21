#ifndef __BB_OVERLAY_H__
#define __BB_OVERLAY_H__

#include "../Container/Vector.h"

namespace BlueBell
{
	class Overlay
	{
	public:

		enum VariableType
		{
			Int,
			Float,
			Vector2D,
			Vector3D
		};

		struct Variable
		{
			Variable(void* _pMem, const char* _name, VariableType _type) : pMem(_pMem), name(_name), type(_type) {}

			void* pMem;
			const char* name;
			VariableType type;
		};

		Overlay(const char* name);
		Overlay(std::initializer_list<Variable> initList, const char* name);
		~Overlay();

		void AddVariable(void* pMem, const char* name, VariableType type) { m_variables.EmplaceBack(pMem, name, type); }

		void Render();

	private:

		Vector<Variable> m_variables;

		const char* m_name;
		int m_corner;
		bool m_open;
	};
}

#endif // !__BB_OVERLAY_H__
