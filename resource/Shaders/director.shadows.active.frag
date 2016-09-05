varying vec3 v_texNormal;
varying vec2 v_texCoord;
varying vec4 v_texColor;
varying vec4 v_texPosition;

uniform vec3 u_DirLightSourceColor[1];
uniform vec3 u_DirLightSourceDirection[1];

uniform vec3 u_AmbientLightSourceColor;

uniform float common;
uniform sampler2D transformTexture;

/**
 *
 *
 *
 */
void main(void)
{
  vec2 position = vec2(v_texCoord.x, 1.0 - v_texCoord.y);

  /**
   *
   *
   *
   */
  gl_FragColor = texture2D(CC_Texture0, position) * v_texColor;

  vec3 direction = u_DirLightSourceDirection[0];
  vec3 color = u_DirLightSourceColor[0];

  vec3 index = max(
    dot(
      normalize(v_texNormal),
      -normalize(direction * 2.0)
    ),
    0.0
  ) * color + u_AmbientLightSourceColor;

  /**
   *
   *
   *
   */
  if(index.r > 0.75) {
    float x = v_texPosition.x;
    float y = v_texPosition.y;
    float z = v_texPosition.z;

    float b = 0.0025;
    float shadow = 1.0;

    if(texture2D(transformTexture, vec2(x, y)).z < z - b) {
      shadow = 0.9;
    }

    if(shadow < 1.0) gl_FragColor *= vec4(shadow, shadow, shadow, 1.0);
    if(common > 1.0) gl_FragColor *= vec4(common, common, common, 1.0);
  }
}
