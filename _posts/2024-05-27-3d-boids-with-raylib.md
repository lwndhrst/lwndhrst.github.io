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




## Contents

1. [Let there be Boids!](#let-there-be-boids)
2. [Turning 1000 Draw Calls into 1](#turning-1000-draw-calls-into-1)
3. [Multi-threading the Simulation Loop with OpenMP](#multi-threading-the-simulation-loop-with-openmp)
4. [Speeding it up with a Spatial Hash Grid](#speeding-it-up-with-a-spatial-hash-grid)




## Let there be Boids!

While I was looking for a small project to practice what I had heard about at
university, I stumbled upon Ben Eater's demonstration of a simple [2D Boid
Algorithm](https://eater.net/boids). I thought it looked fun and it would allow
me to try out a few different things such as instanced rendering, spatial
partitioning and some simple multi-threading. If you're interested, the final
source code is available here:
[github:lwndhrst/cboids](https://github.com/lwndhrst/cboids).


### How do Boids generally work?

The term *boid* refers to *bird-like objects* and is typically used in the
context of flocking simulations that try to mimic the swarm behavior of birds.
Each individual boid underlies a set of constraints that determines its
behavior. These constraints can be purely based on the position, orientation
and velocity of other boids that are part of the same scene. By incorporating
other factors such as the position of the user's mouse cursor or the size of
the visible area, this core set of behavioral rules can be arbitrarily
extended.

It would be quite boring if I were to recite the historical background of boids
and how their core behavioral constraints were derived. For the sake of this
article, let's just have a brief look at the three main rules that [Craig W.
Reynolds describes in his paper](https://doi.org/10.1145%2F37401.37406) from
1987:

1. *Collision Avoidance*: avoid collisions with nearby flockmates
2. *Velocity Matching*: attempt to match velocity with nearby flockmates
3. *Flock Centering*: attempt to stay close to nearby flockmates

With just these three simple ideas, it is possible to create surprisingly
realistic flocking behavior.


### Implementing 3D Boids with C and Raylib

Pretty much all of our Computer Graphics courses at university required us to
use C++.

Based on [V. Hunter Adams
article](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html)
and the pseudocode he provides, I chose to implement the following simulation
parameters, which can later be used to influence the simulation:

- turn_factor;
- visual_range;
- protected_range;
- centering_factor;
- avoid_factor;
- matching_factor;
- max_speed;
- min_speed;

TODO:
- setting up the simulation loop (joy of using raylib and plain c)
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
