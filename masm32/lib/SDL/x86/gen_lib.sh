#!/bin/bash
sudo apt install mingw-w64-tools
gendef SDL.dll
gendef SDL_gfx.dll
i686-w64-mingw32-dlltool -m i386 -d SDL.def -l libSDL.a
i686-w64-mingw32-dlltool -m i386 -d SDL.def -l libSDL_gfx.a
