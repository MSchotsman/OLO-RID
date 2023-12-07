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
START_DIR                 =  ~/CforThesis/include/PIM
CMD_FILE                  = correlatedRelease_rtw_linux.rsp
C_STANDARD_OPTS           = -fwrapv
MODELLIB                  = correlatedRelease.a
SHELL                 	  = /bin/sh

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
                       -Wl,--out-implib,$(notdir $(basename $(PRODUCT))).a



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./correlatedRelease.a
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

OBJS = global.o stat.o geom2.o poly2.o merge.o libqhull.o geom.o poly.o qset.o mem.o random.o usermem.o userprintf.o io.o user.o rboxlib.o mwQhull.o correlatedRelease_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o correlatedRelease_initialize.o correlatedRelease_terminate.o correlatedRelease.o minOrMax.o find.o convhulln.o mergeDuplicatePoints.o sortLE.o rand.o mpower.o eig.o xnrm2.o xdlapy3.o recip.o xdlaev2.o xzlartg.o xzladiv.o power.o rcond.o schur.o mpower_schur.o norm.o relop.o gamrnd.o randn.o eml_rand_mt19937ar_stateful.o sort.o sortIdx.o eml_rand_mt19937ar.o xsyheev.o xzlarfg.o xzlarf.o xgemv.o xgerc.o xzsteqr.o xzlahqr.o sqrt.o xztrevc3.o xhseqr.o trisolve.o xrotg.o xzlascl.o xzgebal.o correlatedRelease_emxutil.o correlatedRelease_emxAPI.o correlatedRelease_rtwutil.o

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

global.o : $(START_DIR)/qhull/src/libqhull/global.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stat.o : $(START_DIR)/qhull/src/libqhull/stat.c
	$(CC) $(CFLAGS) -o "$@" "$<"


geom2.o : $(START_DIR)/qhull/src/libqhull/geom2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


poly2.o : $(START_DIR)/qhull/src/libqhull/poly2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


merge.o : $(START_DIR)/qhull/src/libqhull/merge.c
	$(CC) $(CFLAGS) -o "$@" "$<"


libqhull.o : $(START_DIR)/qhull/src/libqhull/libqhull.c
	$(CC) $(CFLAGS) -o "$@" "$<"


geom.o : $(START_DIR)/qhull/src/libqhull/geom.c
	$(CC) $(CFLAGS) -o "$@" "$<"


poly.o : $(START_DIR)/qhull/src/libqhull/poly.c
	$(CC) $(CFLAGS) -o "$@" "$<"


qset.o : $(START_DIR)/qhull/src/libqhull/qset.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mem.o : $(START_DIR)/qhull/src/libqhull/mem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


random.o : $(START_DIR)/qhull/src/libqhull/random.c
	$(CC) $(CFLAGS) -o "$@" "$<"


usermem.o : $(START_DIR)/qhull/src/libqhull/usermem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


userprintf.o : $(START_DIR)/qhull/src/libqhull/userprintf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


io.o : $(START_DIR)/qhull/src/libqhull/io.c
	$(CC) $(CFLAGS) -o "$@" "$<"


user.o : $(START_DIR)/qhull/src/libqhull/user.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rboxlib.o : $(START_DIR)/qhull/src/libqhull/rboxlib.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mwQhull.o : $(START_DIR)/qhull/interface/mwQhull.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_data.o : $(START_DIR)/correlatedRelease_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_initialize.o : $(START_DIR)/correlatedRelease_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_terminate.o : $(START_DIR)/correlatedRelease_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease.o : $(START_DIR)/correlatedRelease.c
	$(CC) $(CFLAGS) -o "$@" "$<"


minOrMax.o : $(START_DIR)/minOrMax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


find.o : $(START_DIR)/find.c
	$(CC) $(CFLAGS) -o "$@" "$<"


convhulln.o : $(START_DIR)/convhulln.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mergeDuplicatePoints.o : $(START_DIR)/mergeDuplicatePoints.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortLE.o : $(START_DIR)/sortLE.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rand.o : $(START_DIR)/rand.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mpower.o : $(START_DIR)/mpower.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eig.o : $(START_DIR)/eig.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2.o : $(START_DIR)/xnrm2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xdlapy3.o : $(START_DIR)/xdlapy3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


recip.o : $(START_DIR)/recip.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xdlaev2.o : $(START_DIR)/xdlaev2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlartg.o : $(START_DIR)/xzlartg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzladiv.o : $(START_DIR)/xzladiv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


power.o : $(START_DIR)/power.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rcond.o : $(START_DIR)/rcond.c
	$(CC) $(CFLAGS) -o "$@" "$<"


schur.o : $(START_DIR)/schur.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mpower_schur.o : $(START_DIR)/mpower_schur.c
	$(CC) $(CFLAGS) -o "$@" "$<"


norm.o : $(START_DIR)/norm.c
	$(CC) $(CFLAGS) -o "$@" "$<"


relop.o : $(START_DIR)/relop.c
	$(CC) $(CFLAGS) -o "$@" "$<"


gamrnd.o : $(START_DIR)/gamrnd.c
	$(CC) $(CFLAGS) -o "$@" "$<"


randn.o : $(START_DIR)/randn.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar_stateful.o : $(START_DIR)/eml_rand_mt19937ar_stateful.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sort.o : $(START_DIR)/sort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortIdx.o : $(START_DIR)/sortIdx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eml_rand_mt19937ar.o : $(START_DIR)/eml_rand_mt19937ar.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xsyheev.o : $(START_DIR)/xsyheev.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlarfg.o : $(START_DIR)/xzlarfg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlarf.o : $(START_DIR)/xzlarf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgemv.o : $(START_DIR)/xgemv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgerc.o : $(START_DIR)/xgerc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzsteqr.o : $(START_DIR)/xzsteqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlahqr.o : $(START_DIR)/xzlahqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sqrt.o : $(START_DIR)/sqrt.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xztrevc3.o : $(START_DIR)/xztrevc3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xhseqr.o : $(START_DIR)/xhseqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


trisolve.o : $(START_DIR)/trisolve.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrotg.o : $(START_DIR)/xrotg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlascl.o : $(START_DIR)/xzlascl.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzgebal.o : $(START_DIR)/xzgebal.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_emxutil.o : $(START_DIR)/correlatedRelease_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_emxAPI.o : $(START_DIR)/correlatedRelease_emxAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


correlatedRelease_rtwutil.o : $(START_DIR)/correlatedRelease_rtwutil.c
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


