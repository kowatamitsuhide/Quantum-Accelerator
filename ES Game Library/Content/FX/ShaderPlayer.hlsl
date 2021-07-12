float4x4 wvp;

texture modelTex1;

int alpha   = 1;
int r_color = 0;

sampler tex1 = sampler_state
{
    Texture = <modelTex1>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};

struct VS_INPUT 
{
    float4 position : POSITION;
    float2 uv       : TEXCOORD0;
};

struct VS_OUTPUT 
{
    float4 position  : POSITION;
    float2 uv        : TEXCOORD1;
};

VS_OUTPUT VS_OUT(VS_INPUT input)
{
    VS_OUTPUT vs_out = (VS_OUTPUT)0;

    vs_out.position  = mul(input.position, wvp);
    
    vs_out.uv = input.uv;
    
    return vs_out;
}


float4 PS_OUT(VS_OUTPUT input) : COLOR0
{  
    
    float4 tex_1 = tex2D(tex1, input.uv);
    
    tex_1.a = alpha;
    tex_1.r = r_color;
    
    float4 output = tex_1;
    
    return output;
}

technique Sobel
{
    pass pass0
    {
        VertexShader = compile vs_3_0 VS_OUT();
        PixelShader  = compile ps_3_0 PS_OUT();
    }
}