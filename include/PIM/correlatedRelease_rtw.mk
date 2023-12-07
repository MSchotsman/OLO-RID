###########################################################################
## Makefile generated for component 'correlatedRelease'. 
## 
## Makefile     : correlatedRelease_rtw.mk
## Generated on : Sun May 28 14:28:27 2023
## Final product: ./correlatedRelease.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = correlatedRelease
MAKEFILE                  = correlatedRelease_rtw.mk
START_DIR                 = C:/Users/s153326/DOCUME~1/School/2022-2~1/PREPAR~1/OLDRIDUAV/include/PIM
CMD_FILE                  = correlatedRelease_rtw.rsp
C_STANDARD_OPTS           = -fwrapv
MODELLIB                  = correlatedRelease.lib
SHELL                 	  = %SystemRoot%/system32/cmd.exe

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          MinGW64 | gmake (64-bit Windows)
# Supported Version(s):    6.x
# ToolchainInfo Version:   2023a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# C_COMP_ROOT
# C_COMP_C_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS            = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX        = $(WARN_FLAGS) -Wcast-qual -Wshadow
TOOLCHAIN_LIBS = -lws2_32

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC_PATH = $(C_COMP_ROOT)
CC = "$(CC_PATH)/gcc"

# Linker: GNU Linker
LD_PATH = $(C_COMP_ROOT)
LD = "$(LD_PATH)/g++"

# Archiver: GNU Archiver
AR_PATH = $(C_COMP_ROOT)
AR = "$(AR_PATH)/ar"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = $(C_COMP_ROOT)
MAKE = "$(MAKE_PATH)/mingw32-make.exe"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
RM                  = @del
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_COMP_C_STANDARD_OPTS) -m64 \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =  -static -m64
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined \
                       -Wl,--out-implib,$(notdir $(basename $(PRODUCT))).lib



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./correlatedRelease.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__USE_MINGW_ANSI_STDIO=1
DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=correlatedRelease

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/qhull/src/libqhull/global.c $(START_DIR)/qhull/src/libqhull/stat.c $(START_DIR)/qhull/src/libqhull/geom2.c $(START_DIR)/qhull/src/libqhull/poly2.c $(START_DIR)/qhull/src/libqhull/merge.c $(START_DIR)/qhull/src/libqhull/libqhull.c $(START_DIR)/qhull/src/libqhull/geom.c $(START_DIR)/qhull/src/libqhull/poly.c $(START_DIR)/qhull/src/libqhull/qset.c $(START_DIR)/qhull/src/libqhull/mem.c $(START_DIR)/qhull/src/libqhull/random.c $(START_DIR)/qhull/src/libqhull/usermem.c $(START_DIR)/qhull/src/libqhull/userprintf.c $(START_DIR)/qhull/src/libqhull/io.c $(START_DIR)/qhull/src/libqhull/user.c $(START_DIR)/qhull/src/libqhull/rboxlib.c $(START_DIR)/qhull/interface/mwQhull.c $(START_DIR)/correlatedRelease_data.c $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c $(START_DIR)/correlatedRelease_initialize.c $(START_DIR)/correlatedRelease_terminate.c $(START_DIR)/correlatedRelease.c $(START_DIR)/minOrMax.c $(START_DIR)/find.c $(START_DIR)/convhulln.c $(START_DIR)/mergeDuplicatePoints.c $(START_DIR)/sortLE.c $(START_DIR)/rand.c $(START_DIR)/mpower.c $(START_DIR)/eig.c $(START_DIR)/xnrm2.c $(START_DIR)/xdlapy3.c $(START_DIR)/recip.c $(START_DIR)/xdlaev2.c $(START_DIR)/xzlartg.c $(START_DIR)/xzladiv.c $(START_DIR)/power.c $(START_DIR)/rcond.c $(START_DIR)/schur.c $(START_DIR)/mpower_schur.c $(START_DIR)/norm.c $(START_DIR)/relop.c $(START_DIR)/gamrnd.c $(START_DIR)/randn.c $(START_DIR)/eml_rand_mt19937ar_stateful.c $(START_DIR)/sort.c $(START_DIR)/sortIdx.c $(START_DIR)/eml_rand_mt19937ar.c $(START_DIR)/xsyheev.c $(START_DIR)/xzlarfg.c $(START_DIR)/xzlarf.c $(START_DIR)/xgemv.c $(START_DIR)/xgerc.c $(START_DIR)/xzsteqr.c $(START_DIR)/xzlahqr.c $(START_DIR)/sqrt.c $(START_DIR)/xztrevc3.c $(START_DIR)/xhseqr.c $(START_DIR)/trisolve.c $(START_DIR)/xrotg.c $(START_DIR)/xzlascl.c $(START_DIR)/xzgebal.c $(START_DIR)/correlatedRelease_emxutil.c $(START_DIR)/correlatedRelease_emxAPI.c $(START_DIR)/correlatedRelease_rtwutil.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = global.obj stat.obj geom2.obj poly2.obj merge.obj libqhull.obj geom.obj poly.obj qset.obj mem.obj random.obj usermem.obj userprintf.obj io.obj user.obj rboxlib.obj mwQhull.obj correlatedRelease_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj correlatedRelease_initialize.obj correlatedRelease_terminate.obj correlatedRelease.obj minOrMax.obj find.obj convhulln.obj mergeDuplicatePoints.obj sortLE.obj rand.obj mpower.obj eig.obj xnrm2.obj xdlapy3.obj recip.obj xdlaev2.obj xzlartg.obj xzladiv.obj power.obj rcond.obj schur.obj mpower_schur.obj norm.obj relop.obj gamrnd.obj randn.obj eml_rand_mt19937ar_stateful.obj sort.obj sortIdx.obj eml_rand_mt19937ar.obj xsyheev.obj xzlarfg.obj xzlarf.obj xgemv.obj xgerc.obj xzsteqr.obj xzlahqr.obj sqrt.obj xztrevc3.obj xhseqr.obj trisolve.obj xrotg.obj xzlascl.obj xzgebal.obj correlatedRelease_emxutil.obj correlatedRelease_emxAPI.obj correlatedRelease_rtwutil.obj

ALL_OBJS = $(OBJS)

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

CFLAGS_ = -D_EXPORTING -w -fno-strict-aliasing
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_) $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


C_COMP_C_STANDARD_OPTS = $(C_STANDARD_OPTS)


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

global.obj : $(START_DIR)/qhull/src/libqhull/global.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stat.obj : $(START_DIR)/qhull/src/libqhull/stat.c
	$(CC) $(CFLAGS) -o "$@" "$<"


geom2.obj : $(START_DIR)/qhull/src/libqhull/geom2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


poly2.obj : $(START_DIR)/qhull/src/libqhull/poly2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


merge.obj : $(START_DIR)/qhull/src/libqhull/merge.c
	$(CC) $(CFLAGS) -o "$@" "$<"


libqhull.obj : $(START_DIR)/qhull/src/libqhull/libqhull.c
	$(CC) $(CFLAGS) -o "$@" "$<"


geom.obj : $(START_DIR)/qhull/src/libqhull/geom.c
	$(CC) $(CFLAGS) -o "$@" "$<"


poly.obj : $(START_DIR)/qhull/src/libqhull/poly.c
	$(CC) $(CFLAGS) -o "$@" "$<"


qset.obj : $(START_DIR)/qhull/src/libqhull/qset.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mem.obj : $(START_DIR)/qhull/src/libqhull/mem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


random.obj : $(START_DIR)/qhull/src/libqhull/random.c
	$(CC) $(CFLAGS) -o "$@" "$<"


usermem.obj : $(START_DIR)/qhull/src/libqhull/usermem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


userprintf.obj : $(START_DIR)/qhull/src/libqhull/userprintf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


io.obj : $(START_DIR)/qhull/src/libqhull/io.c
	$(CC) $(CFLAGS) -o "$@" "$<"


user.obj : $(START_DIR)/qhull/src/libqhull/user.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rboxlib.obj : $(START_DIR)/qhull/src/libqhull/rboxlib.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mwQhull.obj : $(START_DIR)/qhull/interface/mwQhull.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_data.obj : $(START_DIR)/correlatedRelease_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.obj : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.obj : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.obj : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_initialize.obj : $(START_DIR)/correlatedRelease_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_terminate.obj : $(START_DIR)/correlatedRelease_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease.obj : $(START_DIR)/correlatedRelease.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.obj : $(START_DIR)/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


find.obj : $(START_DIR)/find.c
	$(CC) $(CFLAGS) -o "$@" "$<"


convhulln.obj : $(START_DIR)/convhulln.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mergeDuplicatePoints.obj : $(START_DIR)/mergeDuplicatePoints.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortLE.obj : $(START_DIR)/sortLE.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rand.obj : $(START_DIR)/rand.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mpower.obj : $(START_DIR)/mpower.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eig.obj : $(START_DIR)/eig.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2.obj : $(START_DIR)/xnrm2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xdlapy3.obj : $(START_DIR)/xdlapy3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


recip.obj : $(START_DIR)/recip.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xdlaev2.obj : $(START_DIR)/xdlaev2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlartg.obj : $(START_DIR)/xzlartg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzladiv.obj : $(START_DIR)/xzladiv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


power.obj : $(START_DIR)/power.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rcond.obj : $(START_DIR)/rcond.c
	$(CC) $(CFLAGS) -o "$@" "$<"


schur.obj : $(START_DIR)/schur.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mpower_schur.obj : $(START_DIR)/mpower_schur.c
	$(CC) $(CFLAGS) -o "$@" "$<"


norm.obj : $(START_DIR)/norm.c
	$(CC) $(CFLAGS) -o "$@" "$<"


relop.obj : $(START_DIR)/relop.c
	$(CC) $(CFLAGS) -o "$@" "$<"


gamrnd.obj : $(START_DIR)/gamrnd.c
	$(CC) $(CFLAGS) -o "$@" "$<"


randn.obj : $(START_DIR)/randn.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar_stateful.obj : $(START_DIR)/eml_rand_mt19937ar_stateful.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sort.obj : $(START_DIR)/sort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortIdx.obj : $(START_DIR)/sortIdx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar.obj : $(START_DIR)/eml_rand_mt19937ar.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xsyheev.obj : $(START_DIR)/xsyheev.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlarfg.obj : $(START_DIR)/xzlarfg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlarf.obj : $(START_DIR)/xzlarf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgemv.obj : $(START_DIR)/xgemv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgerc.obj : $(START_DIR)/xgerc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzsteqr.obj : $(START_DIR)/xzsteqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlahqr.obj : $(START_DIR)/xzlahqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sqrt.obj : $(START_DIR)/sqrt.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xztrevc3.obj : $(START_DIR)/xztrevc3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xhseqr.obj : $(START_DIR)/xhseqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


trisolve.obj : $(START_DIR)/trisolve.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrotg.obj : $(START_DIR)/xrotg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlascl.obj : $(START_DIR)/xzlascl.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzgebal.obj : $(START_DIR)/xzgebal.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_emxutil.obj : $(START_DIR)/correlatedRelease_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_emxAPI.obj : $(START_DIR)/correlatedRelease_emxAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_rtwutil.obj : $(START_DIR)/correlatedRelease_rtwutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


