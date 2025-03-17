#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;
layout(location = 3) in mat4 uMVPMatrix;
layout(location = 4) in mat4 uMVMatrix;
layout(location = 5) in mat4 uNormalMatrix;

out vec4 vPositionVC;
out vec4 vNormalVC;
out vec2 vTexCoords;
out vec4 gl_Position;


mat4 translate(float tx, float ty, float tz){
  mat4 M = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(tx, ty, tz, 1));
  return M;
}

mat4 scale(float sx, float sy, float sz){
  mat4 M = mat4(vec4(sx, 0, 0, 0), vec4(0, sy, 0, 0), vec4(0, 0, sz, 0), vec4(0, 0, 0, 1));
  return M;
}

mat4 rotate(float a){
  mat4 M = mat4(vec4(1, 0, 0, 0), vec4(0, cos(radians(a)), -sin(radians(a)), 0), vec4(0, sin(radians(a)), cos(radians(a)), 0), vec4(0, 0, 0, 1));
  return M;
}

void main() {
//Coordonnées homogènes de la position du vertex

 vec4 PositionCoordHomogene;
   for(int i = 0; i < 3; i++){
    if(i == 3){
        PositionCoordHomogene[i] = 1;
    }
    PositionCoordHomogene[i] = aVertexPosition[i];
   } 

//Coordonnées homogènes de la normale du vertex

 vec4 NormalCoordHomogene;
 for(int i = 0; i < 3; i++){
    if(i == 3){
        NormalCoordHomogene[i] = 0;
    }
    NormalCoordHomogene[i] = aVertexNormal[i];
   } 

//Les Model Coordinates MC sont les coordonnées en entrée soit aVertexPosition

//Calcul ViewCoordinates matrice MV * position homogene 
vec4 ViewCoordinates;
ViewCoordinates = uMVMatrix * PositionCoordHomogene;


//Calcul ClipCoordinates Matrice MVP * position homogene
vec4 ClipCoordinates;
ClipCoordinates = uMVPMatrix * PositionCoordHomogene;
gl_Position = ClipCoordinates;


};


