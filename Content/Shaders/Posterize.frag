#version 120

uniform sampler2D sourceTexture;


const float LEVELS = 4.0; // Number of posterization levels

void main(){

    vec2 uv = gl_TexCoord[0].xy;

   vec4 baseColor = texture2D(sourceTexture, uv);

   float luminance = dot(baseColor.rgb, vec3(0.299, 0.587, 0.114)); // Calculate luminance
   float posterizedLuminance = floor(luminance * LEVELS) / LEVELS; // Posterize luminance

   gl_FragColor = vec4(vec3(posterizedLuminance), baseColor.a); // Set the final color with posterized luminance
  
}

