# Real-Mode-Ex
An x86 emulator specializing in 16-bit Real Mode

![RMX in action](/images/real-mode-ex.png)

**WARNING: This project is extremely early in development, expect many bugs or programs not to work**

## Why..?

As computers continue to evolve, things must inevitably be left in the past.  Sadly, this includes real mode.  Real mode is one of my favorite parts of the x86 computer, it serves an important role in being both an informative and fun tool to help when learning assembly, or even just for legacy applications.  I couldn't just sit back and watch real mode die.  This emulator is written entirely in software, meaning this will work on x86, ARM, PowerPC, and even RISC-V all alike, hopefully encouraging a new generation to give real mode a try, and maybe learn a few things about how computers work while doing it.

## Building

To build RMX, simply run GNU Make, `make`, in the root directory of the project.  Currently our project only targets raw libc and no other libraries.  A proof of concept ncurses UI is coming, however not actually implemented into the build yet.  This build has been tested and is working on both Windows and Linux, most other platforms with GNU utils should build it fine as well.

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

