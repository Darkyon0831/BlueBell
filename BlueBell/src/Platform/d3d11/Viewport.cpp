#include "Viewport.h"

BlueBell::Viewport::Viewport(float& startX, float& startY, float& width, float& height)
{
	m_viewport.TopLeftX = startX;
	m_viewport.TopLeftY = startY;
	m_viewport.Width = width;
	m_viewport.Height = height;
}

BlueBell::Viewport::~Viewport()
{
}
