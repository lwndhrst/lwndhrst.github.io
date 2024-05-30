---
layout:     post
title:      "3D Boids with C and Raylib"
date:       2024-05-27
categories: c raylib boids spatial-partitioning
---

<div style="position: relative; overflow: hidden; width: 100%; padding-top: 56.25%;">
  <iframe
    style="position: absolute; top: 0; left: 0; bottom: 0; right: 0; width: 100%; height: 100%;"
    src="https://www.youtube.com/embed/tiQMZTRqvHI"
    allowfullscreen="allowfullscreen"
  ></iframe>
</div>
<br>

- [github:lwndhrst/cboids](https://github.com/lwndhrst/cboids)




## Contents

1. [Let there be Boids!](#let-there-be-boids)
2. [Turning 1000 Draw Calls into 1](#turning-1000-draw-calls-into-1)
3. [Multi-threading the Simulation Loop with OpenMP](#multi-threading-the-simulation-loop-with-openmp)
4. [Speeding it up with a Spatial Hash Grid](#speeding-it-up-with-a-spatial-hash-grid)




## Let there be Boids!

While I was looking for a small project to practice what I had heard about at
university, I stumbled upon Ben Eater's demonstration of a simple [2D Boid
Algorithm](https://eater.net/boids). I thought it looked fun and it would allow
me to try out a few different things such as *instanced rendering*, *spatial
partitioning* and some basic *multi-threading*.


### How do Boids generally work?

TODO:
- boid properties
- behavioral constraints + pseudocode
- [https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html)


### Implementing 3D Boids with C and Raylib

Pretty much all of our Computer Graphics courses at university required us to
use C++.

TODO:
- setting up the simulation loop
- code snippets per constraint
- draw call per boid
- funny floating point effects at high fps




## Turning 1000 Draw Calls into 1

TODO:
- going from draw calls per boid to instanced rendering
- array of transforms
- vertex shader for instanced rendering




## Multi-threading the Simulation Loop with OpenMP

TODO:
- linear speedup


### Dangers to be aware of ...

TODO:
- data races, deadlocks, etc.


### ... and why it's easy in this case

TODO:
- "double-buffered" simulation loop means read and write arrays are disjoint
    => can read without worry
- each thread gets a disjoint range of indices (by OpenMP) into write array
    => no race conditions for writing




## Speeding it up with a Spatial Hash Grid

TODO:
- spatial partitioning techniques


### The Simulation Loop is sloooow

TODO:
- O(n^2)


### How Spatial Partitioning can speed it up

TODO:
- severly reduce search space


### Building a simple Spatial Hash Grid

TODO:
- API
- memory management
- ...


### Integrating it into the Simulation Loop

TODO:
- multiple grids, one per thread to avoid write conflicts
- "double-buffered" => can read without worry




## References

- [https://eater.net/boids](https://eater.net/boids)
- [https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html)
