# ALU

 - 8‑bit Arithmetic Logic Unit (ALU) using a Hardware Description Language (HDL) with a fully structural approach. The focus is on hardware modules (registers, multiplexers, arithmetic units, control unit) and their interconnections rather than behavioral descriptions.

# Supported Operations

1. Addition

2. Subtraction

3. Multiplication

4. Division

# Algorithm Choices

- Booth Radix‑4
- SRT Radix‑2

## Structural Implementation

- **Hardware Modules**
    
    - Arithmetic Unit (adder/subtractor, multiplier, divider)
        
    - Control Unit (generates control signals C0…C13)
        
    - Registers 
        
    - Multiplexers & Tri‑states 
        
- **Design Style**
    
    - Structural HDL: instantiate and interconnect modules explicitly
        
    - Minimal behavioral code (only where unavoidable)
        

## Control Unit
