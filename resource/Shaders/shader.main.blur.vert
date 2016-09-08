attribute vec4 a_position;
attribute vec2 a_texCoord;

varying float v_Index;

varying vec2 position;
varying vec2 coordinates[5];

uniform float index;

/**
 *
 *
 *
 */
void main()
{
  gl_Position = CC_MVPMatrix * a_position;

  v_Index = index;
  position = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
  
  if(index > 0.0)
  {
    coordinates[0] = position.xy;
    coordinates[1] = position.xy + vec2(index) * 1.407333;
    coordinates[2] = position.xy - vec2(index) * 1.407333;
    coordinates[3] = position.xy + vec2(index) * 3.294215;
    coordinates[4] = position.xy - vec2(index) * 3.294215;
  }
}
