uniform vec3 u_DirLightSourceColor[1];
uniform vec3 u_DirLightSourceDirection[1];

uniform vec3 u_AmbientLightSourceColor;
uniform vec4 u_color;

uniform float u_element;

uniform sampler2D transformTexture;

varying vec3 v_texNormal;
varying vec2 v_texCoord;
varying vec4 v_texPosition;
varying vec2 TextureCoordOut;

vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation)
{
  float diffuse = max(dot(normalVector, lightDirection), 0.0);
  vec3 diffuseColor = lightColor  * diffuse * attenuation;

  return diffuseColor;
}

void main(void)
{
  vec3 normal  = normalize(v_texNormal);
  vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);

  vec3 lightDirection = normalize(u_DirLightSourceDirection[0] * 2.0);
  combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[0], 1.0);

  float x = v_texPosition.x;
  float y = v_texPosition.y;
  float z = v_texPosition.z;

  float f = 1.0;
  float b = 0.003;

  if(texture2D(transformTexture, vec2(x, y)).z < z - b) {
    f = 0.9;
  }

  gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color* vec4(f, f, f, 1.0);

  if(u_element > 0.0) {
    if(combinedColor.r > 0.75) {
      gl_FragColor *= vec4(u_element, u_element, u_element, 1.0);
    }
  }
}
