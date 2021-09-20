# GravSim

GravSim is a simple 2D newtonian gravitation simulation

## Building and running

```bash
# Clone this repository
git clone https://github.com/cephox/GravSim

# Build the executable
cd GravSim
cmake .
make

# Cleaning up
# This will remove all build files (except the resulting executable)
./clean.sh
```

The executable file is named `gravsim`.

### Dependencies

- [SFML](https://sfml-dev.org/)

Other libraries (such as [Dear ImGui](github.com/ocornut/imgui) and [imgui-sfml](https://github.com/eliasdaler/imgui-sfml)) are located in [vendor/\<library name\>](vendor/) and being built on compilation.
Their respective Licenses are found in their separate folder.

## Known issues

- Not everywhere is begin drawn
- Somehow undeterministic, random errors
