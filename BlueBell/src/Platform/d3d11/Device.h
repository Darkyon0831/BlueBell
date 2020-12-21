#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "../../Helpers/Singleton.h"

#include <d3d11.h>

namespace BlueBell
{
	class Device : public Singleton<Device>
	{
	public:

		Device();
		~Device();

		ID3D11Device* GetDevice() { return m_pDevice; }
		ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
	};
}

#endif // !__DEVICE_H__
