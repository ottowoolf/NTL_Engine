#version 120

uniform sampler2D sourceTexture;
uniform vec2 texelSize;

void main(){
    const float weight[5] = float[5](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = texture2D(sourceTexture, uv) * weight[0];

    for(int i = 1; i < 5; i++)
    {
        vec2 offset = texelSize * float(i);
        color += texture2D(sourceTexture, uv + offset) * weight[i];
        color += texture2D(sourceTexture, uv - offset) * weight[i];
    }
    gl_FragColor = color;
}