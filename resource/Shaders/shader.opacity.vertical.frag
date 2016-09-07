varying vec2 v_texCoord;

/**
 *
 *
 *
 */
void main()
{
   float a;
   if(v_texCoord.y < 0.2) {
a =v_texCoord.y*(1.0 / 0.2);
   } else if(v_texCoord.y > 0.9) {
a = 1.0 - (v_texCoord.y-0.9)*20.0;
   }
   else {
a= 1.0;
   }

  gl_FragColor = texture2D(CC_Texture0, v_texCoord) * vec4(a,a,a,a);
}
