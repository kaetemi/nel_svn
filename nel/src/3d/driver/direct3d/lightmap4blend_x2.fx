texture texture0;
texture texture1;
texture texture2;
texture texture3;
texture texture4;
// Color0 is the Ambient Added to the lightmap (for Lightmap 8 bit compression)
// Other colors are the lightmap Factors for each lightmap
dword color0;
dword color1;
dword color2;
dword color3;
dword color4;
float4 factor0;
float4 factor1;
float4 factor2;
float4 factor3;
float4 factor4;

float4 g_black = { 0.0f, 0.0f, 0.0f, 1.0f };
// modulate the dyn light by 0.5, because of MODULATE2X
float4 g_dyn_factor = { 0.5f, 0.5f, 0.5f, 1.0f };


// **** 5 stages technique
pixelshader five_stages_ps = asm
{
	ps_1_4;
	texld r0, t0;
	texld r1, t1;
	texld r2, t2;
	texld r3, t3;
	texld r4, t4;
	// multiply lightmap with factor, and add with LMCAmbient+DynamicLight term
	mad r1.xyz, c1, r1, v0;
	mad r1.xyz, c2, r2, r1;
	mad r1.xyz, c3, r3, r1;
	mad r1.xyz, c4, r4, r1;
	mul_x2 r0.xyz, r1, r0;	
};

technique five_stages_5
{
	pass p0
	{
		TexCoordIndex[2] = 1;
		TexCoordIndex[3] = 1;
		TexCoordIndex[4] = 1;

		// Use Emissive For LMCAmbient, and diffuse for per vertex dynamic lighting
		Lighting = true;
		MaterialEmissive= <factor0>;
		MaterialAmbient= <g_black>;
		MaterialDiffuse= <g_dyn_factor>;
		MaterialSpecular= <g_black>;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;

		Texture[0] = <texture0>;
		Texture[1] = <texture1>;
		Texture[2] = <texture2>;
		Texture[3] = <texture3>;
		Texture[4] = <texture4>;
		PixelShaderConstant[1] = <factor1>;
		PixelShaderConstant[2] = <factor2>;
		PixelShaderConstant[3] = <factor3>;
		PixelShaderConstant[4] = <factor4>;
		PixelShader = (five_stages_ps);
	}
}

// **** 4 stages technique
pixelshader four_stages_ps = asm
{
	ps_1_1;
	tex t0;
	tex t1;
	tex t2;
	tex t3;
	// multiply lightmap with factor, and add with LMCAmbient+DynamicLight term
	mad r0.xyz, c1, t1, v0;
	mad r0.xyz, c2, t2, r0;
	mad r0.xyz, c3, t3, r0;
	mul_x2 r0.xyz, r0, t0;
	+mov r0.w, t0;
};

technique four_stages_4
{
	pass p0
	{
		TexCoordIndex[2] = 1;
		TexCoordIndex[3] = 1;

		// Use Emissive For LMCAmbient, and diffuse for per vertex dynamic lighting
		Lighting = true;
		MaterialEmissive= <factor0>;
		MaterialAmbient= <g_black>;
		MaterialDiffuse= <g_dyn_factor>;
		MaterialSpecular= <g_black>;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;

		Texture[0] = <texture0>;
		Texture[1] = <texture1>;
		Texture[2] = <texture2>;
		Texture[3] = <texture3>;
		PixelShaderConstant[1] = <factor1>;
		PixelShaderConstant[2] = <factor2>;
		PixelShaderConstant[3] = <factor3>;
		PixelShader = (four_stages_ps);
	}
	pass p1
	{
		FogColor = 0x00000000; // don't accumulate fog several times
		Lighting = false;
		DestBlend = one;

		// the DiffuseTexture texture 0 is in last stage
		TexCoordIndex[0] = 1;
		TexCoordIndex[1] = 0;
		Texture[0] = <texture4>;
		Texture[1] = <texture0>;
		TextureFactor = <color4>;
		ColorOp[0] = MODULATE;
		ColorArg1[0] = TFACTOR;
		ColorArg2[0] = TEXTURE;
		ColorOp[1] = MODULATE2X;
		ColorArg1[1] = CURRENT;
		ColorArg2[1] = TEXTURE;
		ColorOp[2] = DISABLE;
		ColorOp[3] = DISABLE;
		// Alpha stage 0 unused
		AlphaOp[0] = SELECTARG1;
		AlphaArg1[0] = TFACTOR;
		AlphaOp[1] = SELECTARG1;
		AlphaArg1[1] = TEXTURE;
		AlphaOp[2] = DISABLE;
		AlphaOp[3] = DISABLE;
		PixelShader = NULL;
	}
}

// **** 3 stages technique
pixelshader three_stages_0_ps = asm
{
	ps_1_1;
	tex t0;
	tex t1;
	tex t2;
	// multiply lightmap with factor, and add with LMCAmbient+DynamicLight term
	mad r0.xyz, c1, t1, v0;
	mad r0.xyz, c2, t2, r0;
	mul_x2 r0.xyz, r0, t0;
	+mov r0.w, t0;
};

technique three_stages_3
{
	// 2 pass with the same pixel shader
	pass p0
	{
		TexCoordIndex[2] = 1;

		// Use Emissive For LMCAmbient, and diffuse for per vertex dynamic lighting
		Lighting = true;
		MaterialEmissive= <factor0>;
		MaterialAmbient= <g_black>;
		MaterialDiffuse= <g_dyn_factor>;
		MaterialSpecular= <g_black>;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;

		Texture[0] = <texture0>;
		Texture[1] = <texture1>;
		Texture[2] = <texture2>;
		PixelShaderConstant[1] = <factor1>;
		PixelShaderConstant[2] = <factor2>;
		PixelShader = (three_stages_0_ps);
	}
	pass p1
	{
		FogColor = 0x00000000; // don't accumulate fog several times
		// second pass: shut down all lighting (lmc ambient term and dynamic lighting already added in first pass)
		MaterialEmissive= <g_black>;
		MaterialDiffuse= <g_black>;

		DestBlend = one;
		Texture[1] = <texture3>;
		Texture[2] = <texture4>;
		PixelShaderConstant[1] = <factor3>;
		PixelShaderConstant[2] = <factor4>;
	}
}

// **** 2 stages, no pixel shader technique
technique two_stages_2
{
	pass p0
	{
		// Use Emissive For LMCAmbient, and diffuse for per vertex dynamic lighting
		Lighting = true;
		MaterialEmissive= <factor0>;
		MaterialAmbient= <g_black>;
		MaterialDiffuse= <g_dyn_factor>;
		MaterialSpecular= <g_black>;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;

		// the DiffuseTexture texture 0 is in last stage
		TexCoordIndex[0] = 1;
		TexCoordIndex[1] = 0;
		Texture[0] = <texture1>;
		Texture[1] = <texture0>;
		TextureFactor = <color1>;
		ColorOp[0] = MULTIPLYADD;
		ColorArg0[0] = DIFFUSE;
		ColorArg1[0] = TFACTOR;
		ColorArg2[0] = TEXTURE;
		ColorOp[1] = MODULATE2X;
		ColorArg1[1] = CURRENT;
		ColorArg2[1] = TEXTURE;
		// Alpha stage 0 unused
		AlphaOp[0] = SELECTARG1;
		AlphaArg1[0] = TFACTOR;
		AlphaOp[1] = SELECTARG1;
		AlphaArg1[1] = TEXTURE;
	}
	pass p1
	{
		FogColor = 0x00000000; // don't accumulate fog several times
		Lighting = false;
		DestBlend = one;
		Texture[0] = <texture2>;
		TextureFactor = <color2>;
		ColorOp[0] = MODULATE;
	}
	pass p2
	{
		Texture[0] = <texture3>;
		TextureFactor = <color3>;
	}
	pass p3
	{
		Texture[0] = <texture4>;
		TextureFactor = <color4>;
	}
}


