7# Orbit
Orbit is a demo that I am developing to test and demonstrate my [entity component system implementation](https://github.com/talhacali/ECS). It is a quite simple game with
multiple types of objects that orbit around light sources. Objects can be pushed out of their orbit by the player. The aim is to have many entities, components, systems and
to push the limits of performance of my implementation. The version of C++ is 17 and I used OpenGL for rendering, stb for loading textures, glm as math library. 

The demo has at least 4 different types of entities that rotate and components and systems for transform, rendering, movement, lifetime, and collision. Entities spawn in random positions around a light source and they start orbiting. After their lifetime ends, they are destroyed. Objects can be pushed out of their orbit by the player by interacting with them and if they can't find another light source on the way, they are destroyed.

I borrowed the rendering engine from my [tinyengine](https://github.com/talhacali/tinyengine). The game has phong lighting with a directional light and point lights, material with diffuse and specular maps, and a fly-like camera.

## Current status
At the moment, there is one type of object which is a cube with container texture, there are Transform and Renderable components, and Render system. Lighting, and camera are up and running. There now is a light source with cubes around it.

### Work in progress
1. Add multiple light sources with multiple objects around.
2. Add different object types and create entities for them.
3. Add different light shapes.
4. Implement the movement system.
