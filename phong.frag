uniform vec3 lightPos;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec4 vP; // in object space
varying vec3 vN; // in object space
//varying vec3 color; // passed from the vertex shader

void main()
{
	vec3 ambient, diffuse, specular;

	vec3 normal = normalize(vN);
	vec3 normalLight = normalize(lightPos - vP.xyz);

	vec3 eyeVec = normalize(-vP.xyz); //the camera is assumed to be (0,0,0)
	vec3 halfVec = normalize(eyeVec + normalLight);

	ambient = ka;
	diffuse = kd * max(dot(normalLight,normal), 0);
	specular = ks * pow(max(dot(halfVec,normal), 0),s);
	
	vec3 color = ambient + diffuse + specular;

	gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
