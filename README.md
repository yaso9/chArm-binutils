# chArm binutils

This is a fork of GNU binutils that has the aarch64 target modified to only support the chArm subset of the Arm architecture, a subset used for teaching computer architecture at UT Austin. The following instructions are supported:
- LDUR
- STUR
- MOVK
- MOVZ
- ADRP
- ADDS
- SUBS
- CMP
- MVN
- ORR
- EOR
- ANDS
- TST
- LSL
- LSR
- ASR
- B
- B.cond
- BL
- RET
- NOP

Additionally, only the Xn, XZR, and SP registers are supported.

## Compilation
Run the following
```
./configure --target=aarch64-elf
make -j
```
