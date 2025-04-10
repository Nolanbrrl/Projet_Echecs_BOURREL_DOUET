#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

// Première source de lumière (fixe)
uniform vec3 lightPos1;
uniform vec3 lightColor1;

// Deuxième source de lumière (mobile)
uniform vec3 lightPos2;
uniform vec3 lightColor2;

uniform vec3 viewPos;
//
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Ns;
uniform float ambientFactor;

uniform bool useTexture;
uniform sampler2D map_Kd;

// Fonction pour calculer l'effet d'une source lumineuse
vec3 calculateLight(vec3 lightPos, vec3 lightColor, vec3 diffuseColor, vec3 normal, float ambientStrength) {
    // Ambient
    vec3 ambient = Ka * (lightColor * ambientStrength);
    
    // Diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor * lightColor;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), Ns);
    vec3 specular = spec * Ks * lightColor;
    
    return ambient + diffuse + specular;
}

void main() {
    vec3 diffuseColor = useTexture ? texture(map_Kd, TexCoords).rgb : Kd;
    vec3 N = normalize(Normal);
    
    // Calculer l'éclairage des deux sources
    vec3 result1 = calculateLight(lightPos1, lightColor1, diffuseColor, N, ambientFactor);
    vec3 result2 = calculateLight(lightPos2, lightColor2, diffuseColor, N, ambientFactor * 0.5); // Lumière secondaire moins intense
    
    vec3 result = result1 + result2;
    
    result = min(result, vec3(1.0));
    
    FragColor = vec4(result, 1.0);
}