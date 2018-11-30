#version 330 core

in vec2 UV;
in vec3 origin;
in vec3 fragPos;
out vec4 color;
   
struct mat
{
	float ambient;
	float diffuse;
	float specular;
	float specular_exp;
};

uniform sampler2D image;

uniform vec3 light_pos;
uniform vec3 camera_pos;
uniform mat  material;

void main() {

	vec3 normal = normalize(fragPos - origin);
	vec3 lightDir = normalize(light_pos - fragPos);
	vec3 viewDir = normalize(camera_pos - fragPos);
	vec3 h = normalize(lightDir - viewDir);


	float lighting = material.ambient +
					 max(0, material.diffuse * dot(lightDir, normal)) +
					 material.specular * pow(max(0, dot(h, normal)), material.specular_exp);

	color = min(lighting, 1.0) * texture( image, UV );
}