#include "mini_rt.h"

static t_colour colour_multiply(t_colour c1, t_colour c2);
static t_colour colour_scalar_multiply(t_colour c, double scalar);

static t_ray	get_light_ray(t_light light, t_vector hit_point)
{
	t_ray	light_ray;

	light_ray.origin = hit_point;
	light_ray.direction = vec_subtract(light.cords, hit_point);
	light_ray.direction = normalize_vector(light_ray.direction);
	light_ray.hit_point = light.cords;
	// if (hit_point.y > light.cords.y)
	// 	light_ray.direction.y *= -1;
	return (light_ray);
}


static bool	light_hit(t_ray ray, t_object *objects)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
	while (temp != NULL)
	{
		distance = hit_object(temp, &ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
			old_hit = distance;
		temp = temp->next;
	}
	if (old_hit == 0)
		return (true);
	return (false);
}

void	lighting2(t_scene *scene, t_ray *ray)
{
	t_colour	amb;
	t_colour	diffuse;
	t_vector	light_dir;
	double		dot;

	t_colour	specular;
	double		shiny;

	t_ray	light_ray = get_light_ray(scene->light, ray->hit_point);

	shiny = 25;
	amb = get_ambient_light( ray->ray_colour, scene->amb_light);

	// hits object
	if (ray->distance >= 0)
	{
		light_dir = normalize_vector(vec_subtract(scene->light.cords, ray->hit_point));
		dot = dot_product(ray->surface_norm, light_dir);
		if (dot > 0 && light_hit(light_ray, scene->objects))
		{
			diffuse = colour_multiply(scene->light.colour, ray->ray_colour);
			diffuse = colour_scalar_multiply(diffuse, dot * scene->light.light_ratio);
			diffuse.r = (diffuse.r / 255.0) * (scene->light.light_ratio) * 255;
			diffuse.g = (diffuse.g / 255.0) * (scene->light.light_ratio) * 255;
			diffuse.b = (diffuse.b / 255.0) * (scene->light.light_ratio) * 255;

			// Calculate reflection vector
			t_vector reflection = vec_subtract(vec_scalar_multiply(ray->surface_norm, 2 * dot), light_dir);
			// Calculate view direction (from hit point to camera)
			t_vector view_dir = normalize_vector(vec_subtract(ray->origin, ray->hit_point));
			// Calculate dot product between view direction and reflection vector
			double spec_angle = fmax(dot_product(view_dir, reflection), 0.0);
			// intensity
			double spec_intensity = pow(spec_angle, shiny);
			// Calculate specular color
			specular = colour_scalar_multiply(scene->light.colour, spec_intensity);

			// Combine everuthing for phong
			ray->ray_colour.r = clamp(amb.r + diffuse.r + specular.r, 0, 255);
			ray->ray_colour.g = clamp(amb.g + diffuse.g + specular.g, 0, 255);
			ray->ray_colour.b = clamp(amb.b + diffuse.b + specular.b, 0, 255);
			// ray->ray_colour.r = clamp(amb.r + diffuse.r, 0, 255);
			// ray->ray_colour.g = clamp(amb.g + diffuse.g, 0, 255);
			// ray->ray_colour.b = clamp(amb.b + diffuse.b, 0, 255);
		}
		else
			ray->ray_colour = (t_colour){0, 0, 0};
	}
	else
	{
		// TODO: Add sky background colour??
		ray->ray_colour = get_ambient_light((t_colour){255, 255, 255}, scene->amb_light);
		// ray->ray_colour = colour_scalar_multiply(ray->ray_colour, 255);
	}
}

static t_colour colour_multiply(t_colour c1, t_colour c2)
{
	t_colour result;

	result.r = (c1.r / 255.0 * c2.r / 255.0) * 255;
	result.g = (c1.g / 255.0 * c2.g / 255.0) * 255;
	result.b = (c1.b / 255.0 * c2.b / 255.0) * 255;
	return (result);
}

static t_colour colour_scalar_multiply(t_colour c, double scalar)
{
	t_colour	result;

	result.r = c.r * scalar;
	result.g = c.g * scalar;
	result.b = c.b * scalar;
	return (result);
}


double	clamp(double value, double min, double max)
{
	return fmin(fmax(value, min), max);
}
