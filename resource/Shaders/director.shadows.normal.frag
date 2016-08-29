void main()
{
  float r = gl_FragCoord.z;

  gl_FragColor = vec4(r, r, r, 1.0);
}
