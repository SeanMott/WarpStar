# Building for Windows

Use the solution file `Source/dolphin-emu.sln` to build Dolphin on Windows.
~~Visual Studio 2015 Update 2 is a hard requirement. Other compilers might be
able to build Dolphin on Windows but have not been tested and are not
recommended to be used. Git and Windows 10 SDK 10.0.10586.0 must be installed.~~

Nie, Jas ported it over to use Windows 10 SDK 10.0.17763.0 and 2015-2019 142V build tools. Thoses can be aquired [here]() or use the installer python script in the repo root called `SetUpWInBuildEnv.py`, or use [KAR Workshop]() to set up your dev envirment.

An installer can be created by using the `Installer.nsi` script in the
Installer directory. This will require the Nullsoft Scriptable Install System
(NSIS) to be installed. Creating an installer is not necessary to run Dolphin
since the Binary directory contains a working Dolphin distribution.