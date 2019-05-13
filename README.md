# Space-Invader
My old incomplete version of the [Space Invader](https://en.wikipedia.org/wiki/Space_Invaders) game. <br>
*Missing: Menus, sounds and usage rules.*
### OS
Windows only.
### Dependencies
PDCurses
## Installation ( Visual Studio 2017 )
* Download the repository by clicking the green "Clone or download" button on the top-right of the repository's main page, then click on "Download ZIP"
* Create new project in Visual Studio and extract the zipped file in it
* Visual Studio 2017 [Source](https://stackoverflow.com/questions/42708392/install-pdcurses-on-visual-studio-2017?noredirect=1&lq=1)
    * Take the developer command prompt of VS2017 community edition and type in set `PDCURSES_SRCDIR=<PDCurses Directory Location>`; in my case it was

    ``` 
    set PDCURSES_SRCDIR=C:\pdcurses-master 
    ```

    * Navigate in the command window to the directory of PDcurses/wincon (in my case `C:\pdcurses-master\wincon`)

    * ` nmake –f Makefile.vc `
    (This is the make file for pd curses.) It will create the pdcurses.lib for our Visual Studio.

    * Now we need to incorporate the generated library into our project. So open up your project and go to project properties
      - In “VC++ Directories”, change:
        - Include directories: Add a new file-path to PDCurses installation directory, in my case it is `C:\pdcurses-master`.
        - Library directories: Add a new file-path to PDCurses installation library directory, in my case it is `C:\pdcurses-master\win32`.

      - In C/C++:
        - In “Code Generation” tab, change “Runtime Library” to “Multithreaded Debug (/MTd)”. (Usually, it is set already)
      - In Linker:
        - In “Input” tab, add pdcurses.lib to Additional Dependencies (I initially got confused - remeber, it is the input tab of linker)
      - Click on Apply, and OK.
* Build and run project

## Usage

* How to run:
   * Download and run the SpaceInvader.exe in the repo <br>
   *or*
   * Build and run Visual studio project by following the installation procedure

* Rules:
   * Tap `A` or `D` to move left or right or double tap to jump by a level-restrained boost 
   * Tap `Space` to shoot
   * There is 5 levels in the game, each with certain number of invaders you need to kill. Boss rounds start above level 2

