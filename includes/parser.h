
#ifndef PARSER_H
# define PARSER_H

# include <stdint.h>

/* -------------------------------------------------------------------------- */
/*                                   Structs                                  */
/* -------------------------------------------------------------------------- */

typedef struct s_colour
{
	int				r;
	int				g;
	int				b;
}	t_colour;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
}	t_vector;

typedef struct s_amb_light
{
	double			light_ratio;
	t_colour		colour_in_range;
}	t_amb_light;

typedef struct s_camera
{
	t_vector		cords;
	t_vector		or_vect;
	int				fov;
}	t_camera;

typedef struct s_light
{
	t_vector		cords;
	double			light_ratio;
	t_colour		colour;
}	t_light;

typedef struct s_sphere
{
	t_vector		cords;
	double			diameter;
	t_colour		colour;
}	t_sphere;

typedef struct s_plane
{
	t_vector		cords;
	t_vector		threed_vec;
	t_colour		colour;
}	t_plane;

typedef struct s_cylinder
{
	t_vector		cords;
	t_vector		axis;
	double			diameter;
	double			height;
	t_colour		colour;
}	t_cylinder;

typedef struct s_object
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	struct s_object	*next;
}	t_object;

typedef struct s_scene
{
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
}	t_scene;

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

char		**split_line(char *line);
t_scene		parser(char **argv);
void		parser_exit(int error_code, void **free_me);
void		free_2d_array(char **tokens);
bool		atof_check(char *str);
bool		is_valid_numbers(char **tokens);
bool		legal_colour(t_colour colour);
void		exit_analize(t_scene *scene, char **tokens, int fd, t_object *object);
void		init_amb(t_scene *scene, char **tokens, int fd);
void		init_cam(t_scene *scene, char **tokens, int fd);
void		init_light(t_scene *scene, char **tokens, int fd);
bool		legal_vector(t_vector vector, double min, double max);
void		init_plane(t_scene *scene, char **tokens, int fd);
void		init_cylinder(t_scene *scene, char **tokens, int fd);
void		init_sphere(t_scene *scene, char **tokens, int fd);
void		assign_vector(t_vector *vector, char **tokens, int start_index);
void		assign_colour(t_colour *colour, char **tokens, int start_index);


#endif /*PARSER_H*/