###########################################################################
## File : checkMetal_rtw.mk
## 
## Makefile generated for MATLAB file/project 'checkMetal'. 
## 
## Makefile Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/checkMetal.lib
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

PRODUCT_NAME              = checkMetal
MAKEFILE                  = checkMetal_rtw.mk
COMPUTER                  = PCWIN
ARCH                      = win32
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2013a
START_DIR                 = C:/Users/ASADUL~1/DOCUME~1/GitHub/MAGNET~1/MYWORK~1/codegen/lib/CHECKM~1
RELATIVE_PATH_TO_ANCHOR   = .
MATLAB_BIN                = $(MATLAB_ROOT)/bin
MATLAB_ARCH_BIN           = $(MATLAB_ROOT)/bin/win32
PERL                      = $(MATLAB_ROOT)/sys/perl/win32/bin/perl.exe
GEN_LNK_SCRIPT            = $(MATLAB_ROOT)/rtw/c/tools/mkvc_lnk.pl
CMD_FILE                  = $(PRODUCT_NAME).lnk

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

TOOLCHAIN_MAKEFILE = checkMetal_rtw_tools.mk

-include checkMetal_rtw_tools.mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/checkMetal.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -IC:/Users/ASADUL~1/DOCUME~1/GitHub/MAGNET~1/MYWORK~1 -I$(START_DIR) -IC:/Users/ASADUL~1/DOCUME~1/GitHub/MAGNET~1/C_CONV~1 -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=checkMetal -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/checkMetal_initialize.c $(START_DIR)/checkMetal_terminate.c $(START_DIR)/checkMetal.c $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c

###########################################################################
## OBJECTS
###########################################################################

OBJS = checkMetal_initialize.obj checkMetal_terminate.obj checkMetal.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj

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

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS)
	@echo "### Creating command file: $(CMD_FILE)"
	$(PERL) $(GEN_LNK_SCRIPT) $(CMD_FILE) $(OBJS)
	@echo "### Created: $(CMD_FILE)"
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) /out:$(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"
	@echo "### Deleting command file: $(CMD_FILE)"
	$(RM) $(CMD_FILE)
	@echo "### Deleted: $(CMD_FILE)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	@echo "### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)\%.c
	@echo "### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src\%.c
	@echo "### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


%.obj : $(START_DIR)\%.c
	@echo "### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


%.obj : C:/Users/ASADUL~1/DOCUME~1/GitHub/MAGNET~1/MYWORK~1\%.c
	@echo "### Compiling "$<" ..."
	$(CC) $(CFLAGS) -Fo"$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(OBJS) : $(MAKEFILE) rtw_proj.tmw $(TOOLCHAIN_MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "###  PRODUCT = $(PRODUCT)"
	@echo "###  PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "###  BUILD_TYPE = $(BUILD_TYPE)"
	@echo "###  INCLUDES = $(INCLUDES)"
	@echo "###  DEFINES = $(DEFINES)"
	@echo "###  SRCS = $(SRCS)"
	@echo "###  OBJS = $(OBJS)"
	@echo "###  LIBS = $(LIBS)"
	@echo "###  MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "###  SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "###  TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "###  CFLAGS = $(CFLAGS)"
	@echo "###  ARFLAGS = $(ARFLAGS)"
	@echo "###  LDFLAGS = $(LDFLAGS)"
	@echo "###  SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "###  MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "###  MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "###  DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "###  EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "###  MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "###  Deleting $(PRODUCT) and all derived files..."
	$(RM) $(PRODUCT) $(OBJS)
	$(RM) *$(EXE_EXT)
	$(RM) *$(OBJ_EXT)
	$(RM) *$(SHAREDLIB_EXT)
	$(RM) *$(STATICLIB_EXT)
	$(ECHO) "###  Deleted: $(PRODUCT), all derived files"


