###########################################################################
## File : FFT_CO2_rtw.mk
## 
## Makefile generated for MATLAB file/project 'FFT_CO2'. 
## 
## Makefile Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)\FFT_CO2.lib
## Product type : static-library
## 
## MATLAB Coder version: 2.4 (R2013a)
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.
# PERL                    PERL Tool
# GEN_LNK_SCRIPT          Perl script to generate the command file
# CMD_FILE                Command file

PRODUCT_NAME              = FFT_CO2
MAKEFILE                  = FFT_CO2_rtw.mk
COMPUTER                  = PCWIN
ARCH                      = win32
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2013a
START_DIR                 = C:\Users\Raju\Desktop\Github\CO2_SE~1\code\Raju\MATLAB\codegen\lib\FFT_CO2
RELATIVE_PATH_TO_ANCHOR   = .
MATLAB_BIN                = $(MATLAB_ROOT)\bin
MATLAB_ARCH_BIN           = $(MATLAB_ROOT)\bin\win32
PERL                      = $(MATLAB_ROOT)\sys\perl\win32\bin\perl.exe
GEN_LNK_SCRIPT            = $(MATLAB_ROOT)\rtw\c\tools\mkvc_lnk.pl
CMD_FILE                  = $(PRODUCT_NAME).lnk
NODEBUG                   = 1

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

TOOLCHAIN_MAKEFILE = FFT_CO2_rtw_tools.mk

!include FFT_CO2_rtw_tools.mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)\FFT_CO2.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

#################################################################
# INCLUDE PATHS
#################################################################

INCLUDES_BUILDINFO = C:\Users\Raju\Desktop\Github\CO2_SE~1\code\Raju\MATLAB;$(START_DIR);$(MATLAB_ROOT)\extern\include;$(MATLAB_ROOT)\simulink\include;$(MATLAB_ROOT)\rtw\c\src;$(MATLAB_ROOT)\rtw\c\src\ext_mode\common;$(MATLAB_ROOT)\rtw\c\ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=FFT_CO2 -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\FFT_CO2_initialize.c $(START_DIR)\FFT_CO2_terminate.c $(START_DIR)\FFT_CO2.c $(START_DIR)\rt_nonfinite.c $(START_DIR)\rtGetNaN.c $(START_DIR)\rtGetInf.c

###########################################################################
## OBJECTS
###########################################################################

OBJS = FFT_CO2_initialize.obj FFT_CO2_terminate.obj FFT_CO2.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) 

CFLAGS = $(CFLAGS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) 

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_BASIC)

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS)
	@cmd /C "@echo ### Creating command file: $(CMD_FILE)"
	$(PERL) $(GEN_LNK_SCRIPT) $(CMD_FILE) $(OBJS)
	@cmd /C "@echo ### Created: $(CMD_FILE)"
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"
	@cmd /C "@echo ### Deleting command file: $(CMD_FILE)"
	$(RM) $(CMD_FILE)
	@cmd /C "@echo ### Deleted: $(CMD_FILE)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(MATLAB_ROOT)\rtw\c\src}.c.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(MATLAB_ROOT)\rtw\c\src}.cpp.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{C:\Users\Raju\Desktop\Github\CO2_SE~1\code\Raju\MATLAB}.c.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{C:\Users\Raju\Desktop\Github\CO2_SE~1\code\Raju\MATLAB}.cpp.obj :
	@cmd /C "@echo ### Compiling "$<" ..."
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(OBJS) : $(MAKEFILE) rtw_proj.tmw $(TOOLCHAIN_MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ###  PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ###  PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ###  BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ###  INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ###  DEFINES = $(DEFINES)"
	@cmd /C "@echo ###  SRCS = $(SRCS)"
	@cmd /C "@echo ###  OBJS = $(OBJS)"
	@cmd /C "@echo ###  LIBS = $(LIBS)"
	@cmd /C "@echo ###  MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ###  SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ###  TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ###  CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ###  CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ###  ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ###  LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ###  SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ###  MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ###  MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ###  DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ###  EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ###  MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "###  Deleting $(PRODUCT) and all derived files..."
	$(RM) $(PRODUCT) $(OBJS)
	$(RM) *_win32.exp
	$(RM) *_win32.lib
	$(RM) *$(EXE_EXT)
	$(RM) *$(OBJ_EXT)
	$(RM) *$(SHAREDLIB_EXT)
	$(RM) *$(STATICLIB_EXT)
	$(ECHO) "###  Deleted: $(PRODUCT), all derived files"


