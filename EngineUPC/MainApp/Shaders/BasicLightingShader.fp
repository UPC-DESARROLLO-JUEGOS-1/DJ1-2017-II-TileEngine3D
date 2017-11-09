#version 150

in vec3 fragmentVertex;
in vec3 fragmentNormal;
in vec4 fragmentColor;

out vec4 finalColor;

uniform mat4 model;
uniform vec3 cameraPosition;
uniform float materialShininess;
uniform vec3 materialSpecularColor;

// ambient
uniform float ambientCoefficient;

uniform struct Light {
   vec3 position;
   vec3 color;
   float intensity;
   float attenuation;
   
} light0, light1;

vec4 ComputeLight(in vec3 surfacePos, in vec3 surfaceToCamera, vec4 ambient, in Light light) {
	vec4 lightResultColor;
 
	vec3 normal = normalize(fragmentNormal);
	vec3 lightColor = light.color * light.intensity;

	// Light starts
	vec3 surfaceToLight = normalize(light.position - surfacePos);
	
    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * ambient.rgb * lightColor;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), 
			materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * lightColor;
    
    //attenuation
    float distanceToLight = length(light.position - surfacePos);
    float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

    //linear color (color before gamma correction)
    vec3 linearColor = attenuation * (diffuse + specular);
    
    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    lightResultColor = vec4(pow(linearColor, gamma), ambient.a);
 
    return(lightResultColor);
}

void main() {		
    vec3 surfacePos = vec3(model * vec4(fragmentVertex, 1));
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);
	vec4 surfaceColor = (fragmentColor * ambientCoefficient);  // * texture(materialTex, fragTexCoord);
	surfaceColor.a = fragmentColor.a;
	
	vec4 light0Result = ComputeLight(surfacePos, surfaceToCamera, surfaceColor, light0);
	vec4 light1Result = ComputeLight(surfacePos, surfaceToCamera, surfaceColor, light1);
	
	finalColor = light0Result + light1Result;
}




