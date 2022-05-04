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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define SCREEN_BASE_HEIGHT       480

#define WINDOW_NAME              "Minesweeper"

#define WINDOW_BASE_HEIGHT       180
#define WINDOW_BASE_WIDTH        150

#define CELL_WIDTH               16
#define CELL_TEX_PATH_FMT        "textures/cell_%d.png"

#define BORDER_SEP_MARGIN_TOP    3
#define BORDER_TEX_PATH_FMT      "textures/border_%d.png"

#define SMILE_TEX_PATH_FMT       "textures/smile_%d.png"

#define COUNTER_TEX_PATH_FMT     "textures/counter_%d.png"

#define FIELD_MARGIN_TOP         4
#define FIELD_MARGIN_LEFT        1
#define FIELD_MARGIN_RIGHT       1
#define FIELD_MARGIN_BOTTOM      1

#define SMILE_MARGIN_TOP         1

#define COUNTER_WIDTH_F          0.82f
#define COUNTER_HEIGHT_F         1.45f

#define DEFAULT_VSHADER_PATH     "shaders/default.vert"
#define DEFAULT_FSHADER_PATH     "shaders/default.frag"

#define ICON_PATH                "icon.png"

#endif /* DEFINITIONS_H */