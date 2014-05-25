
BINARY = cpr

CFLAGS += -DPROCESSOR_ARCHITECTURE=PAF_X86 -DOPERATING_SYSTEM=OSF_LINUX
VPATH += base

SOURCES = \
  base.cpp \
  base_cmessage.cpp \
  base_cobject.cpp \
  base_cstring.cpp \
  base_ctime.cpp \
  base_eexception.cpp \
  \
  timer.c \
  \
  cpr.cpp \
  cpr_cfile.cpp \
  cpr_cinput.cpp \
  cpr_compressor_ccompressor.cpp \
  cpr_compressor_chuffman.cpp \
  cpr_compressor_clz77hash.cpp \
  cpr_compressor_clz77linear.cpp \
  cpr_coutput.cpp \
  main.cpp
  
include common.mk
