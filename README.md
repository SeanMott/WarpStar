# Warp Star - A fork* of Slippie Ishiiruka R10 for the purpose of supporting KAR Netplay 

[Netplay Website](https://www.kirbyairrideonline.com/) | [Netplay Discord](http://discord.gg/p3rGrcr) | [Wiki](https://kar.miraheze.org/wiki/Main_Page) | [KAR Workshop]()

NO LONGER MAINTAINED, THIS REPO HAS BEEN ABANDONED AND ALL WORK HAS MOVED TO [REAL KARPHIN](https://github.com/SeanMott/KARphin)

Warp Star is a fork* of [Slippie](https://github.com/project-slippi/Ishiiruka/tree/slippi) Ishiiruka R10 for the purpose of supporting KAR Netplay. It is differant from [KARphin](https://github.com/SeanMott/KARphin) which is a fork of Dolphin 5.0 for the purpose of supporting KAR Netplay.

Warp Star is an emulator for running ~~GameCube and Wii games~~ Kirby Air Ride (KAR) on Windows,
Linux, macOS, and recent Android devices. It's licensed under the terms
of the GNU General Public License, version 2 or later (GPLv2+).

<b>We reccomand using [KAR Workshop]() for downloading the needed programs and files for KAR Netplay.</b>

## System Requirements
### Desktop
* OS
    * Windows (7 SP1 or higher is officially supported, but Vista SP2 might also work).
    * Linux.
    * macOS (10.10 Yosemite or higher).
    * Unix-like systems other than Linux are not officially supported but might work.
* Processor
    * A CPU with SSE2 support.
    * A modern CPU (3 GHz and Dual Core, not older than 2008) is highly recommended.
* Graphics
    * A reasonably modern graphics card (Direct3D 10.0 / OpenGL 3.0).
    * A graphics card that supports Direct3D 11 / OpenGL 4.4 is recommended.

### Android
* OS
    * Android (5.0 Lollipop or higher).
* Processor
    * An ARM processor with support for 64-bit applications. (An Intel x86 processor could also work in theory, but no known x86 devices support 64-bit applications.)
* Graphics
    * A graphics processor that supports OpenGL ES 3.0 or higher. Performance varies heavily with [driver quality](https://dolphin-emu.org/blog/2013/09/26/dolphin-emulator-and-opengl-drivers-hall-fameshame/).
    * A graphics processor that supports standard desktop OpenGL features is recommended for best performance.

<b> Dolphin can only be installed on devices that satisfy the above requirements. Attempting to install on an unsupported device will fail and display an error message. </b>



## Uninstalling
When Dolphin has been installed with the NSIS installer, you can uninstall
Dolphin like any other Windows application.

Linux users can run `cat install_manifest.txt | xargs -d '\n' rm` as root from the build directory
to uninstall Dolphin from their system.

macOS users can simply delete Dolphin.app to uninstall it.

Additionally, you'll want to remove the global user directory (see below to
see where it's stored) if you don't plan to reinstall Dolphin.

## Video Backends

## Audio Backends

