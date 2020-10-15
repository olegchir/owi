# OWI - Drawing over the Overwatch Replays

Now you can create your own epic Overwatch coaching series, similar to Stylosa's OverAnalyzed.

OWI manages an overlay that lets you to draw over the Overwatch window in real-time, allowing you to highlight important parts of your replay. The software that do actual drawing is Epic Pen, and this script do seamless transitions between the UI states. For example, if you want to clear your drawing, switch to Overwatch and turn off pause, now you can do it with a single button.

## Usage

* Ensure that system prerequisites are met and that all required software packages are installed

* Run Win Hide Tool
* Run Epic Pen
* With Epic Pen window active, click on the Win Hide Tool icon in tray
* Epic Pen main window should disappear

* Run Overwatch
* Load a replay
* Ensure it is paused

* Run owi.ahk from this repo (e.g. double click in Windows Explorer)
* Enjoy

* Optional: Run OBS or any other video recording software to record your epic Overwatch coaching series.

### Order of execution

Ensure that owi.ahk is loaded after the Epic Pen and Overwatch, exactly in this order!

If you started owi.ahk either before Overwatch or Epic Pen, you can fix it by pressking Ctrl + L, it will hard reload this script. Alternatively you can find AHK icon in the tray, right click it and activate the "Reload This Script" menu item.

## Controls

The controls are optimized for left hand, because you need right hand inside Overwatch.
You can change the script to fit your needs.

* CapsLock - cycle between the view and editor modes
* Ctrl + Z - clear screen and switch back to the view mode
* Ctrl + X - clear screen, switch to the view mode and continue playback
* Ctrl + C - pause and switch to the editor mode
* Ctrl + L - reload this script
* Ctrl + K - suspend hotkeys (useful if you want copy something from your text editor)
* Ctrl + J - unsuspend hotkeys

## Prerequisites

### Apps

* Epic Pen for drawing on the screen: <https://epic-pen.com>, free version is OK
* Window-Hide, because Epic Pen can't hide itself: <www.window-hide.com>
* AHK for running this script: <https://www.autohotkey.com/>

* Please make sure that owi.exe located in the bin directory. If it is not, you can build it using the instructions in this file. Unfortunately this may require heavy programming skills and a lot of tools installed on your computer, so if you're not a C++ programmer don't try to do this at home.
  
### Settings

You must change settings inside the Epic Pen and Overwatch to match the settings inside the owi.ahk. This is the default layout:

#### Overwatch 

* Settings -> Controls -> Spectate -> Spectate Toggle Pause: Ctrl + S
* Settings -> Controls -> Replay -> Media Controls: Ctrl + D

#### Epic Pen

* Pencil: Ctrl + W
* Cursor: Ctrl + E
* Clear screen: Ctrl + Q
* Undo: Ctrl + R

### Building the C++ part

If you want to manually build the owi.exe, here's my recommendations.

Owi.exe is a simple C++ code that you can compile with Microsoft Visual Studio, given you created a MSVS project and so on. Personally I don't like this. 

This is the Way:

- [Install MSYS2](https://www.msys2.org/). It's like ArchLinux, but with Windows Kernel. Follow all steps, update everything as the page says.
- Cast this magic spell to set up environment: `pacman -S --needed base-devel mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain mingw-w64-i686-cmake mingw-w64-x86_64-cmake mingw-w64-x86_64-llvm mingw-w64-x86_64-clang`
- Now you can use CLion to build everything inside the IDE. That's it: don't read the remaining steps in this guide!
- But if you don't like CLion and want to build everything from the command line...
- Go to the MSYS2 installation directory (e.g. `C:\msys64`) and load he MinGW environment: `mingw64.exe`
- Locate this repository on your hard drive (a console command like `cd "C:\git\owi\owi-cpp"`)
- Create cmake files with command like that: `cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/clang++.exe" -G "CodeBlocks - MinGW Makefiles" "C:\git\owi\owi-cpp" -B "C:\git\owi\owi-cpp\cmake-build-debug"`
- Build actual exe file with: `cmake.exe --build "C:\git\owi\owi-cpp\cmake-build-debug" --target all -- -j 6`
- Get your exe file: `C:\git\owi\owi-cpp\cmake-build-debug\owi.exe`


- Don't forget to copy all necessary files to the distribution. You can either copy it from the MinGW distribution itself (if you don't mind it may be a copyright issue, ask your lawyer), they are located under `C:\msys64\mingw64\bin`. Alternatively you can build them by yourself from MSYS2 sources (which is obvously out of the scope of this guide). Usually you need `libgcc_s_seh-1.dll`, `libstdc++-6.dll` and `libwinpthread-1.dll`.
