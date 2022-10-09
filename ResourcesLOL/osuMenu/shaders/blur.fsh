#ifdef GL_ES
    varying lowp vec4 v_fragmentColor;
    varying mediump vec2 v_texCoord;
    precision mediump float;
#else
    varying vec4 v_fragmentColor;
    varying vec2 v_texCoord;
#endif

#define PI 3.14159265359
#define A 16.0
#define B 8.0

uniform float blurRadius;

uniform sampler2D CC_Texture0;

void main()
{
    vec4 result = texture2D(CC_Texture0, v_texCoord);
    for(float d = 0.0; d < PI * 2.0; d += PI * 2.0 / A)
    {
        for(float s = 1.0 / B; s <= 1.0; s += 1.0 / B)
        {
            result += texture2D(CC_Texture0, clamp(v_texCoord + vec2(cos(d), sin(d)) * (blurRadius / 100.0 / v_texCoord) * s, 0.0, 1.0));
        }
    }
    result /= B * A - (A - 1.0);

    gl_FragColor = result * v_fragmentColor;

    //gl_FragColor = vec4(v_texCoord, 0.0, 1.0); // uv debug
}