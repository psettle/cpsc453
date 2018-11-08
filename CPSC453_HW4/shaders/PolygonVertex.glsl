#version 330 core

layout(location = 0) in vec3 position;

out vec3 colorOut;

/**********************************************************
                       CONSTANTS
**********************************************************/

#define MAX_DISTANCE 1000000.0f

#define MAX_SPHERES		10
#define MAX_TRIANGLES	70
#define MAX_PLANES		10
#define MAX_LIGHTS		10
#define MAX_REFLECTS    10

#define SPHERE_OFFSET   0
#define TRIANGLE_OFFSET MAX_SPHERES
#define PLANE_OFFSET    TRIANGLE_OFFSET + MAX_TRIANGLES

/**********************************************************
                       TYPES
**********************************************************/
 
struct Material
{
	vec3 colour;
	float ambient;
	float diffuse;
	float specular;
	uint  specular_exp;
	float reflectivity;
};
 
struct Sphere
{
	Material material;
	vec3 	 centre;
	float    radius;
};

struct SphereIntersect
{
	uint  count;
	float t0;
	float t1;
	vec3  p0;
	vec3  p1;
};

struct Plane
{
	Material material;
	vec3	 normal;
	vec3     point;
};

struct PlaneIntersect
{
	bool  exists;
	float t;
	vec3  p;
};

struct Triangle
{
	Material material;
	vec3	 p0;
	vec3	 p1;
	vec3	 p2;
};

struct TriangleIntersect
{
	bool  exists;
	float t;
	float w;		// 1 - u - v
	float u;
	float v;
	vec3  p;
};

struct Light
{
	vec3 colour;
	vec3 position;
};

struct Intersect
{
	bool exists;
	Material material;
	vec3 p;
	vec3 n;
	float t;
	uint objectID;
};

struct Trace
{
	bool exists;
	vec3 colour;
	vec3 n;
	vec3 p;
	uint objectID;
	Material material;
};

/**********************************************************
                       UNIFORMS
**********************************************************/

/* Distance to film */
uniform float d;

uniform vec3 camera_pos = vec3(0.0f);
uniform vec3 camera_dir = vec3(0, 0, -1);
uniform vec3 camera_up  = vec3(0, 1, 0);

/* Sphere data */
uniform uint   sphere_count;
uniform Sphere spheres[MAX_SPHERES];

/* Plane data */
uniform uint   plane_count;
uniform Plane  planes[MAX_PLANES];

/* Triagle data */
uniform uint   triangle_count;
uniform Triangle  triangles[MAX_TRIANGLES];

/* Light data */
uniform uint   light_count;
uniform Light  lights[10];

/**********************************************************
                       PROTOTYPES
**********************************************************/

//calculate the intersection points of a ray with a sphere
//sphere:
//		Target sphere
//origin:
//		Origin on the ray
//direction:
//		Direction of the ray
SphereIntersect calculate_sphere_intersect(Sphere sphere, vec3 origin, vec3 direction);

PlaneIntersect calculate_plane_intersect(Plane plane, vec3 origin, vec3 direction);

TriangleIntersect calculate_triangle_intersect(Triangle triangle, vec3 origin, vec3 direction);

Intersect calculate_intersect(vec3 origin, vec3 direction, uint originID);

Trace trace_ray(vec3 origin, vec3 direction, uint originID);

/**********************************************************
                       FUNCTIONS
**********************************************************/

void main()
{
	/* Calculate ray direction vector */
	gl_Position = vec4(position, 1.0f);
	
	vec3 final_colour = vec3(1.0f);
	vec3 origin = camera_pos;
	
	vec3 centre_screen = origin + normalize(camera_dir) * d;
	
	vec3 rayDir = normalize(centre_screen + camera_up * position.y + normalize(cross(camera_dir, camera_up)) * position.x);
	
	uint objectID = uint(1000);
	float reflectivity = 1.0f;
	
	for(int i = 0; i < MAX_REFLECTS; ++i)
	{
		Trace trace = trace_ray(origin, rayDir, objectID);
	
		if(i == 0)
		{
			final_colour = trace.colour;
		}
		else
		{
			final_colour += trace.colour * reflectivity;
		}
		
		
		if(!trace.exists || trace.material.reflectivity == 0.0f)
		{
			break;
		}
		
		//reflect the ray, run again.
		rayDir = reflect(rayDir, trace.n);
		origin = trace.p;
		objectID = trace.objectID;
		reflectivity = trace.material.reflectivity;
	}
	
	colorOut = final_colour;
}

Trace trace_ray(vec3 origin, vec3 direction, uint originID)
{
	Trace ret;
	
	ret.colour = vec3(0.0f);

	Intersect rayIntersect = calculate_intersect(origin, direction, originID);
		
	if(!rayIntersect.exists)
	{
		ret.exists = false;
		ret.colour = vec3(0.0f);
		return ret;
	}
	else
	{
		ret.exists = true;
		ret.n = rayIntersect.n;
		ret.p = rayIntersect.p;
		ret.objectID = rayIntersect.objectID;
		ret.material = rayIntersect.material;
	}
	
	vec3 lightDir = normalize(lights[0].position - rayIntersect.p);
	
	float ambientFactor;
	float diffuseFactor;
	float specularFactor;
	
	Intersect shadowIntersect = calculate_intersect(rayIntersect.p, lightDir, rayIntersect.objectID);
	
	if( ( shadowIntersect.exists ) &&
		( shadowIntersect.t > 0 ) && 
		( shadowIntersect.t < length(lights[0].position - rayIntersect.p) ) &&
		( dot(rayIntersect.n, lightDir) > 0.0f ) )
	{
		//light blocked by other object
		ret.colour = rayIntersect.material.colour * rayIntersect.material.ambient;
	}
	else
	{
		//normal lighting
		ambientFactor = rayIntersect.material.ambient;
		diffuseFactor = rayIntersect.material.diffuse * max(0, dot(rayIntersect.n, lightDir));
		
		vec3 reflectedLightDir = normalize(-lightDir + 2 * dot(lightDir, rayIntersect.n) * rayIntersect.n);	
		specularFactor = rayIntersect.material.specular * pow(max(0, dot(-direction, reflectedLightDir)), rayIntersect.material.specular_exp);
			
		ret.colour = rayIntersect.material.colour * (ambientFactor + diffuseFactor) + specularFactor * vec3(1.0f);
	}
	
	return ret;
}

Intersect calculate_intersect(vec3 origin, vec3 direction, uint originID)
{
	Intersect ret;
	ret.t = MAX_DISTANCE;
	ret.objectID = uint(1000);

	for(uint i = uint(0); i < sphere_count; ++i)
	{	
		uint objectID = uint(SPHERE_OFFSET) + i;
		SphereIntersect intersect = calculate_sphere_intersect(spheres[i], origin, direction);
		
		if(intersect.count > uint(1) && ret.t > intersect.t0 && objectID != originID && intersect.t0 > 0.0f)
		{
			ret.t = intersect.t0;
			ret.p = intersect.p0;
			ret.n = normalize(intersect.p0 - spheres[i].centre);
			ret.material = spheres[i].material;
			ret.objectID = objectID;
		}
		
		if(intersect.count > uint(2) && ret.t > intersect.t1 && objectID != originID && intersect.t1 > 0.0f)
		{
			ret.t = intersect.t1;
			ret.p = intersect.p1;
			ret.n = normalize(intersect.p1 - spheres[i].centre);
			ret.material = spheres[i].material;
			ret.objectID = objectID;
		}
	}
	
	for(uint i = uint(0); i < plane_count; ++i)
	{		
		uint objectID = uint(PLANE_OFFSET) + i;
		PlaneIntersect intersect = calculate_plane_intersect(planes[i], origin, direction);

		if(intersect.exists && intersect.t > 0.0f && ret.t > intersect.t && objectID != originID)
		{
			ret.t = intersect.t;
			ret.p = intersect.p;
			ret.n = normalize(planes[i].normal);
			ret.material = planes[i].material;
			ret.objectID = objectID;
		}
	}

	for(uint i = uint(0); i < triangle_count; ++i)
	{		
		uint objectID = uint(TRIANGLE_OFFSET) + i;
		TriangleIntersect intersect = calculate_triangle_intersect(triangles[i], origin, direction);
	
		if(intersect.exists && intersect.t > 0.0f && ret.t > intersect.t && objectID != originID)
		{
			ret.t = intersect.t;
			ret.p = intersect.p;
			ret.n = normalize(cross(triangles[i].p1 - triangles[i].p0, triangles[i].p2 - triangles[i].p1));
			ret.material = triangles[i].material;
			ret.objectID = objectID;
		}
	}
	
	if(ret.t < MAX_DISTANCE)
	{
		ret.exists = true;
	}
	else
	{
		ret.exists = false;
	}
	
	return ret;
}

//calculate the intersection points of a ray with a sphere
//centre:
//		Centre of target sphere
//origin:
//		Origin on the ray
//direction:
//		Direction of the ray
//radius:
//		Radius of the sphere
SphereIntersect calculate_sphere_intersect(Sphere sphere, vec3 origin, vec3 direction)
{
	SphereIntersect ret;

	// dot(origin + t * direction - centre, origin + t * direction - centre) - R^2 == 0
	// 
	// simplify origin - centre:
	vec3 offset = origin - sphere.centre;
	// and you get:
	//
	// dot(t * direction + offset, t * direction + offset) - R^2 == 0
	//
	// distribute dot products:
	//
	// t^2 * dot(direction, direction) + 2 * t * dot(direction, offset) + dot(offset, offset) - R^2 == 0
	//
	// Quadratic equation constants:
	//
	float a, b, c;
	a = dot(direction, direction);
	b = 2.0 * dot(direction, offset);
	c = dot(offset, offset) - pow(sphere.radius,2);

	float radical = pow(b, 2) - 4 * a * c;

	if(radical < 0.0f)
	{
		ret.count = uint(0);
	}
	else if(radical == 0.0f)
	{
		ret.count = uint(1);
	}
	else
	{
		ret.count = uint(2);
	}
	
	if(ret.count > uint(0))
	{
		radical = sqrt(radical);
		ret.t0 = ( -b - radical ) / ( 2 * a );
		ret.p0 = origin + ret.t0 * direction;
	}

	if(ret.count > uint(1))
	{
		ret.t1 = ( -b + radical ) / ( 2 * a );
		ret.p1 = origin + ret.t1 * direction;
	}

	return ret;	
}

PlaneIntersect calculate_plane_intersect(Plane plane, vec3 origin, vec3 direction)
{
	PlaneIntersect ret;
	
	//dot(origin + t * direction - plane.point, plane.normal) = 0
	//dot(origin - plane.point, plane.normal) + t * dot(direction, plane.normal) = 0
	//t = -dot(origin - plane.point, plane.normal) / dot(direction, plane.normal)
	
	float divisor = dot(direction, plane.normal);
	float numerator = -1.0 * dot(origin - plane.point, plane.normal);
	
	if(divisor == 0.0f)
	{
		ret.exists = false;
		return ret;
	}
	ret.exists = true;
	
	ret.t = numerator / divisor;
	ret.p = origin + ret.t * direction;
	
	return ret;
}

TriangleIntersect calculate_triangle_intersect(Triangle triangle, vec3 origin, vec3 direction)
{
	TriangleIntersect ret;
	
	Plane plane;
	plane.normal = cross(triangle.p1 - triangle.p0, triangle.p2 - triangle.p1);
	plane.point = triangle.p1;
	
	PlaneIntersect planeIntersect = calculate_plane_intersect(plane, origin, direction);
	
	if(!planeIntersect.exists)
	{
		ret.exists = false;
		return ret;
	}
	
	//we know the ray collides with the plane the triangle is on, and the location of the intersect,
	//now we calculate w, u, v to test if the point is inside the bounds of the triangle.
	float A, A0, A1, A2;
	
	A = length(cross(triangle.p2 - triangle.p1, triangle.p1 - triangle.p0));
	A0 = length(cross(triangle.p2 - triangle.p1, triangle.p1 - planeIntersect.p));
	A1 = length(cross(triangle.p2 - planeIntersect.p, planeIntersect.p - triangle.p0));
	A2 = length(cross(planeIntersect.p - triangle.p1, triangle.p1 - triangle.p0));
	
	ret.u = A1 / A;
	ret.v = A2 / A;
	ret.w = A0 / A;
	ret.t = planeIntersect.t;
	ret.p = planeIntersect.p;
	
	/* If p is outside the triangle, at least 2 of the partial areas will sum past 1.*/
	if( ( ret.u + ret.v <= 1.0f ) &&
		( ret.v + ret.w <= 1.0f ) &&
		( ret.w + ret.u <= 1.0f ) )
	{
		ret.exists = true;
	}
	else
	{
		ret.exists = false;
	}
		
	return ret;
}




