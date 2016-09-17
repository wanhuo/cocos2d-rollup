varying vec3 v_texNormal;
varying vec2 v_texCoord;
varying vec4 v_texColor;

/**
 *
 *
 *
 */
void main(void)
{
  
float d = distance(vec2(0.5, 0.5), v_texCoord);

gl_FragColor = v_texColor * texture2D(CC_Texture0, v_texCoord) * (d > 0.36 ? 0.0 : 1.0);
}

