uniform sampler2D texture;
uniform float blink_alpha;

void main()
{
    vec4 pixel = gl_Color;
	gl_FragColor = pixel;
}
