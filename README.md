# ZorkTrek

<p align="center">
  <img src=".github/logo.png" alt="ZorkTrek logo" width="128" />
</p>

A Zork-style text adventure set in the Star Trek universe, written in
C++. It has an optional SDL and OpenGL map view.

## What it does

You command a starship and move between star systems, planets and moons
drawn from Star Trek lore (see `source/data`). Commands include
`warp`, `transwarp`, `back`, `scan`, `map`, `status`,
`target`, `phaser`, `launch`, `beam`, `use`, `repair`,
`help` and `quit`. `startgui` opens the graphical map.

## Tech

- C++
- SDL 1.2, SDL_ttf, SDL_image, SDL_mixer, OpenGL and FreeType
- Doxygen documentation in `doc`

## Building

On Debian or Ubuntu:

```sh
make deps   # installs the SDL and OpenGL development packages with apt
make build  # builds source/bin/zorktrek
make run
```

`make build-debug` and `make valgrind` are also available.

## License

Licensed under the Apache License 2.0. See [LICENSE](LICENSE).
