# Testbed Application

To compile this application you must have the open-source `pspsdk` installed and in the system `PATH` then run `build.sh` in this directory.

`build.sh` supports building as `EBOOT.PBP` or `.prx`. The default is PRX but it can be changed by passing the `PRX=0` argument to the script. 

To run the application on Linux PPSSPP, make sure to have PPSSPPP installed using Flatpak then run `test.sh` and finally press `n` when prompted.

To run the application on Windows PPSSPP on Linux, make sure you have Wine installed and a version of Windows PPSSPP in `./emu_win` then run `test.sh` and finally press `y` when prompted. Example directory structure is below.
```
testbed/
├── emu_win/
│	├── PPSSPPWindows64.exe
│	└── PPSSPPWindows.exe
├── main.cpp
├── Makefile
└──	README.md
```

You should modify the `test.sh` script to support other platforms if required.
