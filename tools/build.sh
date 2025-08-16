#!/bin/sh

cmake --build build --parallel

# copy completed build to dist for hosting (excluding index.html)
cp build/lwndhrst.github.io/lwndhrst.github.io.js   dist
cp build/lwndhrst.github.io/lwndhrst.github.io.wasm dist
cp build/lwndhrst.github.io/lwndhrst.github.io.data dist

# NOTE: might have to also copy resources later
