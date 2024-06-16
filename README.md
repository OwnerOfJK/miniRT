# miniRT
Raytracing project modelling 3D objects while simulating light beams.

## How to clone

In order to properly clone the repo with all including submodules please:

`git clone --recurse-submodules https://github.com/OwnerOfJK/miniRT.git`


## How to run

### Mandatory Scenes
In order to run the program compile with `make` and run the executable with a scene as input.

`./miniRT scenes/mandatory/spheres.rt`

### Invalid Scenes
If you would like to check for faulty inputs you can run any of the maps inside the `scenes/invalid` folder.

`./miniRT scenes/invalid/map.r`

### Test Scenes
In order to test the current version of the renderer use the following command:

`./miniRT scenes/test_inputs/sphere_intersection.rt`
