#version 120

uniform sampler2D sourceTexture;
uniform float progress; // Drives the radius (0.0 to 1.0)
uniform vec2 hitCenter; // The UV coordinate of the collision
uniform vec4 hitColor; // Color of the ripple effect

const float MAX_RADIUS = 0.1;
const float THICKNESS = 0.02;
const float FORCE  = 0.03;

void main(){

    vec2 uv = gl_TexCoord[0].xy;

    float dist = distance(uv, hitCenter);

    float currentRadius = MAX_RADIUS * progress;
    float diff = abs(dist - currentRadius);
    float mask = 1 - smoothstep(0.0, THICKNESS, diff);

    mask *= smoothstep(0.0, 1.0, 1.0 - progress); // Fade out as progress approaches 1.0

    vec2 direction = normalize(uv - hitCenter);
    vec2 distortedUV = uv - (direction * FORCE * mask);

    vec4 baseColor = texture2D(sourceTexture, distortedUV);
   

    gl_FragColor = baseColor + (hitColor * mask);
  
}

