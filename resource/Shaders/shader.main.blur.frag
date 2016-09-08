varying float v_Index;

varying vec2 position;
varying vec2 coordinates[5];

/**
 *
 *
 *
 */
void main()
{
  if(v_Index > 0.0)
  {
    gl_FragColor = vec4(0.0);

    gl_FragColor += texture2D(CC_Texture0, coordinates[0]) * 0.204164;
    gl_FragColor += texture2D(CC_Texture0, coordinates[1]) * 0.304005;
    gl_FragColor += texture2D(CC_Texture0, coordinates[2]) * 0.304005;
    gl_FragColor += texture2D(CC_Texture0, coordinates[3]) * 0.093913;
    gl_FragColor += texture2D(CC_Texture0, coordinates[4]) * 0.093913;
  }
  else
  {
    gl_FragColor = texture2D(CC_Texture0, position);
  }
}
