/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * require_extensions: GL_ARB_arrays_of_arrays
 * [end config]
 */
#version 120
#extension GL_ARB_arrays_of_arrays: enable

struct S {
  vec4 [2] x[2];
};

uniform S s;

void main()
{
  gl_FragData[0] = s.x[0][1];
}
