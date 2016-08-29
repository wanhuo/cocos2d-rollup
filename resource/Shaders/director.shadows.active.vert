attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;
varying vec4 v_texColor;
varying vec3 v_texNormal;
varying vec4 v_texPosition;

uniform mat4 cameraTransformMatrix;
uniform mat4 modelTransformMatrix;

void main(void)
{
  gl_Position = CC_MVPMatrix * a_position;

  vec3 position = vec3(modelTransformMatrix * a_position);
  vec4 transform = cameraTransformMatrix * vec4(position, 1.0);

  v_texNormal = CC_NormalMatrix * a_normal;
  v_texPosition = transform / transform.w;
  v_texCoord = a_texCoord;
  v_texColor = a_color;
}
