# Real-Mode-Ex
An x86 emulator specializing in 16-bit Real Mode

![RMX in action](/images/real-mode-ex.png)

**WARNING: This project is extremely early in development, expect many bugs or programs not to work**

## Why..?

As computers continue to evolve, things must inevitably be left in the past.  Sadly, this includes real mode.  Real mode is one of my favorite parts of the x86 computer, it serves an important role in being both an informative and fun tool to help when learning assembly, or even just for legacy applications.  I couldn't just sit back and watch real mode die.  This emulator is written entirely in software, meaning this will work on x86, ARM, PowerPC, and even RISC-V all alike, hopefully encouraging a new generation to give real mode a try, and maybe learn a few things about how computers work while doing it.

## Building

### Building on Windows

Download Msys2, a toolchain which closely emulates a \*nix build environment.  Make sure to setup gcc.  To install SDL2, type `pacman -Ss SDL2` and install the package that you need, either the i686 or x86_64 one.  After that simply typing `make` should result in a working build

### Building on \*nix

Download SDL2 from your package manager, what ever that may be.  Note, on a system like Debian or Ubuntu, make sure to download the development package for SDL2.  After doing that, running the make file with `make` should work.

## Supported Platforms:

* Linux
* Mac OS
* Windows
* Any other platform with libc and GNU Make (haiku, the BSDs, Illumos, etc)

## Planned Supported Platforms:

* UEFI
* x86 Bare Metal (protected mode)
* ARM Bare Metal (Mostly for singleboard computers such as the Raspberry Pi)

## How does it work?

RMX works by trying to emulate all facets of an early x86 processor.  This is a monumental task, so at the current moment, many things are thrown together without much care for accuracy as much as they are to make sure the emulator works.  If you encounter any bugs with the emulation, please leave an issue report.

## How much of it is implemented?

Not very much, roughly around 10%.  Development has mostly been slow due to a busy work schedule for me, as well as shortjumps taking a while to implement without problem.  The project is still under active development however, and always changing.

## Notes on the dependency on SDL2

Currently our window system depends on SDL2.  At the moment this is here mostly as a cross platform solution for graphics and text rendering, however is not preferable.  At this time, we are not ready to start developing native X11, Win32, or Cocoa window systems for RMX, so we will rely on a library which handles most of that for us, despite the fact it may be slower than an implementation we could write.

