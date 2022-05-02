#version 460 core

in vec3 Position;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 uCameraDir;
uniform vec3 uNegLightDir;

uniform vec3 uAmbient;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;

void main()
{
    vec3 neglightdir = normalize(uNegLightDir);

    float dotdiffuse = max(dot(-Normal, neglightdir), 0.0);

    vec3 reflected = normalize(reflect(uNegLightDir, Normal));
    float dotspecular = max(dot(uCameraDir, reflected), 0.0);
    float powspecular = pow(dotspecular, uShininess);

    FragColor = vec4(sin(uAmbient + dotdiffuse * uDiffuse + powspecular * uSpecular), 1.);
}
