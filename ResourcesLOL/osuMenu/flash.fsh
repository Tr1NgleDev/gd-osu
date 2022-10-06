#ifdef GL_ES
    varying lowp vec4 v_fragmentColor;
    varying mediump vec2 v_texCoord;
    precision mediump float;
#else
    varying vec4 v_fragmentColor;
    varying vec2 v_texCoord;
#endif

#define A 3.0

uniform float leftValue;
uniform float rightValue;

uniform sampler2D CC_Texture0;

void main()
{
    float leftGradient = v_texCoord.x - (1.0 - (1.0 / A));
    float rightGradient = (1.0 - v_texCoord.x) - (1.0 - (1.0 / A));

    if(leftGradient < 0.0)
        leftGradient = 0.0;
    if(leftGradient > 1.0)
        leftGradient = 1.0;

    if(rightGradient < 0.0)
        rightGradient = 0.0;
    if(rightGradient > 1.0)
        rightGradient = 1.0;

    gl_FragColor = (leftGradient * leftValue * A + rightGradient * rightValue * A);

    //gl_FragColor = vec4(v_texCoord, 0.0, 1.0); // uv debug
}