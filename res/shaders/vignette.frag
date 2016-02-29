uniform sampler2D texture;

// Window resolution
uniform vec2 resolution;

// Radius of the vignette, where 0.5 results in a circle fitting the screen
const float RADIUS = 0.75;

// Softness of the vignette, between 0.0 and 1.0
const float SOFTNESS = 0.3;

void main()
{
	
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // Apply vignette effect
    vec2 position = (gl_FragCoord.xy / resolution.xy) - vec2(0.5);

    float len = length(position);

    float vignette = smoothstep(RADIUS, RADIUS - SOFTNESS, len);

    pixel.rgb = mix(pixel.rgb, pixel.rgb * vignette, 0.7);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}