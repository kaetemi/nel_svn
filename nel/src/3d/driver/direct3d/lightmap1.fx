texture texture0;
texture texture1;
// Color0 is the Ambient Added to the lightmap (for Lightmap 8 bit compression)
// Other colors are the lightmap Factors for each lightmap
dword color0;
dword color1;
float4 factor0;
float4 factor1;

float4 g_black = { 0.0f, 0.0f, 0.0f, 1.0f };
float4 g_dyn_factor = { 1.0f, 1.0f, 1.0f, 1.0f };

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
		AlphaBlendEnable = false;

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
		ColorOp[1] = MODULATE;
		ColorArg1[1] = CURRENT;
		ColorArg2[1] = TEXTURE;
		AlphaOp[0] =   SELECTARG1;
		AlphaArg1[0] = TFACTOR;
		AlphaOp[1] =   SELECTARG1; // for alpha test
		AlphaArg1[1] = TEXTURE;
	}
};
