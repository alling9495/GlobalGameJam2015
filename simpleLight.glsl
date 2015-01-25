#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
varying vec2 surfacePosition;

#define PI 3.14159265358979
#define N 30
void main( void ) {
	float size = .055;
	float dist = 1.0;
	float ang = 0.0;
	vec2 pos = vec2(1.0,0.0);
	vec3 color = vec3(50, 0,0);;
	for(int i=0; i<N; i++){
		float r = 0.3;
		ang += PI / (float(N)*0.11111111111111);
		pos = vec2(sin(ang + time)*r,cos(ang + time)*r);
		dist += size / distance(pos,surfacePosition);
		vec3 c = vec3(0.05);
		color = c*dist;
	}
	gl_FragColor = vec4(color, 1.0);
}