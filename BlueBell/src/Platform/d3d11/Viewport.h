#ifndef __BB_VIEWPORT_H__
#define __BB_VIEWPORT_H__

#include <d3d11.h>

namespace BlueBell
{
	class Viewport
	{
	public:

		Viewport(float& startX, float& startY, float& width, float& height);
		~Viewport();

		void SetStartX(float& startX) { m_viewport.TopLeftX = startX; }
		void SetStartY(float& startY) { m_viewport.TopLeftY = startY; }	
		void SetWidth(float& width) { m_viewport.Width = width; }
		void SetHeight(float& height) { m_viewport.Height = height; }

		const float& GetStartX() const { return m_viewport.TopLeftX; }
		const float& GetStartY() const { return m_viewport.TopLeftY; }
		const float& GetWidth() const { return m_viewport.Width; }
		const float& GetHeight() const { return m_viewport.Height; }	

		D3D11_VIEWPORT GetD3D11Viewport() { return m_viewport; }

	private:
		D3D11_VIEWPORT m_viewport;
	};
}

#endif // !__BB_VIEWPORT_H__
