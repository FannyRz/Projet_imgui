#version 330 core

// Entrees du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet
in vec4 vColor;

// Light position dans l'espace View
uniform vec3 uLightPos_vs = vec3(0, 50.0, 0);

// Sorties du shader
out vec4 fFragColor;

void main() {
    // Direction de la lumière (vers le fragment)
    vec3 lightDir = normalize(uLightPos_vs - vPosition_vs);

    // Normale normalisée
    vec3 N = normalize(vNormal_vs);

    // Calcul de la lumière diffuse (Lambert)
    float diff = max(dot(N, lightDir), 0.0);

    // Couleur finale
    vec3 finalColor = diff * vec3(vColor); // applique l'intensité lumineuse

    fFragColor = vec4(finalColor, vColor.a);
}