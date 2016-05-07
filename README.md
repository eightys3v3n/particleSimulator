a program to simulate basic interactions between particles by terrence plunkett with input from sean.

this program simulates a number of 2D particles on the screen. you can left click to create new particles and drag around particles; right click and drag to select a box that deletes all particles inside it.

To Compile:
requires: SFML, make, c++ 17+ or gcc 5.3+
* 'make -j4' || 'make'

To Run:
* './main <arguments>'

Arguments:
arguments can be entered when run initially or by typing '/' in the window, then the argument, then enter. the simulation should pause but you will not see what your typing.
particles<int>    | sets the number of particles in the simulation. will resize while running by deleting particles somewhat randomly.
framerate<int>    | sets the maximum framerate
globalMass<int>   | sets the mass of every particle
globalRadius<int> | sets the radius of all the particles
randomize_masses  | randomizes all the masses
pause             | pause simulation
resume            | resume simulation

left arrow key  | move the entire universe right
right arrow key | move the entire universe left
down arrow key  | move the entire universe up
up arrow key    | move the entire universe down
