float4x4 wvp;

float2 moveUv;

float3x3 World;

float4 LightDiffuse;
float4 LightAmbient;
float4 LightSpecular;

float4 ModelDiffuse;
float4 ModelAmbient;
float4 ModelSpeclar;
float4 ModelEmissive;
float  ModelPowor;

texture modelTex;
sampler tex0 = sampler_state
{
    Texture = <modelTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};

texture modelTex1;
sampler tex1 = sampler_state
{
    Texture = <modelTex1>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};

texture modelTex2;
sampler tex2 = sampler_state
{
    Texture = <modelTex2>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};

struct VS_INPUT 
{
    float4 position : POSITION;
    float3 Normal   : NORMAL;
    float2 uv       : TEXCOORD0;
};

struct VS_OUTPUT 
{
    float4 position  : POSITION;
    float3 Normal    : TEXCOORD0;
    float2 uv        : TEXCOORD1;
};

VS_OUTPUT VS_OUT(VS_INPUT input)
{
    VS_OUTPUT vs_out = (VS_OUTPUT)0;

    vs_out.position  = mul(input.position, wvp);

    vs_out.Normal    = mul(input.Normal, World);
    
    vs_out.Normal    = normalize(vs_out.Normal);
    
    vs_out.uv = input.uv;
    
    return vs_out;
}


float4 PS_OUT(VS_OUTPUT input) : COLOR0
{   
    float2 uv = input.uv + moveUv;
    
    float4 Diffuse = LightDiffuse  * ModelDiffuse;
    float4 Ambient = LightAmbient  * ModelAmbient;
    float4 Speclar = LightSpecular * ModelSpeclar;    
    
    float4 a = tex2D(tex0, input.uv);
    float4 b = tex2D(tex1, input.uv);
   
    
    float4 output = a;
    
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