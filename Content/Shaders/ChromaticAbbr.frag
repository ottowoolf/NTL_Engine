#version 120

uniform sampler2D sourceTexture;
uniform float time;

const float OFFSET = 0.005;
const float MAX_OFFSET = 0.015;



void main(){

    float isGlitching = step(2.85, mod(time, 3.0));

    float Jitter = sin(time * 60.0);
    float dynamicOffset = MAX_OFFSET * isGlitching * Jitter;

    vec2 uv = gl_TexCoord[0].xy;

   vec4 color = texture2D(sourceTexture, uv);

   color.r = texture2D(sourceTexture, uv + vec2(dynamicOffset, 0.0)).r;
   color.b = texture2D(sourceTexture, uv - vec2(dynamicOffset, 0.0)).b;

    gl_FragColor = color;
  
}

