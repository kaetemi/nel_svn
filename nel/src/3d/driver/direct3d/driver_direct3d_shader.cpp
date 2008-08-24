/** \file driver_direct3d_shader.cpp
 * Direct 3d driver implementation
 *
 */

/* Copyright, 2000 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "stddirect3d.h"

#include "driver_direct3d.h"
#include "resource.h"

#ifdef NL_STATIC
#	include "nel/misc/path.h"
#	include "nel/misc/file.h"
#endif

using namespace std;
using namespace NLMISC;

namespace NL3D
{

// mem allocator for state records
std::allocator<uint8> CStateRecord::Allocator;


// ***************************************************************************
// The state manager with cache
// ***************************************************************************

HRESULT CDriverD3D::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
	H_AUTO_D3D(CDriverD3D_QueryInterface)
	return D3D_OK;
}

// ***************************************************************************

ULONG CDriverD3D::AddRef(VOID)
{
	H_AUTO_D3D(CDriverD3D_AddRef)
	return 0;
}

// ***************************************************************************

ULONG CDriverD3D::Release(VOID)
{
	H_AUTO_D3D(CDriverD3D_Release)
	return 0;
}

// ***************************************************************************

HRESULT CDriverD3D::LightEnable(DWORD Index, BOOL Enable)
{
	H_AUTO_D3D(CDriverD3D_LightEnable)
	enableLight ((uint8)Index, Enable!=FALSE);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetFVF(DWORD FVF)
{
	H_AUTO_D3D(CDriverD3D_SetFVF)
	// Not implemented
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	H_AUTO_D3D(CDriverD3D_SetLight)
	_LightCache[Index].Light = *pLight;
	touchRenderVariable (&_LightCache[Index]);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	H_AUTO_D3D(CDriverD3D_SetMaterial)
	setMaterialState( *pMaterial );
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetNPatchMode(FLOAT nSegments)
{
	H_AUTO_D3D(CDriverD3D_SetNPatchMode)
	// Not implemented
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetPixelShader(LPDIRECT3DPIXELSHADER9 pShader)
{
	H_AUTO_D3D(CDriverD3D_SetPixelShader)
	setPixelShader (pShader);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT RegisterCount)
{
	H_AUTO_D3D(CDriverD3D_SetPixelShaderConstantB)
	uint i;
	for (i=0; i<RegisterCount; i++)
		setPixelShaderConstant (i+StartRegister, (int*)(pConstantData+i*4));
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetPixelShaderConstantF(UINT StartRegister, CONST FLOAT* pConstantData, UINT RegisterCount)
{
	H_AUTO_D3D(CDriverD3D_SetPixelShaderConstantF)
	uint i;
	for (i=0; i<RegisterCount; i++)
		setPixelShaderConstant (i+StartRegister, pConstantData+i*4);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetPixelShaderConstantI(UINT StartRegister, CONST INT* pConstantData, UINT RegisterCount)
{
	H_AUTO_D3D(CDriverD3D_SetPixelShaderConstantI)
	uint i;
	for (i=0; i<RegisterCount; i++)
		setPixelShaderConstant (i+StartRegister, pConstantData+i*4);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	H_AUTO_D3D(CDriverD3D_SetRenderState)
	setRenderState (State, Value);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	H_AUTO_D3D(CDriverD3D_SetSamplerState)
	setSamplerState (Sampler, Type, Value);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetTexture (DWORD Stage, LPDIRECT3DBASETEXTURE9 pTexture)
{
	H_AUTO_D3D(CDriverD3D_SetTexture )
	// Look for the current texture
	uint i;
	const uint count = _CurrentShaderTextures.size();
	for (i=0; i<count; i++)
	{
		const CTextureRef &ref = _CurrentShaderTextures[i];
		if (ref.D3DTexture == pTexture)
		{
			// Set the additionnal stage set by NeL texture (D3DSAMP_ADDRESSU, D3DSAMP_ADDRESSV, D3DSAMP_MAGFILTER, D3DSAMP_MINFILTER and D3DSAMP_MIPFILTER)
			setTexture (Stage, ref.NeLTexture);
			break;
		}
	}
	if (i == count)
		setTexture (Stage, pTexture);

	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	H_AUTO_D3D(CDriverD3D_SetTextureStageState)
	if (Type == D3DTSS_TEXCOORDINDEX)
		setTextureIndexUV (Stage, Value);
	else
		setTextureState (Stage, Type, Value);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	H_AUTO_D3D(CDriverD3D_SetTransform)
	setMatrix (State, *pMatrix);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetVertexShader(LPDIRECT3DVERTEXSHADER9 pShader)
{
	H_AUTO_D3D(CDriverD3D_SetVertexShader)
	setVertexProgram (pShader, NULL);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT RegisterCount)
{
	H_AUTO_D3D(CDriverD3D_SetVertexShaderConstantB)
	uint i;
	for (i=0; i<RegisterCount; i++)
		setVertexProgramConstant (i+StartRegister, (int*)(pConstantData+i*4));
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetVertexShaderConstantF(UINT StartRegister, CONST FLOAT* pConstantData, UINT RegisterCount)
{
	H_AUTO_D3D(CDriverD3D_SetVertexShaderConstantF)
	uint i;
	for (i=0; i<RegisterCount; i++)
		setVertexProgramConstant (i+StartRegister, pConstantData+i*4);
	return D3D_OK;
}

// ***************************************************************************

HRESULT CDriverD3D::SetVertexShaderConstantI(UINT StartRegister, CONST INT* pConstantData, UINT RegisterCount)
{
	H_AUTO_D3D(CDriverD3D_SetVertexShaderConstantI)
	uint i;
	for (i=0; i<RegisterCount; i++)
		setVertexProgramConstant (i+StartRegister, pConstantData+i*4);
	return D3D_OK;
}

// ***************************************************************************

CShaderDrvInfosD3D::CShaderDrvInfosD3D(IDriver *drv, ItShaderDrvInfoPtrList it) : IShaderDrvInfos(drv, it)
{
	H_AUTO_D3D(CShaderDrvInfosD3D_CShaderDrvInfosD3D)
	Validated = false;
}

// ***************************************************************************

CShaderDrvInfosD3D::~CShaderDrvInfosD3D()
{
	H_AUTO_D3D(CShaderDrvInfosD3D_CShaderDrvInfosD3DDtor)
	Effect->Release();
}

// ***************************************************************************

bool CDriverD3D::validateShader(CShader *shader)
{
	H_AUTO_D3D(CDriverD3D_validateShader)
	CShaderDrvInfosD3D *shaderInfo = static_cast<CShaderDrvInfosD3D*>((IShaderDrvInfos*)shader->_DrvInfo);

	if (!shaderInfo->Validated)
	{
		// Choose the good method
		D3DXHANDLE hTechnique = NULL;
		D3DXHANDLE hCurrentTechnique = NULL;
		while (hTechnique == NULL)
		{
			if (shaderInfo->Effect->FindNextValidTechnique(hCurrentTechnique, &hCurrentTechnique) != D3D_OK)
				return false;

			// Info

#ifdef NL_FORCE_TEXTURE_STAGE_COUNT
			D3DXTECHNIQUE_DESC desc;
			nlverify (shaderInfo->Effect->GetTechniqueDesc(hCurrentTechnique, &desc) == D3D_OK);

			// Check this is compatible
			const uint len = strlen(desc.Name);
			if (len)
			{
				char shaderStageCount = desc.Name[len-1];
				if ((shaderStageCount>='0') && (shaderStageCount<='9'))
				{
					uint stageCount = NL_FORCE_TEXTURE_STAGE_COUNT;

					if ((uint)(shaderStageCount-'0')<=stageCount)
						// The good technique
						hTechnique = hCurrentTechnique;
				}
			}
#else // NL_FORCE_TEXTURE_STAGE_COUNT
			hTechnique = hCurrentTechnique;
#endif // NL_FORCE_TEXTURE_STAGE_COUNT

#ifdef NL_DEBUG_D3D
			{
				D3DXTECHNIQUE_DESC desc;
				nlverify (shaderInfo->Effect->GetTechniqueDesc(hCurrentTechnique, &desc) == D3D_OK);
				if (hTechnique)
					nlinfo ("Shader \"%s\" : use technique \"%s\" with %d passes.", shader->getName(), desc.Name, desc.Passes);
			}
#endif // NL_DEBUG_D3D
		}

		// Set the technique
		shaderInfo->Effect->SetTechnique(hTechnique);

		// Set the state manager
		shaderInfo->Effect->SetStateManager (this);

		shaderInfo->Validated = true;
	}
	return true;
}

// ***************************************************************************

bool CDriverD3D::activeShader(CShader *shd)
{
	H_AUTO_D3D(CDriverD3D_activeShader)
	if (_DisableHardwarePixelShader)
		return false;

	// Clear current textures
	_CurrentShaderTextures.clear();

	// Shader has been changed ?
	if (shd && shd->_ShaderChanged)
	{
		// Remove old shader
		shd->_DrvInfo.kill();

		// Already setuped ?
		CShaderDrvInfosD3D *shaderInfo = static_cast<CShaderDrvInfosD3D*>((IShaderDrvInfos*)shd->_DrvInfo);
		if ( !shd->_DrvInfo )
		{
			// insert into driver list. (so it is deleted when driver is deleted).
			ItShaderDrvInfoPtrList	it= _ShaderDrvInfos.insert(_ShaderDrvInfos.end(), NULL);
			// create and set iterator, for future deletion.
			shaderInfo = new CShaderDrvInfosD3D(this, it);
			*it= shd->_DrvInfo = shaderInfo;
		}

		// Assemble the shader
		LPD3DXBUFFER pErrorMsgs;
		if (D3DXCreateEffect(_DeviceInterface,	shd->getText(), strlen(shd->getText())+1, NULL, NULL, 0, NULL, &(shaderInfo->Effect), &pErrorMsgs)
			== D3D_OK)
		{
			// Get the texture handle
			uint i;
			for (i=0; i<CShaderDrvInfosD3D::MaxShaderTexture; i++)
			{
				string name = "texture" + toString (i);
				shaderInfo->TextureHandle[i] = shaderInfo->Effect->GetParameterByName(NULL, name.c_str());
				name = "color" + toString (i);
				shaderInfo->ColorHandle[i] = shaderInfo->Effect->GetParameterByName(NULL, name.c_str());
				name = "factor" + toString (i);
				shaderInfo->FactorHandle[i] = shaderInfo->Effect->GetParameterByName(NULL, name.c_str());
				name = "scalarFloat" + toString (i);
				shaderInfo->ScalarFloatHandle[i] = shaderInfo->Effect->GetParameterByName(NULL, name.c_str());
			}
		}
		else
		{
			nlwarning ("Can't create shader '%s':", shd->getText());
			nlwarning ((const char*)pErrorMsgs->GetBufferPointer());
			shd->_ShaderChanged = false;
			_CurrentShader = NULL;
			return false;
		}

		// Done
		shd->_ShaderChanged = false;
	}

	// Set the shader
	_CurrentShader = shd;

	return true;
}

// ***************************************************************************
// tmp for debug
static void setFX(CShader &s, const char *name, INT rsc, CDriverD3D *drv)
{
	H_AUTO_D3D(setFX)

#ifdef NL_STATIC

	// in static mode, you need to have the .fx file in a directory
	std::string path = CPath::lookup(string(name)+".fx");
	CIFile file (path.c_str());
	int size = file.getFileSize();
	std::vector<char> shaderText(size + 1, 0);
	file.serialBuffer((uint8*)&shaderText[0], size);

#else

	HRSRC hrsrc = FindResource(HInstDLL, MAKEINTRESOURCE(rsc), "FX");
	HGLOBAL hglob = LoadResource(HInstDLL, hrsrc);
	std::vector<char> shaderText(SizeofResource(HInstDLL, hrsrc) + 1, 0);
	memcpy(&shaderText[0], LockResource(hglob), shaderText.size() - 1);

#endif

	s.setName(name);
	s.setText(&shaderText[0]);
	nlverify (drv->activeShader (&s));
}

#define setFx(a,b) { setFX(a, #b, b, this); }

void CDriverD3D::initInternalShaders()
{
	H_AUTO_D3D(CDriverD3D_initInternalShaders)
	setFx(_ShaderLightmap0,lightmap0);
	setFx(_ShaderLightmap1,lightmap1);
	setFx(_ShaderLightmap2,lightmap2);
	setFx(_ShaderLightmap3,lightmap3);
	setFx(_ShaderLightmap4,lightmap4);
	setFx(_ShaderLightmap0Blend,lightmap0blend);
	setFx(_ShaderLightmap1Blend,lightmap1blend);
	setFx(_ShaderLightmap2Blend,lightmap2blend);
	setFx(_ShaderLightmap3Blend,lightmap3blend);
	setFx(_ShaderLightmap4Blend,lightmap4blend);
	setFx(_ShaderLightmap0X2,lightmap0_x2);
	setFx(_ShaderLightmap1X2,lightmap1_x2);
	setFx(_ShaderLightmap2X2,lightmap2_x2);
	setFx(_ShaderLightmap3X2,lightmap3_x2);
	setFx(_ShaderLightmap4X2,lightmap4_x2);
	setFx(_ShaderLightmap0BlendX2,lightmap0blend_x2);
	setFx(_ShaderLightmap1BlendX2,lightmap1blend_x2);
	setFx(_ShaderLightmap2BlendX2,lightmap2blend_x2);
	setFx(_ShaderLightmap3BlendX2,lightmap3blend_x2);
	setFx(_ShaderLightmap4BlendX2,lightmap4blend_x2);
	setFx(_ShaderCloud,cloud);
	setFx(_ShaderWaterNoDiffuse,water_no_diffuse);
	setFx(_ShaderWaterDiffuse,water_diffuse);
}


// ***************************************************************************

void CDriverD3D::releaseInternalShaders()
{
	H_AUTO_D3D(CDriverD3D_releaseInternalShaders)
	_ShaderLightmap0._DrvInfo.kill();
	_ShaderLightmap1._DrvInfo.kill();
	_ShaderLightmap2._DrvInfo.kill();
	_ShaderLightmap3._DrvInfo.kill();
	_ShaderLightmap4._DrvInfo.kill();
	_ShaderLightmap0Blend._DrvInfo.kill();
	_ShaderLightmap1Blend._DrvInfo.kill();
	_ShaderLightmap2Blend._DrvInfo.kill();
	_ShaderLightmap3Blend._DrvInfo.kill();
	_ShaderLightmap4Blend._DrvInfo.kill();
	_ShaderLightmap0X2._DrvInfo.kill();
	_ShaderLightmap1X2._DrvInfo.kill();
	_ShaderLightmap2X2._DrvInfo.kill();
	_ShaderLightmap3X2._DrvInfo.kill();
	_ShaderLightmap4X2._DrvInfo.kill();
	_ShaderLightmap0BlendX2._DrvInfo.kill();
	_ShaderLightmap1BlendX2._DrvInfo.kill();
	_ShaderLightmap2BlendX2._DrvInfo.kill();
	_ShaderLightmap3BlendX2._DrvInfo.kill();
	_ShaderLightmap4BlendX2._DrvInfo.kill();
	_ShaderCloud._DrvInfo.kill();
	_ShaderWaterNoDiffuse._DrvInfo.kill();
	_ShaderWaterDiffuse._DrvInfo.kill();
}

// ***************************************************************************
bool CDriverD3D::setShaderTexture (uint textureHandle, ITexture *texture, CFXCache *cache)
{
	H_AUTO_D3D(CDriverD3D_setShaderTexture )
	// Setup the texture
	if (!setupTexture(*texture))
		return false;

	// Set the main texture
	nlassert (_CurrentShader);
	CShaderDrvInfosD3D *shaderInfo = static_cast<CShaderDrvInfosD3D*>((IShaderDrvInfos*)_CurrentShader->_DrvInfo);
	nlassert (shaderInfo);
	ID3DXEffect	*effect = shaderInfo->Effect;
	CTextureDrvInfosD3D *d3dtext = getTextureD3D (*texture);
	if (texture)
	{
		if (cache)
		{
			cache->Params.setTexture(textureHandle, d3dtext->Texture);
		}
		else
		{
			effect->SetTexture (shaderInfo->TextureHandle[textureHandle], d3dtext->Texture);
		}
	}


	// Add a ref on this texture
	_CurrentShaderTextures.push_back (CTextureRef());
	CTextureRef &ref = _CurrentShaderTextures.back();
	ref.NeLTexture = texture;
	ref.D3DTexture = d3dtext->Texture;
	return true;
}

// ***************************************************************************

void CDriverD3D::disableHardwareTextureShader()
{
	// cannot disable pixel shader under DX, because it crashes with lightmap
	// => no-op
	/*
	_DisableHardwarePixelShader = true;
	_PixelShader = false;
	*/
}



// ***************************************************************************
void CDriverD3D::notifyAllShaderDrvOfLostDevice()
{
	for(TShaderDrvInfoPtrList::iterator it = _ShaderDrvInfos.begin(); it != _ShaderDrvInfos.end(); ++it)
	{
		nlassert(*it);
		CShaderDrvInfosD3D *drvInfo = NLMISC::safe_cast<CShaderDrvInfosD3D *>(*it);
		if (drvInfo->Effect)
		{
			nlverify(drvInfo->Effect->OnLostDevice() == D3D_OK);
		}
	}
}

// ***************************************************************************
void CDriverD3D::notifyAllShaderDrvOfResetDevice()
{
	for(TShaderDrvInfoPtrList::iterator it = _ShaderDrvInfos.begin(); it != _ShaderDrvInfos.end(); ++it)
	{
		nlassert(*it);
		CShaderDrvInfosD3D *drvInfo = NLMISC::safe_cast<CShaderDrvInfosD3D *>(*it);
		if (drvInfo->Effect)
		{
			//nlverify(
			drvInfo->Effect->OnResetDevice();
			//== D3D_OK);
		}
	}
}


// ***************************************************************************
// state records (for .fx caching)
// ***************************************************************************

class CStateRecordLightEnable : public CStateRecord
{
public:
	DWORD Index;
	BOOL  Enable;
public:
	CStateRecordLightEnable(DWORD index, BOOL enable) : Index(index), Enable(enable) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv.enableLight ((uint8)Index, Enable!=FALSE);
	}
};
//
class CStateRecordLight : public CStateRecord
{
public:
	DWORD	  Index;
	D3DLIGHT9 Light;
public:
	CStateRecordLight(DWORD index, const D3DLIGHT9 *pLight) : Index(index), Light(*pLight) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv._LightCache[Index].Light = Light;
		drv.touchRenderVariable (&drv._LightCache[Index]);
	}
};
//
class CStateRecordMaterial : public CStateRecord
{
public:
	D3DMATERIAL9 Material;
public:
	CStateRecordMaterial(const D3DMATERIAL9 *pMaterial) : Material(*pMaterial) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv.setMaterialState(Material);
	}
};
//
class CStateRecordPixelShader : public CStateRecord
{
public:
	LPDIRECT3DPIXELSHADER9 PixelShader;
public:
	CStateRecordPixelShader(LPDIRECT3DPIXELSHADER9 pixelShader) : PixelShader(pixelShader) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv.setPixelShader(PixelShader);
	}
};
//
class CStateRecordPixelShaderConstantB : public CStateRecord
{
public:
	std::vector<BOOL> Values;
	uint			  StartRegister;
public:
	CStateRecordPixelShaderConstantB(DWORD startRegister, const BOOL *values, DWORD countVec4) : StartRegister(startRegister)
	{
		Values.resize(countVec4 * 4);
		std::copy(values, values + countVec4 * 4, Values.begin());
	}
	virtual void apply(class CDriverD3D &drv)
	{
		const BOOL *curr = &Values[0];
		const BOOL *last = &Values[0] + Values.size();
		uint i = StartRegister;
		while (curr != last)
		{
			drv.setPixelShaderConstant (i, curr);
			curr += 4;
			++ i;
		}
	}
};
//
class CStateRecordPixelShaderConstantF : public CStateRecord
{
public:
	std::vector<FLOAT> Values;
	uint			  StartRegister;
public:
	CStateRecordPixelShaderConstantF(DWORD startRegister, const FLOAT *values, DWORD countVec4) : StartRegister(startRegister)
	{
		Values.resize(countVec4 * 4);
		std::copy(values, values + countVec4 * 4, Values.begin());
	}
	virtual void apply(class CDriverD3D &drv)
	{
		const FLOAT *curr = &Values[0];
		const FLOAT *last = &Values[0] + Values.size();
		uint i = StartRegister;
		while (curr != last)
		{
			drv.setPixelShaderConstant (i, curr);
			curr += 4;
			++ i;
		}
	}
};
//
class CStateRecordPixelShaderConstantI : public CStateRecord
{
public:
	std::vector<INT>  Values;
	uint			  StartRegister;
public:
	CStateRecordPixelShaderConstantI(DWORD startRegister, const INT *values, DWORD countVec4) : StartRegister(startRegister)
	{
		Values.resize(countVec4 * 4);
		std::copy(values, values + countVec4 * 4, Values.begin());
	}
	virtual void apply(class CDriverD3D &drv)
	{
		const INT *curr = &Values[0];
		const INT *last = &Values[0] + Values.size();
		uint i = StartRegister;
		while (curr != last)
		{
			drv.setPixelShaderConstant (i, curr);
			curr += 4;
			++ i;
		}
	}
};
//
class CStateRecordRenderState : public CStateRecord
{
public:
	D3DRENDERSTATETYPE State;
	DWORD Value;
public:
	CStateRecordRenderState(D3DRENDERSTATETYPE state, DWORD value) : State(state), Value(value) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv.setRenderState(State, Value);
	}
};
//
class CStateRecordSamplerState : public CStateRecord
{
public:
	DWORD Sampler;
	D3DSAMPLERSTATETYPE Type;
	DWORD Value;
public:
	CStateRecordSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value) : Sampler(sampler), Type(type), Value(value) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv.setSamplerState(Sampler, Type, Value);
	}
};
//
class CStateRecordTexture : public CStateRecord
{
public:
	DWORD Stage;
	CRefPtr<ITexture>      TexRef;
	LPDIRECT3DBASETEXTURE9 Texture;
	BOOL IsNelTexture;
public:
	CStateRecordTexture(DWORD stage, LPDIRECT3DBASETEXTURE9 texture, ITexture *nelTexture) : Stage(stage), Texture(texture)
	{
		nlassert(Texture);
		H_AUTO_D3D(CDriverD3D_SetTexture )
		// if not a NeL texture, should add a reference on texture, else use refptr instead
		IsNelTexture = nelTexture != NULL;
		TexRef = nelTexture;
		if (!IsNelTexture)
		{
			HRESULT r = Texture->AddRef();
			nlassert(r == D3D_OK);
		}
	}
	~CStateRecordTexture()
	{
		nlassert(Texture); // no default ctor, so texture should have been set
		if (!IsNelTexture)
		{
			nlassert(TexRef == NULL);
			HRESULT r = Texture->Release();
			nlassert(r == D3D_OK);
		}
	}
	virtual void apply(class CDriverD3D &drv)
	{
		nlassert(Texture);
		if (TexRef)
		{
			drv.setTexture(Stage, TexRef);
		}
		else
		{
			drv.setTexture(Stage, Texture);
		}
	}
};
//
class CStateRecordTextureStageState : public CStateRecord
{
public:
	DWORD Stage;
	D3DTEXTURESTAGESTATETYPE Type;
	DWORD Value;
public:
	CStateRecordTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value) : Stage(stage), Type(type), Value(value) {}
	virtual void apply(class CDriverD3D &drv)
	{
		if (Type == D3DTSS_TEXCOORDINDEX)
			drv.setTextureIndexUV (Stage, Value);
		else
			drv.setTextureState (Stage, Type, Value);
	}
};
//
class CStateRecordTransform : public CStateRecord
{
public:
	D3DTRANSFORMSTATETYPE State;
	D3DMATRIX Matrix;
public:
	CStateRecordTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *pMatrix) : State(state), Matrix(*pMatrix) {}
	virtual void apply(class CDriverD3D &drv)
	{
		drv.setMatrix(State, Matrix);
	}
};
//
class CStateRecordVertexShader : public CStateRecord
{
public:
	LPDIRECT3DVERTEXSHADER9 Shader;
public:
	CStateRecordVertexShader(LPDIRECT3DVERTEXSHADER9 shader) : Shader(shader) {}
	virtual void apply(class CDriverD3D &drv)
	{
		nlassert(0); // not supported
		//drv.setVertexProgram(Shader);
	}
};
//
class CStateRecordVertexShaderConstantB : public CStateRecord
{
public:
	std::vector<BOOL> Values;
	uint			  StartRegister;
public:
	CStateRecordVertexShaderConstantB(DWORD startRegister, const BOOL *values, DWORD countVec4) : StartRegister(startRegister)
	{
		Values.resize(countVec4 * 4);
		std::copy(values, values + countVec4 * 4, Values.begin());
	}
	virtual void apply(class CDriverD3D &drv)
	{
		const BOOL *curr = &Values[0];
		const BOOL *last = &Values[0] + Values.size();
		uint i = StartRegister;
		while (curr != last)
		{
			drv.setVertexProgramConstant(i, curr);
			curr += 4;
			++ i;
		}
	}
};
class CStateRecordVertexShaderConstantF : public CStateRecord
{
public:
	std::vector<FLOAT> Values;
	uint			   StartRegister;
public:
	CStateRecordVertexShaderConstantF(DWORD startRegister, const FLOAT *values, DWORD countVec4) : StartRegister(startRegister)
	{
		Values.resize(countVec4 * 4);
		std::copy(values, values + countVec4 * 4, Values.begin());
	}
	virtual void apply(class CDriverD3D &drv)
	{
		const FLOAT *curr = &Values[0];
		const FLOAT *last = &Values[0] + Values.size();
		uint i = StartRegister;
		while (curr != last)
		{
			drv.setVertexProgramConstant(i, curr);
			curr += 4;
			++ i;
		}
	}
};
class CStateRecordVertexShaderConstantI : public CStateRecord
{
public:
	std::vector<INT> Values;
	uint			   StartRegister;
public:
	CStateRecordVertexShaderConstantI(DWORD startRegister, const INT *values, DWORD countVec4) : StartRegister(startRegister)
	{
		Values.resize(countVec4 * 4);
		std::copy(values, values + countVec4 * 4, Values.begin());
	}
	virtual void apply(class CDriverD3D &drv)
	{
		const INT *curr = &Values[0];
		const INT *last = &Values[0] + Values.size();
		uint i = StartRegister;
		while (curr != last)
		{
			drv.setVertexProgramConstant(i, curr);
			curr += 4;
			++ i;
		}
	}
};

// state recorder
HRESULT STDMETHODCALLTYPE CFXPassRecorder::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
	nlassert(Driver);
	return Driver->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CFXPassRecorder::AddRef(VOID)
{
	nlassert(Driver);
	return Driver->AddRef();
}

ULONG STDMETHODCALLTYPE CFXPassRecorder::Release(VOID)
{
	nlassert(Driver);
	return Driver->Release();
}

#undef new

HRESULT STDMETHODCALLTYPE CFXPassRecorder::LightEnable(DWORD Index, BOOL Enable)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordLightEnable(Index, Enable));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetFVF(DWORD FVF)
{
	nlassert(0); // not managed
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordLight(Index, pLight));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordMaterial(pMaterial));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetNPatchMode(FLOAT nSegments)
{
	nlassert(0); // not managed
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetPixelShader(LPDIRECT3DPIXELSHADER9 pShader)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordPixelShader(pShader));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT RegisterCount)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordPixelShaderConstantB(StartRegister, pConstantData, RegisterCount));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetPixelShaderConstantF(UINT StartRegister, CONST FLOAT* pConstantData, UINT RegisterCount)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordPixelShaderConstantF(StartRegister, pConstantData, RegisterCount));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetPixelShaderConstantI(UINT StartRegister, CONST INT* pConstantData, UINT RegisterCount)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordPixelShaderConstantI(StartRegister, pConstantData, RegisterCount));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordRenderState(State, Value));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordSamplerState(Sampler, Type, Value));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetTexture(DWORD Stage, LPDIRECT3DBASETEXTURE9 pTexture)
{
	nlassert(Driver);
	nlassert(Target);
	// Look for the current texture
	uint i;
	const uint count = Driver->getCurrentShaderTextures().size();
	for (i=0; i<count; i++)
	{
		const CDriverD3D::CTextureRef &ref = Driver->getCurrentShaderTextures()[i];
		if (ref.D3DTexture == pTexture)
		{
			// Set the additionnal stage set by NeL texture (D3DSAMP_ADDRESSU, D3DSAMP_ADDRESSV, D3DSAMP_MAGFILTER, D3DSAMP_MINFILTER and D3DSAMP_MIPFILTER)
			Target->States.push_back(new CStateRecordTexture(Stage, pTexture, ref.NeLTexture));
			break;
		}
	}
	if (i == count)
	{
		// The texture isn't a NeL texture (was created inside driver)
		Target->States.push_back(new CStateRecordTexture(Stage, pTexture, NULL));
	}
	return D3D_OK;
}


HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordTextureStageState(Stage, Type, Value));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordTransform(State, pMatrix));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetVertexShader(LPDIRECT3DVERTEXSHADER9 pShader)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordVertexShader(pShader));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT RegisterCount)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordVertexShaderConstantB(StartRegister, pConstantData, RegisterCount));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetVertexShaderConstantF(UINT StartRegister, CONST FLOAT* pConstantData, UINT RegisterCount)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordVertexShaderConstantF(StartRegister, pConstantData, RegisterCount));
	return D3D_OK;
}

HRESULT STDMETHODCALLTYPE CFXPassRecorder::SetVertexShaderConstantI(UINT StartRegister, CONST INT* pConstantData, UINT RegisterCount)
{
	nlassert(Driver);
	nlassert(Target);
	Target->States.push_back(new CStateRecordVertexShaderConstantI(StartRegister, pConstantData, RegisterCount));
	return D3D_OK;
}

//===================================================================================
CFXPassRecord::~CFXPassRecord()
{
	for(std::vector<CStateRecord *>::iterator it = States.begin(); it != States.end(); ++it)
	{
		delete *it;
	}
}

void CFXPassRecord::apply(CDriverD3D &drv)
{
	for(std::vector<CStateRecord *>::iterator it = States.begin(); it != States.end(); ++it)
	{
		(*it)->apply(drv);
	}
}

const uint NL_D3D_NUM_RENDER_FOR_FX_CACHING = 4;

//===================================================================================
void CFXCache::setConstants(CShaderDrvInfosD3D *si)
{
	nlassert(si);
	nlassert(si->Effect);
	for(uint k = 0; k < CFXInputParams::MaxNumParams; ++k)
	{
		if (Params.Textures[k].Set) si->Effect->SetTexture(si->TextureHandle[k], Params.Textures[k].Value);
		if (Params.Vectors[k].Set) si->Effect->SetFloatArray(si->FactorHandle[k], (CONST FLOAT *) &(Params.Vectors[k].Value), 4);
		if (Params.Colors[k].Set) si->Effect->SetInt(si->ColorHandle[k], Params.Colors[k].Value);
		if (Params.Floats[k].Set) si->Effect->SetFloat(si->ScalarFloatHandle[k], Params.Floats[k].Value);
	}
}

void CFXCache::begin(CShaderDrvInfosD3D *si, CDriverD3D *driver)
{
	nlassert(driver);
	// amortize cost of caching for animated material -> ensure that the parameters don't change for
	// a few number of display before doing caching
	if (Params.Touched)
	{
		Steadyness = 0;
		Passes.clear();
		NumPasses = 0;
		Params.Touched = false;
		return;
	}
	if (!Params.Touched)
	{
		++ Steadyness;
	}
	if (Steadyness < NL_D3D_NUM_RENDER_FOR_FX_CACHING)
	{
		NumPasses = 0;
		Passes.clear();
		return;
	}
	if (Passes.empty()) // must record shader ?
	{
		Passes.clear();
		UINT numPasses;
		CFXPassRecorder pr;
		pr.Driver = driver;
		si->Effect->SetStateManager(&pr);
		// Set constants
		setConstants(si);
		//
		HRESULT r = si->Effect->Begin(&numPasses, D3DXFX_DONOTSAVESTATE|D3DXFX_DONOTSAVESHADERSTATE);
		nlassert(r == D3D_OK);
		Passes.resize(numPasses);
		for(uint k = 0; k < numPasses; ++k)
		{
			pr.Target = &Passes[k];
#if (DIRECT3D_VERSION >= 0x0900) && (D3D_SDK_VERSION >= 32)
			si->Effect->BeginPass(k);
			si->Effect->EndPass();
#else
			si->Effect->Pass(k);
#endif
		}
		r = si->Effect->End();
		nlassert(r == D3D_OK);
		NumPasses = numPasses;
		si->Effect->SetStateManager(driver);
	}
}

void CFXCache::applyPass(class CDriverD3D &drv, CShaderDrvInfosD3D *si, uint passIndex)
{
	if (Passes.empty() && NumPasses == 0)
	{
		// the shader has not been cached yet (maybe animated)
		// so uses the standard path
		UINT numPasses;
		setConstants(si);
		HRESULT r = si->Effect->Begin(&numPasses, D3DXFX_DONOTSAVESTATE|D3DXFX_DONOTSAVESHADERSTATE);
		nlassert(r == D3D_OK);
		NumPasses = numPasses;
	}
	nlassert(passIndex < NumPasses);
	if (Passes.empty())
	{
#if (DIRECT3D_VERSION >= 0x0900) && (D3D_SDK_VERSION >= 32)
		HRESULT r = si->Effect->BeginPass(passIndex);
		si->Effect->EndPass ();
#else
		HRESULT r = si->Effect->Pass(passIndex);
#endif
		nlassert(r == D3D_OK);
	}
	else
	{
		Passes[passIndex].apply(drv);
	}
}

void CFXCache::end(CShaderDrvInfosD3D *si)
{
	if (Passes.empty())
	{
		HRESULT r = si->Effect->End();
		nlassert(r == D3D_OK);
	}
}


void CFXCache::reset()
{
	Params.reset();
	Passes.clear();
	Steadyness = 0;
}



} // NL3D
