/*
                                  The MIT License (MIT)

                               Copyright (c) 2022 adasdead

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
    A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "game/game.h"

// MSVC Hook
#ifdef _MSC_VER

#include <windows.h>
#include <stdlib.h>

#define _app_main_ _app_main

int _app_main(int argc, char **argv);

int WINAPI wWinMain(HINSTANCE hInst,
                    HINSTANCE hPreInst,
                    PWSTR lpCmdLine,
                    int nCmdShow)
{
    char **buffer = malloc(sizeof(char*));
    buffer[0] = calloc(512, sizeof(char));

	GetModuleFileNameA(NULL, buffer[0], 512);

    return _app_main(1, (char**) buffer);
}

#else

#define _app_main_ main

#endif

int _app_main_(int argc, char **argv)
{
    game_init(argc, argv);
    game_loop();
    game_free();
    return 0;
}