#version 120

uniform sampler2D sourceTexture;
uniform float time;

const float THICKNESS = 0.05;
const float FORCE  = 0.03;

void main(){

    vec2 uv = gl_TexCoord[0].xy;

    vec2 center = vec2(0.5, 0.5);
    float dist = distance(uv, center);

    float currentRadius = mod(time, 1.5);

    float diff = abs(dist - currentRadius);

    float mask = 1 - smoothstep(0.0, THICKNESS, diff);

    vec2 direction = normalize(uv - center);
    vec2 distortedUV = uv - (direction * FORCE * mask);

    vec4 color = texture2D(sourceTexture, distortedUV);
   

    gl_FragColor = color;
  
}

