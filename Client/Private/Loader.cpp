#include "pch.h"
#include "..\Public\Loader.h"

#include "GameInstance.h"

#include "BackGround.h"

#include "Camera_Free.h"
#include "Player.h"
#include "Player_Tanjiro.h"

#include "StaticMapObject.h"
#include "TerrainMapObject.h"
#include "RotationMapObject.h"
#include "Sky.h"

CLoader::CLoader(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: m_pDevice{ pDevice }
	, m_pContext{pContext}
{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

unsigned int APIENTRY Loading_Main(void* pArg)
{
	CLoader* pLoader = (CLoader*)pArg;

	CoInitializeEx(nullptr, 0);

	EnterCriticalSection(pLoader->Get_CS());

	HRESULT	hr = 0;

	switch (pLoader->Get_LevelID())
	{
	case LEVEL_LOGO:
		if (false == pLoader->Get_Loaded())
		{
			hr = pLoader->LoadingForLogo();
		}
		else
		{
			pLoader->Set_Finished();
		}
		break;
	case LEVEL_GAMEPLAY:
		if (false == pLoader->Get_Loaded())
		{
			hr = pLoader->LoadingForGamePlay();
		}
		else
		{
			pLoader->Set_Finished();
		}
		break;
	case LEVEL_VILLAGE:
		if (false == pLoader->Get_Loaded())
		{
			hr = pLoader->LoadingForVillage();
		}
		else
		{
			pLoader->Set_Finished();
		}
		break;
	case LEVEL_HOUSE:
		if (false == pLoader->Get_Loaded())
		{
			hr = pLoader->LoadingForHouse();
		}
		else
		{
			pLoader->Set_Finished();
		}
		break;
	case LEVEL_TRAIN:
		if (false == pLoader->Get_Loaded())
		{
			hr = pLoader->LoadingForTrain();
		}
		else
		{
			pLoader->Set_Finished();
		}
		break;
	case LEVEL_FINALBOSS:
		if (false == pLoader->Get_Loaded())
		{
			hr = pLoader->LoadingForFinalBoss();
		}
		else
		{
			pLoader->Set_Finished();
		}
		break;
	}

	if (FAILED(hr))
		return 1;

	LeaveCriticalSection(pLoader->Get_CS());

	return 0;
}

HRESULT CLoader::Initialize(LEVELID eLevelID)
{
	m_eLevelID = eLevelID;

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (nullptr != pGameInstance->Get_LoadedStage(m_eLevelID))
		m_isLoaded = true;

	Safe_Release(pGameInstance);

	InitializeCriticalSection(&m_CS);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Loading_Main, this, 0, nullptr);
	if (0 == m_hThread)
	{
		MSG_BOX("Failed to BeginThread");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLoader::LoadingForLogo()
{
	SetWindowText(g_hWnd, TEXT("LoadingForLogo"));

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region COMPONENTS

	SetWindowText(g_hWnd, TEXT("Loading Texture..."));
#pragma region Texture

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Model..."));
#pragma region Model

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Shader..."));
#pragma region Shader

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading ETC..."));
#pragma region Etc

#pragma endregion

	
#pragma endregion

#pragma region GAMEOBJECTS

	SetWindowText(g_hWnd, TEXT("Loading GameObject..."));
#pragma region Object
	
#pragma endregion

#pragma region UI
	/* Protoype_GameObject_BackGround */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_BackGround");
		return E_FAIL;
	}
#pragma endregion

#pragma region Particale

#pragma endregion

#pragma region Effect

#pragma endregion

	

#pragma endregion

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("Loading Finished!!!"));
	m_isFinished = true;
	
	return S_OK;
}

HRESULT CLoader::LoadingForGamePlay()
{
	SetWindowText(g_hWnd, TEXT("LoadingForStage"));

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region COMPONENTS

	SetWindowText(g_hWnd, TEXT("Loading Texture..."));
#pragma region Texture
		
#pragma region EnvironmentTexture
	/* For.Prototype_Component_Texture_TerrainMask*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_TerrainMask"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Models/Environments/Map/Acaza_vs/Filter.bmp")))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Splating*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Splating"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Models/Environments/Map/Acaza_vs/T_d_114_RiceField_01a_BC.dds")))))
		return E_FAIL;

#pragma endregion

#pragma region RampTexture

#pragma endregion

#pragma region EffectTexture

#pragma endregion

#pragma region UITexture

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Model..."));
#pragma region Model

#pragma region Buffer
	
#pragma endregion
	_matrix		PivotMatrix = XMMatrixIdentity();
#pragma region Effect

#pragma endregion
	
#pragma region Character
	/* Prototype_Component_Model_Tanjiro */
	PivotMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tanjiro"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, "../Bin/Resources/Models/Tanjiro/Tanjiro.bin", PivotMatrix))))
	{
		MSG_BOX("Failed to Add_Prototype_Model_Tanjiro");
		return E_FAIL;
	}
#pragma endregion

#pragma region NonCharacter
	/* Prototype_Component_Model_TestBox */
	PivotMatrix = XMMatrixTranslation(-21.9f, 215.2f, -158.6f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_TestBox"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, "../Bin/Resources/Models/TestBox/mdlChest2.bin", PivotMatrix))))
	{
		MSG_BOX("Failed to Add_Prototype_Model_TestBox");
		return E_FAIL;
	}
#pragma endregion

#pragma region Terrain

	Load_MapObjectModel();	// 맵 오브젝트 로드(안원 전용)

	/* Prototype_Component_Navigation */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pContext, TEXT("../Bin/Data/Navigation.dat")))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Navigation");
		return E_FAIL;
	}
#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Shader..."));
#pragma region Shader
	/* Prototype_Component_Shader_VtxNorTex */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxNorTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX_DECL::Elements, VTXNORTEX_DECL::iNumElements))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Shader_VtxNorTex");
		return E_FAIL;
	}

	/* Prototype_Component_Shader_VtxModel */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxModel.hlsl"), VTXMODEL_DECL::Elements, VTXMODEL_DECL::iNumElements))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Shader_VtxModel");
		return E_FAIL;
	}

	/* Prototype_Component_Shader_VtxAnimModel */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxAnimModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxAnimModel.hlsl"), VTXANIMMODEL_DECL::Elements, VTXANIMMODEL_DECL::iNumElements))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Shader_VtxAnimModel");
		return E_FAIL;
	}

	/* Prototype_Component_Shader_VtxTerrainModel */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxTerrainModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxTerrainModel.hlsl"), VTXMODEL_DECL::Elements, VTXMODEL_DECL::iNumElements))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Shader_VtxTerrainModel");
		return E_FAIL;
	}
#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading ETC..."));
#pragma region Etc

	/* Prototype_Component_Collider_AABB */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_AABB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_AABB))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Collider_AABB");
		return E_FAIL;
	}

	/* Prototype_Component_Collider_OBB */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_OBB"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_OBB))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Collider_OBB");
		return E_FAIL;
	}

	/* Prototype_Component_Collider_Sphere */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_Sphere"),
		CCollider::Create(m_pDevice, m_pContext, CCollider::TYPE_SPHERE))))
	{
		MSG_BOX("Failed to Add_Prototype_Component_Collider_Sphere");
		return E_FAIL;
	}


#pragma endregion

#pragma endregion

#pragma region GAMEOBJECTS

	SetWindowText(g_hWnd, TEXT("Loading GameObject..."));
#pragma region Object
	/* Prototype_GameObject_Camera_Free */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Free"),
		CCamera_Free::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_Camera_Free");
		return E_FAIL;
	}

	/* Prototype_GameObject_Player */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player"),
		CPlayer::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_Player");
		return E_FAIL;
	}

	/* Prototype_GameObject_Player_Tanjiro */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Tanjiro"),
		CPlayer_Tanjiro::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_Player_Tanjiro");
		return E_FAIL;
	}
#pragma endregion

#pragma region Environment
	/* For.Prototype_GameObject_StaticMapObject */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StaticMapObject"),
		CStaticMapObject::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_StaticMapObject");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TerrainMapObject */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TerrainMapObject"),
		CTerrainMapObject::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_TerrainMapObject");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_RotationMapObject */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RotationMapObject"),
		CRotationMapObject::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_RotationMapObject");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Sky */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sky"),
		CSky::Create(m_pDevice, m_pContext))))
	{
		MSG_BOX("Failed to Add_Prototype_GameObject_Sky");
		return E_FAIL;
	}
#pragma endregion

#pragma region UI

#pragma endregion

#pragma region Particale

#pragma endregion

#pragma region Effect

#pragma endregion

#pragma endregion

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("Loading Finished!!!"));
	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::LoadingForVillage()
{
	SetWindowText(g_hWnd, TEXT("LoadingForVillage"));

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region COMPONENTS

	SetWindowText(g_hWnd, TEXT("Loading Texture..."));
#pragma region Texture

#pragma region EnvironmentTexture

#pragma endregion

#pragma region RampTexture

#pragma endregion

#pragma region EffectTexture

#pragma endregion

#pragma region UITexture

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Model..."));
#pragma region Model

#pragma region Buffer

#pragma endregion
	_matrix		PivotMatrix = XMMatrixIdentity();
#pragma region Effect

#pragma endregion

#pragma region Character
	
#pragma endregion

#pragma region NonCharacter

#pragma endregion

#pragma region Terrain

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Shader..."));
#pragma region Shader
	
#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading ETC..."));
#pragma region Etc

#pragma endregion

#pragma endregion

#pragma region GAMEOBJECTS

	SetWindowText(g_hWnd, TEXT("Loading GameObject..."));
#pragma region Object
	
#pragma endregion

#pragma region Environment
	
#pragma endregion

#pragma region UI

#pragma endregion

#pragma region Particale

#pragma endregion

#pragma region Effect

#pragma endregion

#pragma endregion

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("Loading Finished!!!"));
	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::LoadingForHouse()
{
	SetWindowText(g_hWnd, TEXT("LoadingForHouse"));

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region COMPONENTS

	SetWindowText(g_hWnd, TEXT("Loading Texture..."));
#pragma region Texture

#pragma region EnvironmentTexture

#pragma endregion

#pragma region RampTexture

#pragma endregion

#pragma region EffectTexture

#pragma endregion

#pragma region UITexture

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Model..."));
#pragma region Model

#pragma region Buffer

#pragma endregion
	_matrix		PivotMatrix = XMMatrixIdentity();
#pragma region Effect

#pragma endregion

#pragma region Character

#pragma endregion

#pragma region NonCharacter
	
#pragma endregion

#pragma region Terrain

	
#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Shader..."));
#pragma region Shader
	
#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading ETC..."));
#pragma region Etc

#pragma endregion

#pragma endregion

#pragma region GAMEOBJECTS

	SetWindowText(g_hWnd, TEXT("Loading GameObject..."));
#pragma region Object
	
#pragma endregion

#pragma region Environment
	
#pragma endregion

#pragma region UI

#pragma endregion

#pragma region Particale

#pragma endregion

#pragma region Effect

#pragma endregion

#pragma endregion

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("Loading Finished!!!"));
	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::LoadingForTrain()
{
	SetWindowText(g_hWnd, TEXT("LoadingForTrain"));

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region COMPONENTS

	SetWindowText(g_hWnd, TEXT("Loading Texture..."));
#pragma region Texture

#pragma region EnvironmentTexture

#pragma endregion

#pragma region RampTexture

#pragma endregion

#pragma region EffectTexture

#pragma endregion

#pragma region UITexture

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Model..."));
#pragma region Model

#pragma region Buffer

#pragma endregion
	_matrix		PivotMatrix = XMMatrixIdentity();
#pragma region Effect

#pragma endregion

#pragma region Character

#pragma endregion

#pragma region NonCharacter
	
#pragma endregion

#pragma region Terrain

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Shader..."));
#pragma region Shader
	
#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading ETC..."));
#pragma region Etc

#pragma endregion

#pragma endregion

#pragma region GAMEOBJECTS

	SetWindowText(g_hWnd, TEXT("Loading GameObject..."));
#pragma region Object
	
#pragma endregion

#pragma region Environment
	
#pragma endregion

#pragma region UI

#pragma endregion

#pragma region Particale

#pragma endregion

#pragma region Effect

#pragma endregion

#pragma endregion

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("Loading Finished!!!"));
	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::LoadingForFinalBoss()
{
	SetWindowText(g_hWnd, TEXT("LoadingForFinalBoss"));

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region COMPONENTS

	SetWindowText(g_hWnd, TEXT("Loading Texture..."));
#pragma region Texture

#pragma region EnvironmentTexture
	
#pragma endregion

#pragma region RampTexture

#pragma endregion

#pragma region EffectTexture

#pragma endregion

#pragma region UITexture

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Model..."));
#pragma region Model

#pragma region Buffer

#pragma endregion
	_matrix		PivotMatrix = XMMatrixIdentity();
#pragma region Effect

#pragma endregion

#pragma region Character
	
#pragma endregion

#pragma region NonCharacter
	
#pragma endregion

#pragma region Terrain

#pragma endregion

#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading Shader..."));
#pragma region Shader
	
#pragma endregion

	SetWindowText(g_hWnd, TEXT("Loading ETC..."));
#pragma region Etc

#pragma endregion

#pragma endregion

#pragma region GAMEOBJECTS

	SetWindowText(g_hWnd, TEXT("Loading GameObject..."));
#pragma region Object

#pragma endregion

#pragma region Environment

#pragma endregion

#pragma region UI

#pragma endregion

#pragma region Particale

#pragma endregion

#pragma region Effect

#pragma endregion

#pragma endregion

	Safe_Release(pGameInstance);

	SetWindowText(g_hWnd, TEXT("Loading Finished!!!"));
	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Load_MapObjectModel()
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	_matrix			PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.f));

	// ===============BattleMap Acaza======================

	/* For.Prototype_Component_Model_BattleMap_Acaza*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BattleMap_Acaza"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/BattleMap_Acaza.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_BrokenLocomotive_01*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BrokenLocomotive_01"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/BrokenLocomotive_01.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_BrokenLocomotive_01c*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BrokenLocomotive_01c"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/BrokenLocomotive_01c.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_Sky*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Sky"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/Sky.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_Far_01a*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Far_01a"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/Far_01a.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_Far_02a*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Far_02a"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/Far_02a.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_Far_04a*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Far_04a"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/Far_04a.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_far_hill_01a*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_far_hill_01a"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/far_hill_01a.bin", PivotMatrix))))
		return E_FAIL;
	/* For.Prototype_Component_Model_far_hill_02a*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_far_hill_02a"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/Environments/Map/Acaza_vs/far_hill_02a.bin", PivotMatrix))))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

CLoader* CLoader::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVELID eLevelID)
{
	CLoader* pInstance = new CLoader(pDevice, pContext);

	if (FAILED(pInstance->Initialize(eLevelID)))
	{
		MSG_BOX("Failed to Create : CLoader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CS);

	CloseHandle(m_hThread);

	Safe_Release(m_pContext);
	Safe_Release(m_pDevice);
}
