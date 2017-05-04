/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:00:01 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/02 20:20:14 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <dlfcn.h>
#define EX exit(-1);
#define LOAD_SYM(x) x##1 = dlsym(fmod_handler, #x); if (!x) puts(dlerror()), EX
#define PROTO_SYM(x) typeof(x) *x##1

static FMOD_SYSTEM	*g_fmod_system;
static void			*g_fmod_handler;
PROTO_SYM(g_fmod_system_sreate);
PROTO_SYM(g_fmod_system_init);
PROTO_SYM(g_fmod_system_createsound);
PROTO_SYM(g_fmod_sound_setloopcount);
PROTO_SYM(g_fmod_system_playsound);
PROTO_SYM(g_fmod_system_close);
PROTO_SYM(g_fmod_system_release);

void			fmod_init(void)
{
	fmod_handler = dlopen(FMOD_LIB, RTLD_LAZY);
	if (!fmod_handler)
	{
		puts(dlerror());
		exit(-1);
	}
	LOAD_SYM(g_fmod_system_create);
	LOAD_SYM(g_fmod_system_init);
	LOAD_SYM(g_fmod_system_createsound);
	LOAD_SYM(g_fmod_sound_setloopcount);
	LOAD_SYM(g_fmod_system_playsound);
	LOAD_SYM(g_fmod_system_close);
	LOAD_SYM(g_fmod_system_release);
	FMOD_System_Create1(&fmod_system);
	FMOD_System_Init1(fmod_system, 1, FMOD_INIT_NORMAL, NULL);
}

FMOD_SOUND		*load_sound(char *fname)
{
	FMOD_SOUND *music;

	if (FMOD_System_CreateSound1(fmod_system, fname, FMOD_2D | \
		FMOD_CREATESTREAM, 0, &music) != FMOD_OK)
	{
		printf("unable to load %s\n", fname);
		exit(-1);
	}
	FMOD_Sound_SetLoopCount1(music, -1);
	return (music);
}

void			play_sound(FMOD_SOUND *s)
{
	FMOD_System_PlaySound1(fmod_system, s, NULL, 0, NULL);
}

void			fmod_deinit(void)
{
	FMOD_System_Close1(fmod_system);
	FMOD_System_Release1(fmod_system);
}
