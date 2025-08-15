#!/bin/sh

emcmake cmake -S . -B build -G Ninja -DPLATFORM=Web # -DGLFW_BUILD_WAYLAND=ON -DGLFW_BUILD_X11=OFF
