ENTRY(entry)

flash = 0x08000000;
ram = 0x20000000;

SECTIONS
{
    . = flash;

    .text               : {build/mcu/stm32f411ret6/entry.o(.text) *(.text)}
    .rodata             : {*(.rodata)}
    
    . = ram;
    .bss                : 
    {
        __bss_start = .;
        *(.bss)
        __bss_end = .;
    }
}