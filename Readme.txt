-------- PROJECT GENERATOR --------
PROJECT NAME :	MotorDriver
PROJECT DIRECTORY :	C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver
CPU SERIES :	SH-2
CPU TYPE :	SH7125
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.4.3.0
GENERATION FILES :
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\dbsct.c
        Setting of B,R Section
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\typedefine.h
        Aliases of Integer Type
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\sbrk.c
        Program of sbrk
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\iodefine.h
        Definition of I/O Register
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\intprg.c
        Interrupt Program
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\vecttbl.c
        Initialize of Vector Table
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\vect.h
        Definition of Vector
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\resetprg.c
        Reset Program
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\hwsetup.c
        Hardware Setup file
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\MotorDriver.c
        Main Program
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\sbrk.h
        Header file of sbrk file
    C:\Users\Kosuke\Develop\SH\MotorDriver\MotorDriver\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'000000000	DVECTTBL,DINTTBL,PIntPRG
 H'000000800	PResetPRG
 H'000001000	P,C,C$BSEC,C$DSEC,D
 H'0FFFFA000	B,R
 H'0FFFFBC00	S

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start H'1000.
* RAM start H'FFFFA000.

SELECT TARGET :
    SH-2 Simulator
DATE & TIME : 2019/11/12 21:24:53
