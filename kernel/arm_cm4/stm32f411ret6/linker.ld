ENTRY("entry")

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (rw) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    . = ORIGIN(FLASH);

    .vector_table : 
    {
        KEEP(build/mcu/stm32f411ret6/entry.o(.text))
    } > FLASH

    .syscall_table 0x08000198: 
    {
        build/kernel/syscalls.o(.text)
    } > FLASH

    .text : 
    {
        *(.text*)
    } > FLASH

    .rodata : 
    {
        *(.rodata*)
    } > FLASH

    . = ORIGIN(RAM);
    .bss : 
    {
        __bss_start = .;
        *(.bss*)
        __bss_end = .;
    } > RAM
}
