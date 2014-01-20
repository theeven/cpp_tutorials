                    ----------------------------
                    Advanced C++ "AdvCPP" folder
                           Updated 9/2011
                    ----------------------------

This folder contains lab materials for "Advanced C++".

=======================================================
C:\AdvCPP Folder Contents (or $HOME/advcpp under *nix):
=======================================================

    01_Recent_Additions_Lab,
    02_Template_Mechanics_Lab, etc. folders:
        Lab exercises.
        Lab basis files (if any) are located directly in the folders;
        solutions may be found in subdirectories named "soln".

    00_Demo folder:
        hello.cpp:      to test that your compiler is installed correctly
        tdebug.cpp:     to test the "debug" STL library with gcc
        err-sample.cpp: to test compiling with/without "STLFilt"
        UtilsDemo.cpp:  simple demo of using the ESTLUtil.h utility header

    ESTLUtil.h header file:
        Utility templates and macros to make STL-related labs easier.
        It is placed up here to make it easy to access using

            #include "../ESTLUtil.h"

        from folders directly below. Note: the namespace is "ESTLUtils"
                                                                     ^

    UtilsTest.cpp:
        A FULL demo of the use of the "ESTLUtil.h" header file
        facilities for:
            a) Populating STL containers with sequences of values
            b) Conveniently displaying the contents of those containers
            c) Timing the execution of sections of code
        (A minimal demo highlighting facilities that are most useful for
        the lab exercises, UtilsDemo, is in the 00_Demo folder).

    PDF:
        PDF files for all course materials

    STLFilt:
        Leor Zolman's "STL Error Message Decryptor" utility
