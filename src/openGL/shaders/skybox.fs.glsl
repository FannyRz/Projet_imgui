#version 330 core
out vec4 FragColor;  // Couleur de sortie du fragment

in vec3 texCoords;  // Coordonnées de texture provenant du vertex shader

uniform samplerCube skybox;  // Texture de la skybox

void main()
{    
    FragColor = texture(skybox, texCoords);  // Appliquer la texture à chaque fragment
}
