attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec3 a_color;
attribute vec2 a_texCoord;

varying vec3 v_texNormal;
varying vec2 v_texCoord;
varying vec4 v_texColor;
varying vec4 v_texPosition;

uniform vec4 u_color;

uniform mat4 cameraTransformMatrix;
uniform mat4 modelTransformMatrix;

void main(void)
{
  vec3 position = vec3(modelTransformMatrix * a_position);
  vec4 transform = cameraTransformMatrix * vec4(position, 1.0);

  v_texNormal = CC_NormalMatrix * a_normal;
  v_texCoord = a_texCoord;
  v_texColor = u_color;
  v_texPosition = transform / transform.w;

  gl_Position = CC_MVPMatrix * a_position;
}
