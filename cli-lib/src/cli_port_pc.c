/*
 * cli_port_pc.c
 *
 * Implementación de la HAL para PC (Linux y Windows).
 * Útil para desarrollo, testing y simulación en escritorio.
 *
 * Linux: termios + fcntl (modo raw, no bloqueante)
 * Windows: conio.h (_kbhit / _getch)
 */

#include "../include/cli_port.h"
#include <stdio.h>

/* ================================================================== */
/*  WINDOWS                                                             */
/* ================================================================== */
#ifdef _WIN32

#include <conio.h>

bool CLI_Port_IsCharAvailable(void)
{
    /* _kbhit() retorna non-zero si hay tecla en el buffer, sin bloquear */
    return (_kbhit() != 0);
}

int CLI_Port_GetChar(void)
{
    /* _getch(): lee carácter sin eco, sin esperar Enter */
    return _getch();
}

void CLI_Port_Print(const char *str)
{
    printf("%s", str);
    fflush(stdout);
}

/* ================================================================== */
/*  LINUX / macOS                                                       */
/* ================================================================== */
#else

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/* Peek buffer a nivel de módulo (compartido entre Is y Get) */
static int  s_peek_char  = 0;
static bool s_peek_valid = false;

static struct termios s_original_termios;
static bool           s_terminal_configured = false;

static void ConfigureRawTerminal(void)
{
    if (s_terminal_configured) return;

    struct termios raw;
    tcgetattr(STDIN_FILENO, &s_original_termios);
    raw = s_original_termios;

    raw.c_lflag &= ~(ICANON | ECHO); /* sin modo canónico, sin eco */
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    s_terminal_configured = true;
}

bool CLI_Port_IsCharAvailable(void)
{
    ConfigureRawTerminal();

    if (s_peek_valid) return true;

    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        s_peek_char  = (int)c;
        s_peek_valid = true;
        return true;
    }
    return false;
}

int CLI_Port_GetChar(void)
{
    if (s_peek_valid) {
        s_peek_valid = false;
        return s_peek_char;
    }
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1) return (int)c;
    return -1;
}

void CLI_Port_Print(const char *str)
{
    printf("%s", str);
    fflush(stdout);
}

#endif /* _WIN32 */
