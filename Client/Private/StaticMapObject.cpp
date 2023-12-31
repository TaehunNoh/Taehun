#include "pch.h"
#include "..\Public\StaticMapObject.h"

#include "GameInstance.h"

CStaticMapObject::CStaticMapObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMapObject(pDevice, pContext)
{
}

CStaticMapObject::CStaticMapObject(const CStaticMapObject& rhs)
	: CMapObject(rhs)
{
}

HRESULT CStaticMapObject::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CStaticMapObject::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_MapObject_Info.iMapObjectType = MAPOBJECT_STATIC;

	return S_OK;
}

void CStaticMapObject::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
}

void CStaticMapObject::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CStaticMapObject::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CStaticMapObject* CStaticMapObject::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CStaticMapObject* pInstance = new CStaticMapObject(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CStaticMapObject");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CStaticMapObject::Clone(void* pArg)
{
	CStaticMapObject* pInstance = new CStaticMapObject(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CStaticMapObject");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStaticMapObject::Free()
{
	__super::Free();
}
