
RM := rm -rf
MKDIR_P := mkdir -p

OUT_OBJ := garland-sample

OUT_DIR := bin
SRC_DIR := src


O_SRCS := 
CPP_SRCS := 
C_UPPER_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
CXX_SRCS := 
C++_SRCS := 
CC_SRCS := 
OBJS := 
C++_DEPS := 
C_DEPS := 
CC_DEPS := 
CPP_DEPS := 
EXECUTABLES := 
CXX_DEPS := 
C_UPPER_DEPS := 


# All of the sources participating in the build are defined here

CPP_SRCS += \
${SRC_DIR}/Garland.cpp \
${SRC_DIR}/MainSample.cpp \
${SRC_DIR}/Request.cpp \
${SRC_DIR}/Response.cpp \
${SRC_DIR}/Route.cpp 

OBJS += \
./${OUT_DIR}/Garland.o \
./${OUT_DIR}/MainSample.o \
./${OUT_DIR}/Request.o \
./${OUT_DIR}/Response.o \
./${OUT_DIR}/Route.o 

CPP_DEPS += \
./${OUT_DIR}/Garland.d \
./${OUT_DIR}/MainSample.d \
./${OUT_DIR}/Request.d \
./${OUT_DIR}/Response.d \
./${OUT_DIR}/Route.d 


${OUT_DIR}/%.o: ${SRC_DIR}/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

	@echo 'Finished building: $<'
	@echo ' '
	
	
USER_OBJS :=
LIBS := -levent

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif


all:  directories ${OUT_OBJ}

# Tool invocations
${OUT_OBJ}: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "${OUT_OBJ}" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS) $(C++_DEPS) $(C_DEPS) $(CC_DEPS) $(CPP_DEPS) $(EXECUTABLES) \
	$(CXX_DEPS) $(C_UPPER_DEPS) ${OUT_OBJ} ${OUT_DIR}
	-@echo ' '
	
directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
	