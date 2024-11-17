#version 330 core

in vec4 planeColor;

out vec4 FragColor;

uniform vec2 resolution;
uniform float currentTime;

const vec4 starColor = vec4(1.0,1.0,0.0,1.0);
const float starRadius = 0.003;
const int starNumber = 200;
const float fallingSpeed = 0.01;

float random(vec2 n) {
    return fract(sin(dot(n, vec2(12.9898, 78.233))) );
}

float srandom(in float x) {
  return abs(fract(sin(x) * 43758.5453)) * 2. - 1.;
}

/* if x goes out of screen it wraps it and put it up again 
* put it on geogebra to understand
*/
float wrap(float x) {
	return x + 2*floor(abs(x)-floor(abs(x)/2.));
}

void main()
{
    // coordinate normalizzate del frammento
    vec2 normalizedCoords = mix(vec2(-1., -1.), vec2(1., 1.), gl_FragCoord.xy / resolution.xy);
    
    // definisce il colore di default del fragment
    vec4 outColor = planeColor;

    bool isStar = false;
    for (int i = 0; i < starNumber && !isStar; i++) {
        // generazione punto casuale di una stella
        // tutti i frammenti individuano gli stessi punti: stessi parametri passati alla funzione random 

        vec2 starPos = vec2(
            srandom(float(i)),
            wrap(srandom(float(i)-starNumber) - (currentTime)*fallingSpeed)
        );

        // distanza del frammento dalla stella
        float distanceToCenter = length(normalizedCoords - starPos);

        // se il fragment è interno alla stella allora aggiorniamo il suo colore
        if (distanceToCenter < starRadius) {
            outColor = starColor;
            isStar = true;
        }
    }

    // assegno il colore del frammento
    FragColor = outColor;
}