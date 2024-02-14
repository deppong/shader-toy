#version 330 core
out vec4 color;
in vec4 gl_FragCoord;

uniform vec2  iResolution;
uniform float iTime;

void main(){
  vec2 uv = gl_FragCoord.xy / iResolution;

  vec3 col = 0.5 + cos(iTime + uv.xyx+vec3(0, 2, 4));

  color = vec4(col, 1.0);
}
