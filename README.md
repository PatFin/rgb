# Small driver for 32x32 RGB panel

This project contains a driver for a 32x32 rgb panel driven by a raspberryPi and an Adafruit Matrix Bonnet for RaspberryPi. Along with this small driver, four demonstrations program are provided:

+ Cascade: an animation consisting in falling lines of color
+ Cycle: flashing of the whole panel in an randomly selected uniform color
+ Raindrop: a variation of Cascade using colorful raindrops falling down the panel
+ Random: random blinking of all the LEDs of the panel

## Dependencies

+ [wiringPi](http://wiringpi.com/): GPIO Interface library for the Raspberry Pi

## Build instructions

1. Clone the repository
```
pi@raspberry:~ $ git clone https://github.com/PatFin/rgb.git
Cloning into 'rgb'...
...
```
2. Create a build directory and generate the Makefile

```
pi@raspberry:~ $ mkdir rgb/build
pi@raspberry:~ $ cd rgb/build
pi@raspberry:~/rgb/build $ cmake ../src
--- The C compiler identification is GNU 8.3.0
...
```

3. Build the project

```
pi@raspberry:~/rgb/build $ make
Scanning dependencies of target RGB
...
[100%] Built target Cycle
```

4. Enjoy!

```
pi@raspberry:~/rgb/build $ ./Random
```
Use Ctrl+C to stop the programs.
