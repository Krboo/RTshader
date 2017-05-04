/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_strings.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 14:53:50 by alelievr          #+#    #+#             */
/*   Updated: 2016/07/21 00:27:03 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_STRINGS_H
# define TERM_STRINGS_H

# define T_SAVE_CURSOR_POSITION		"\x1b\x37"
# define T_RESTORE_CURSOR_POSITION	"\x1b\x38"
# define T_CLEAR_SCREEN				"\x1b\x5b\x48\x1b\x5b\x32\x4a"
# define T_CLEAR_ALL_AFTER_CURSOR	"\x1b\x5b\x4a"
# define TCVN1						"\x32\x35\x68"
# define T_CURSOR_VISIBLE			"\x1b\x5b\x3f\x31\x32\x6c\x1b\x5b\x3f" TCVN1
# define T_CURSOR_INVISIBLE			"\x1b\x5b\x3f\x32\x35\x6c"
# define T_CURSOR_HOME				"\x1b\x5b\x48"
# define T_BELL						"\x7"

#endif
