texture texture0;

float4 g_black = { 0.0f, 0.0f, 0.0f, 1.0f };
float4 g_dyn_factor = { 1.0f, 1.0f, 1.0f, 1.0f };

technique one_stage_1
{
	pass p0
	{
		// do a standard lighting with the first light
		Lighting = true;
		MaterialEmissive= <g_black>;
		MaterialAmbient= <g_black>;
		MaterialDiffuse= <g_dyn_factor>;
		MaterialSpecular= <g_black>;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;

		Texture[0] = <texture0>;
		ColorOp[0] = MODULATE;
		ColorArg1[0] = TEXTURE;
		ColorArg2[0] = DIFFUSE;
		AlphaOp[0] = SELECTARG1;
		AlphaArg1[0] = TEXTURE;
	}
};
