# Proiectarea cu Microprocesoare (Microprocessor Design)

This repository contains materials, laboratory work, and projects for the "Proiectarea cu Microprocesoare" (Microprocessor Design) course. The primary focus is on **Intel 8086/8088 16-bit assembly programming** and understanding low-level computing concepts using the **MASM** (Microsoft Macro Assembler) syntax.

## Course Overview

The course covers the fundamentals of microprocessor architecture and assembly language programming, including:

- **8086 Architecture**: Registers, Flags, Memory Segmentation.
- **Assembly Language**: Instructions, Addressing Modes, Stack Operations.
- **Arithmetic & Logic**: Binary arithmetic, bitwise operations.
- **Control Flow**: Loops, Jumps, Procedures, Macros.
- **System Interactions**: DOS Interrupts (INT 21h) for I/O operations.

## Repository Structure

The repository is organized into the following main sections:

- **`Curs/`**: Contains lecture notes and theoretical materials (PDFs).
- **`Laborator/`**: Includes laboratory assignments and student solutions.
    - Organized by student name (e.g., `Paul/`, `Daria/`, `Catalin/`).
    - Contains `Materiale aditionale/` for reference code.
    - Contains `PDF/` for lab requirements and documentation (e.g., Instruction Set).
- **`Proiect/`**: Dedicated to course projects.
    - `Enunturi Proiect/`: Project requirements and specifications.
    - `Prezentari Proiect/`: Project presentations and documentation.
- **`Examen/`**: Materials related to exam preparation.

## Tools & Environment

To run and test the code in this repository, you will need an environment capable of executing 16-bit DOS applications:

- **DOSBox**: A DOS emulator widely used for running legacy 16-bit software on modern operating systems.
- **MASM/TASM**: Microsoft or Turbo Assembler for compiling `.asm` files.

### Basic Workflow (Example with MASM)

Since there is no automated build system, files are compiled individually. A typical workflow involves:

1.  **Assemble**: `masm file.asm;`
2.  **Link**: `link file.obj;`
3.  **Run**: `file.exe`
