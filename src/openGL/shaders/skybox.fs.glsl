#version 330 core

in vec3 texCoords;  // Coordonnées de texture provenant du vertex shader

uniform samplerCube textureSkybox;  // Texture de la skybox

out vec4 FragColor;  // Couleur de sortie du fragment

void main()
{    
    FragColor = texture(textureSkybox, texCoords);  // Appliquer la texture à chaque fragment
}
