/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:27:20 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/03 14:10:27 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler_sigint(int sig)
{
    if(!s_general

void handler_sigquit(int sig)
{
    
}

int event(void)
{
    return(EXIT_SUCCESS);
}
    
void init_signals(void)
{
    rl_event_hook = event;
    signal(SIGINT, handler_sigint);
    signal(SIGQUIT, SIG_IGN);
}


/*
En términos generales, `rl_event_hook` parece ser un punto de entrada para 
el manejo de eventos relacionados con la terminal. En algunos sistemas 
operativos y bibliotecas, esta función se utiliza como un método de 
llamada por señal para que las aplicaciones puedan registrar sus propios 
handlers de evento.

Aquí hay algunas posibilidades sobre lo que podría hacer la función 
`rl_event_hook`:

1.  **Manejo de eventos de terminal**: La función podría ser responsable 
de manejar diferentes tipos de eventos relacionados con la terminal, como 
cambios en el input, pulsaciones del teclado o llegadas de señales de 
control.
2.  **Asignación de handlers de evento**: La función podría permitir a las 
aplicaciones registrar sus propios handlers de evento para responder 
específicamente a ciertos tipos de eventos que ocurran en la terminal.
3.  **Notificación de cambios**: La función podría notificar a las 
aplicaciones sobre cambios en el estado de la terminal, como cambios en el 
cursor o la posición del cursor.*/

/*### `event(void)`

*   This is an empty function declared as `int` that returns 
`EXIT_SUCCESS`.
*   It seems that this function might have been intended to handle some 
system event, but it doesn't actually do anything in the provided code.

### `sigint_handler(int sig)`

*   This function is a signal handler for the `SIGINT` signal.
*   When `SIGINT` is received (usually triggered by pressing Ctrl+C), this 
function is called.
*   Here's what it does:
    *   If `g_global.in_heredoc` is not set, it prints a newline character 
to the standard error stream (`STDERR_FILENO`).
    *   If `g_global.in_cmd` is true, it sets `stop_heredoc` to 1, clears 
the current readline input line, and displays a prompt.
        *   It uses `rl_replace_line` to clear the current input line.
        *   Then it calls `rl_redisplay` to update the display and trigger 
the next call to `readline`.
    *   If `g_global.in_cmd` is false, it simply triggers a new newline in 
the readline buffer using `rl_on_new_line`.
*   The `(void) sig;` line discards the signal that triggered this 
handler. It's unnecessary but allowed by POSIX for historical reasons.

### `sigquit_handler(int sig)`

*   This function is a signal handler for the `SIGQUIT` signal.
*   When `SIGQUIT` is received, it prints "Quit: " followed by the value 
of the signal to standard error (`STDERR_FILENO`) and then a newline 
character.
*   Like the previous handler, this also discards the signal with `(void) 
sig;`.

### `init_signals(void)`

*   This function initializes signal handling for certain signals.
*   Here's what it does:
    *   It sets up an event hook using `rl_event_hook = event`, which is a 
function that returns immediately without doing anything. In this case, it 
might have been intended to handle some system event but remains unused.
    *   It sets the signal handler for `SIGINT` to `sigint_handler`.
    *   It ignores `SIGQUIT` signals by calling `signal(SIGQUIT, 
SIG_IGN)`, which essentially tells the program to not catch this signal. 
Instead, it will propagate normally.

In summary, this code handles two types of signals: `SIGINT` (which is 
typically triggered when you press Ctrl+C in a terminal) and `SIGQUIT`. 
When these signals are received, they print a message on standard error, 
clear the current input line if necessary, or trigger a new newline. The 
signal handling for `SIGQUIT` is set to ignore it instead of catching it 
like `SIGINT`.

