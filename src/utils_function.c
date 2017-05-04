/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:48:01 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/02 18:16:34 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <sys/time.h>

int				check_file_extension(char *file, char **exts)
{
	char			*ext;

	ext = file + strlen(file) - 1;
	while (ext != file && *ext != '.')
		ext--;
	ext++;
	while (*exts)
	{
		if (!strcmp(ext, *exts))
			return (1);
		exts++;
	}
	return (0);
}

void			display_window_fps(GLFWwindow *win)
{
	static int		frames = 0;
	static double	last_time = 0;
	double			current_time;
	char			fps[0xF00];

	current_time = glfwGetTime();
	frames++;
	if (current_time - last_time >= 1.0)
	{
		sprintf(fps, "Re Tweet - fps [%.3i ]",
				(int)(1.0 / (1000.0 / (float)frames) * 1000.0));
		glfwSetWindowTitle(win, fps);
		frames = 0;
		last_time++;
	}
}

float			get_current_time(void)
{
	struct timeval	t;
	static time_t	l_time = 0;

	if (l_time == 0)
		l_time = time(NULL);
	gettimeofday(&t, NULL);
	return ((float)(time(NULL) - l_time) + (float)t.tv_usec / 1000000.0
		- g_paused_time);
}

int				get_program(int p)
{
	static int		program = -1;

	if (p != -1)
		program = p;
	return (program);
}

char			*get_scene_directory(char *scene_dir)
{
	static char		*scene_directory = NULL;

	if (scene_dir)
		scene_directory = scene_dir;
	return (scene_directory);
}
