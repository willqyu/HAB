# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico\build"

# Utility rule file for bs2_default_padded_checksummed_asm.

# Include the progress variables for this target.
include pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\progress.make

pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm: pico_sdk\src\rp2_common\boot_stage2\bs2_default_padded_checksummed.S
	cd C:\Users\thera\ONEDRI~1\Balloon\Code\Pico\build\pico_sdk\src\RP2_CO~1\BOOT_S~1
	cd C:\Users\thera\ONEDRI~1\Balloon\Code\Pico\build

pico_sdk\src\rp2_common\boot_stage2\bs2_default_padded_checksummed.S:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating bs2_default_padded_checksummed.S"
	cd C:\Users\thera\ONEDRI~1\Balloon\Code\Pico\build\pico_sdk\src\RP2_CO~1\BOOT_S~1
	C:\Users\thera\AppData\Local\Programs\Python\Python37\python.exe C:/Users/thera/Documents/pico-sdk/src/rp2_common/boot_stage2/pad_checksum -s 0xffffffff "C:/Users/thera/OneDrive - Westminster School/Balloon/Code/Pico/build/pico_sdk/src/rp2_common/boot_stage2/bs2_default.bin" "C:/Users/thera/OneDrive - Westminster School/Balloon/Code/Pico/build/pico_sdk/src/rp2_common/boot_stage2/bs2_default_padded_checksummed.S"
	cd C:\Users\thera\ONEDRI~1\Balloon\Code\Pico\build

bs2_default_padded_checksummed_asm: pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm
bs2_default_padded_checksummed_asm: pico_sdk\src\rp2_common\boot_stage2\bs2_default_padded_checksummed.S
bs2_default_padded_checksummed_asm: pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\build.make

.PHONY : bs2_default_padded_checksummed_asm

# Rule to build all files generated by this target.
pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\build: bs2_default_padded_checksummed_asm

.PHONY : pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\build

pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\clean:
	cd C:\Users\thera\ONEDRI~1\Balloon\Code\Pico\build\pico_sdk\src\RP2_CO~1\BOOT_S~1
	$(CMAKE_COMMAND) -P CMakeFiles\bs2_default_padded_checksummed_asm.dir\cmake_clean.cmake
	cd C:\Users\thera\ONEDRI~1\Balloon\Code\Pico\build
.PHONY : pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\clean

pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico" C:\Users\thera\Documents\pico-sdk\src\rp2_common\boot_stage2 "C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico\build" "C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico\build\pico_sdk\src\rp2_common\boot_stage2" "C:\Users\thera\OneDrive - Westminster School\Balloon\Code\Pico\build\pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : pico_sdk\src\rp2_common\boot_stage2\CMakeFiles\bs2_default_padded_checksummed_asm.dir\depend
