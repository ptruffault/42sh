/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:50:42 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:08:28 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_INPUT_H
# define FT_GET_INPUT_H

# define FAILURE 0
# define SUCCESS 1

# define KEY_ENTER 0xA
# define KEY_TAB 9

# define KEY_ARROW_UP 4283163
# define KEY_ARROW_DOWN 4348699
# define KEY_ARROW_LEFT 4479771
# define KEY_ARROW_RIGHT 4414235

# define KEY_OPTION_ARROW_UP 1096489755
# define KEY_OPTION_ARROW_DOWN 1113266971
# define KEY_OPTION_ARROW_LEFT 1146821403
# define KEY_OPTION_ARROW_RIGHT 1130044187

# define KEY_SHIFT_ARROW_UP 71683997260571
# define KEY_SHIFT_ARROW_DOWN 72783508888347
# define KEY_SHIFT_ARROW_LEFT 74982532143899
# define KEY_SHIFT_ARROW_RIGHT 73883020516123

# define KEY_CTRL_C 3
# define KEY_CTRL_D 4
# define KEY_CTRL_L 12
# define KEY_CTRL_R 18

# define KEY_HOME 4741915
# define KEY_END 4610843

# define KEY_SHIFT_HOME 79380578655003
# define KEY_SHIFT_END 77181555399451

# define KEY_BACKSPACE 127
# define KEY_DELETE 2117294875

# define KEY_OPTION_C 42947
# define KEY_OPTION_V 10127586

# define CURSOR_UP "up"
# define CURSOR_MHORIZ "ch"

# define PS1 "$[GREEN]42sh$[RESET]:[$[BLUE]$[UNDERLINE]${PWD}$[RESET]]"
# define PS2 "$[RED]%$[RESET] >"

typedef enum	e_colors
{
	BLUE = 0,
	RED,
	BLUE2,
	UNDERLINE,
	RESET,
	GREEN,
	CYAN1,
	MAGENTA1,
	YELLOW
}				t_colors;

#endif
