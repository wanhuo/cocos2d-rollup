varying vec3 v_texNormal;
varying vec2 v_texCoord;
varying vec4 v_texColor;

uniform float common;

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

  if(common > 0.0) {
    vec3 direction = vec3(0.0, -1.0, 1.0);
    vec4 color = vec4(0.5, 0.5, 0.5, 1.0);

    color.xyz += max(
      dot(
        normalize(v_texNormal),
        -normalize(
          direction * 2.0
        )
      ),
      0.0
    );

    /**
     *
     *
     *
     */
    if(color.r > 0.75) {
      gl_FragColor *= vec4(common, common, common, 1.0);
    }
  }
}
