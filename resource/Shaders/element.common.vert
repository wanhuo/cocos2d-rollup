attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying vec3 v_texNormal;
varying vec2 v_texCoord;
varying vec4 v_texColor;

uniform vec4 u_color;

void main(void)
{
  v_texNormal = CC_NormalMatrix * a_normal;
  v_texCoord = a_texCoord;
  v_texColor = u_color;

  gl_Position = CC_MVPMatrix * a_position;
}
