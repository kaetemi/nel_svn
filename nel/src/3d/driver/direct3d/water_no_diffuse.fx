texture texture0; // bumpmap0
texture texture1; // bumpmap1
texture texture2; // envmap

float4 factor0; // bumpmap0 scale
float4 factor1; // bumpmap1 scale
float  scalarFloat0; // bump scale for 1_1 version

pixelshader water_no_diffuse_2_0 = asm
{
	ps_2_0;
	dcl t0.xy;
	dcl t1.xy;
	dcl t2.xy;
	dcl_2d s0;
	dcl_2d s1;
	dcl_2d s2;	
	//read bump map 0
	texld   r0, t0, s0;
	//bias result (include scaling)
	mad    r0.xy, r0, c0.z, c0;
	add    r0.xy, r0, t1;
	//read bump map 1
	texld  r0, r0, s1;
	//bias result (include scaling)
	mad    r0.xy, r0, c1.z, c1;
	//add envmap coord
	add	   r0.xy, r0, t2;
	//read envmap
	texld  r0, r0, s2;
	mov oC0, r0;
};

technique technique_water_no_diffuse_2_0
{
	pass p0
	{		
		Texture[0] = <texture0>;
		Texture[1] = <texture1>;
		Texture[2] = <texture2>;
		PixelShaderConstant[0] = <factor0>;
		PixelShaderConstant[1] = <factor1>;
		PixelShader = (water_no_diffuse_2_0);
	}
};

pixelshader water_no_diffuse_1_4 = asm
{
	ps_1_4;
	texld   r0, t0;
	texld   r1, t1;
	texcrd  r2.xyz, t2;
	mad r2.xy, r0_bx2, c0, r2;
	mad r2.xy, r1_bx2, c1, r2;
	phase
	texld r2, r2;
	mov r0, r2;
};

technique technique_water_no_diffuse_1_4
{
	pass p0
	{
		Texture[0] = <texture0>;
		Texture[1] = <texture1>;
		Texture[2] = <texture2>;
		PixelShaderConstant[0] = <factor0>;
		PixelShaderConstant[1] = <factor1>;
		PixelShader = (water_no_diffuse_1_4);
	}
};

pixelshader water_no_diffuse_1_1 = asm
{
	// note in OpenGL on nVidia cards, it is permitted to chain 2 texbem so the effect is less nice there (no bumpmap animation)
	ps_1_1;
	tex t1;
	texbem t2, t1;
	mov r0, t2;
};

technique technique_water_no_diffuse_1_1
{
	pass p0
	{
		Texture[1] = <texture1>;
		Texture[2] = <texture2>;		
		PixelShaderConstant[0] = <factor0>;
		PixelShaderConstant[1] = <factor1>;
		PixelShader = (water_no_diffuse_1_1);
		BumpEnvMat00[2] = <scalarFloat0>;
		BumpEnvMat01[0] = 0;
		BumpEnvMat10[0] = 0;
		BumpEnvMat11[2] = <scalarFloat0>;
	}
};
