precision mediump float;
attribute vec3 aVertex;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aVertex, 1.0);
    vTexCoord = aTexCoord;
}
