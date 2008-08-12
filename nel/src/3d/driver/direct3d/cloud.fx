texture texture0;
texture texture1;
float4 factor0;

pixelshader two_stages_ps = asm
{
	ps_1_1;
	tex t0;
	tex t1;
	lrp r0.w, v0, t0, t1;
	mov r0.xyz, c0;
	+mul r0.w, c0, r0;
};

technique two_stages_2
{
	pass p0
	{
		Texture[0] = <texture0>;
		Texture[1] = <texture1>;
		PixelShaderConstant[0] = <factor0>;
		PixelShader = (two_stages_ps);
	}
};
