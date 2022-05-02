#version 460 core

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;

out vec4 FragColor;

uniform sampler2D uTexture;

uniform vec3 uAmbient;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;

#define NLIGHTS 3
uniform vec3 uLightDirs[NLIGHTS];
uniform vec3 uLightColors[NLIGHTS];

uniform vec3 uCameraDir;

void main()
{
    vec3 lighting = vec3(0.);

    for (int i = 0; i < NLIGHTS; i++)
    {
        vec3 neglightdir = -normalize(uLightDirs[i]);

        float dotdiffuse = max(dot(Normal, neglightdir), 0.0);

        vec3 reflected = normalize(reflect(neglightdir, Normal));
        float dotspecular = max(dot(uCameraDir, reflected), 0.0);
        float powspecular = pow(dotspecular, uShininess);

        lighting += (uAmbient + dotdiffuse * uDiffuse + powspecular * uSpecular) * uLightColors[i];
    }

    FragColor = texture(uTexture, Texcoord) * vec4(lighting, 1.);
}
