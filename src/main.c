#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	// mlx_t		*mlx;
	// mlx_image_t	*img;
	// int			progress;
	t_scene		scene;

	scene = (t_scene){};
	scene = parser(argc, argv);
	
	t_print_scene(scene);
	free_objects(scene.objects);
	// mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	// if (mlx == NULL)
	// 	return (1);
	// mlx_key_hook(mlx, (void *)escape, NULL);
	// img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(mlx, img, 0, 0);
	// int	y = 0;
	// while (y < HEIGHT)
	// {
	// 	int	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		uint8_t	r = 255 * ((double)x / (WIDTH - 1));
	// 		uint8_t	g = 255 * ((double)y / (HEIGHT - 1));
	// 		uint8_t	b = 150;
	// 		uint32_t	color = ((r << 24) | (g << 16) | (b << 8) | 0xFF);
	// 		mlx_put_pixel(img, x, y, color);
	// 		x++;
	// 	}
	// 	progress = (100 * y) / HEIGHT;
	// 	display_render_progress(progress);
	// 	y++;
	// }
	// progress = (100 * y) / HEIGHT;
	// display_render_progress(progress);
	// mlx_loop(mlx);
	return (0);
}

