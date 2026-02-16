include ../../py/mkenv.mk

CROSS = 1

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

# include py core make definitions
include $(TOP)/py/py.mk

CROSS_COMPILE ?= riscv64-unknown-elf-

LLVM_BIN := $(STABLE_LIB)/rustlib/x86_64-unknown-linux-gnu/bin
LIBC_DIR := /usr/lib/picolibc/riscv64-unknown-elf/lib/release/rv32imac/ilp32

INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)
INC += -I/usr/lib/picolibc/riscv64-unknown-elf/include

CFLAGS += $(INC) -Wall -Werror -std=c99 -nostdlib $(COPT)
CFLAGS += -march=rv32imac -mabi=ilp32

# Flags for optional C++ source code
CXXFLAGS += $(filter-out -std=c99,$(CFLAGS))

LIBS = baochip-sdk/target/riscv32imac-unknown-none-elf/release/libbaochip_sdk.a
LIBS += $(LIBC_DIR)/libc.a

SRC_C = \
	main.c \
	uart_core.c \
	shared/libc/printf.c \
	shared/readline/readline.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \
	$(BUILD)/_frozen_mpy.c \

SRC_C += shared/libc/string0.c

SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

OBJ += $(PY_CORE_O)
OBJ += $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_CXX:.cpp=.o))

all: $(BUILD)/firmware.uf2

$(BUILD)/_frozen_mpy.c: $(TOP)/tests/frozen/frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@

# This uses riscv64-unknown-elf-gcc because riscv64-unknown-elf-ld doesn't work
$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) '---'
	$(ECHO) "LINK $@"
	$(Q)riscv64-unknown-elf-gcc \
		-march=rv32imac -mabi=ilp32 -nostartfiles -nostdlib \
		-Tbaochip-sdk/link.x \
		-Wl,--gc-sections \
		-o $@ $^ $(LIBS)

$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	$(ECHO) '---'
	$(ECHO) 'Extracting loadable sections to firmware.bin:'
	$(Q)$(OBJCOPY) -O binary $^ $(BUILD)/firmware.bin
	$(ECHO) '---'
	$(ECHO) 'Checking firmware.bin sections:'
	$(Q)riscv64-unknown-elf-objdump -h $^

$(BUILD)/firmware.uf2: $(BUILD)/firmware.bin
	@echo '---'
	@echo "Signing firmware.bin as firmware.img:"
	@python3 baochip-sdk/signer.py $^ $(BUILD)/firmware.img
	@echo '---'
	@echo "Packing firmware.img as $@:"
	@python3 baochip-sdk/uf2ify.py $(BUILD)/firmware.img $@

baochip-sdk/target/riscv32imac-unknown-none-elf/release/libbaochip_sdk.a:
	make -C baochip-sdk release

include $(TOP)/py/mkrules.mk
