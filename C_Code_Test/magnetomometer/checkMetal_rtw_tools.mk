###########################################################################
## File : checkMetal_rtw_tools.mk
## 
## Makefile generated for MATLAB file/project 'checkMetal'. 
## 
## Makefile Info:
## 
## Toolchain Name:          LCC-win32 v2.4.1 | gmake (32-bit Windows)
## Supported Version(s):    2.4.1
## ToolchainInfo Version:   R2013a
## Specification Revision:  1.0
## 
## MATLAB Coder version: 2.4 (R2013a)
## 
###########################################################################




#-----------
# MACROS
#-----------

LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win32/lcc
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win32
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include
MEX_OPTS_FILE      = $(MATLAB_BIN)/win32/mexopts/lccopts.bat

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win32 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = $(CC_PATH)/lcc

# Archiver: Lcc-win32 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = $(AR_PATH)/lcclib

# Linker: Lcc-win32 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = $(LD_PATH)/lcclnk

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = $(MEX_PATH)/mex

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder Application: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win32
MAKE = $(MAKE_PATH)/gmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
LDDEBUG             =
OUTPUT_FLAG         = -o
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 = @cmd /C

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              =
CFLAGS               = -c -noregistrylookup -I$(LCC_ROOT)/include
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LCC_LIB)/wsock32.lib $(LDFLAGS_ADDITIONAL)
MEX_CFLAGS           = -win32 $(MEX_SRC) $(MEX_OPT_FILE)$(INCLUDES) -outdir $(RELATIVE_PATH_TO_ANCHOR)
MEX_LDFLAGS          = LINKFLAGS="$$LINKFLAGS $(LDFLAGS_ADDITIONAL)"
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -s -L$(LCC_LIB) $(LCC_LIB)/wsock32.lib $(LDFLAGS_ADDITIONAL) $(DEF_FILE)

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
STATICLIB_EXT       = .lib
EXE_EXT             = .exe
SHAREDLIB_EXT       = .dll
MEX_EXT             = .mexw32
MAKE_EXT            = .mk

