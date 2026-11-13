#version 120

uniform sampler2D sourceTexture;
uniform vec2 resolution;

const float PIXEL_SIZE = 6.0;


void main(){

    vec2 uv = gl_TexCoord[0].xy;

   vec2 grid = resolution / PIXEL_SIZE;
   vec2 blockyUV = floor(uv * grid) / grid;

    vec4 color = texture2D(sourceTexture, blockyUV);

    gl_FragColor = color;
  
}

