/*
                  Linker File for S3A3 MCU
*/

/* Linker script to configure memory regions. */
MEMORY
{
  FLASH (rx)         : ORIGIN = 0x00000000, LENGTH = 0x100000   /* Vtable @0000000, Swap test uses 1st 16K, Vtable is saved and restored in test. */
  RAM (rwx)          : ORIGIN = 0x20000000, LENGTH = 0x0018000  /* 96K */
  DATA_FLASH (rx)    : ORIGIN = 0x40100000, LENGTH = 0x0002000  /*  8K */
  QSPI_FLASH (rx)    : ORIGIN = 0x60000000, LENGTH = 0x4000000  /*  64M, Change in QSPI section below also */
  
  ID_CODE_1 (rx)      : ORIGIN = 0x01010018, LENGTH = 0x04      /* 4 bytes */    
  ID_CODE_2 (rx)      : ORIGIN = 0x01010020, LENGTH = 0x04      /* 4 bytes */    
  ID_CODE_3 (rx)      : ORIGIN = 0x01010028, LENGTH = 0x04      /* 4 bytes */    
  ID_CODE_4 (rx)      : ORIGIN = 0x01010030, LENGTH = 0x04      /* 4 bytes */ 
}

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 *   __qspi_flash_start__
 *   __qspi_flash_end__
 *   __qspi_flash_code_size__
 *   __qspi_region_max_size__
 *   __qspi_region_start_address__
 *   __qspi_region_end_address__
 */
ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		__ROM_Start = .;

        /* Even though the vector table is not 256 entries (1KB) long, we still allocate that much
         * space because ROM registers are at address 0x400 and there is very little space
         * in between. */
		KEEP(*(.vectors))
		KEEP(*(SORT_BY_NAME(.vector.*)))
		__Vectors_End = .;
		__end__ = .;

		/* ROM Registers start at address 0x00000400 */
		. = __ROM_Start + 0x400;
		KEEP(*(.rom_registers*))

		/* Reserving 0x100 bytes of space for ROM registers. */
		. = __ROM_Start + 0x4000;

		/* Vector information array. */
		__Vector_Info_Start = .;
		KEEP(*(SORT_BY_NAME(.vector_info.*)))
		__Vector_Info_End = .;

		/* Hardware lock lookup array. */
		__Lock_Lookup_Start = .;
		KEEP(*(SORT_BY_NAME(.hw_lock_lookup.*)))
		__Lock_Lookup_End = .;

		*(.text*)

		KEEP(*(.version))
		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
 		*crtbegin.o(.dtors)
 		*crtbegin?.o(.dtors)
 		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
 		*(SORT(.dtors.*))
 		*(.dtors)

		*(.rodata*)

		KEEP(*(.eh_frame*))

		__ROM_End = .;
	} > FLASH = 0xFF

    __Vector_Info_Size = __Vector_Info_End - __Vector_Info_Start;
    __Lock_Lookup_Size = __Lock_Lookup_End - __Lock_Lookup_Start;

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	/* To copy multiple ROM to RAM sections,
	 * uncomment .copy.table section and,
	 * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
	/*
	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		LONG (__etext2)
		LONG (__data2_start__)
		LONG (__data2_end__ - __data2_start__)
		__copy_table_end__ = .;
	} > FLASH
	*/

	/* To clear multiple BSS sections,
	 * uncomment .zero.table section and,
	 * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
	/*
	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
		LONG (__bss2_start__)
		LONG (__bss2_end__ - __bss2_start__)
		__zero_table_end__ = .;
	} > FLASH
	*/

	__etext = .;

    __Vectors_Size = __Vectors_End - __Vectors;

	/* Initialized data section. */
	.data : AT (__etext)
	{
		__data_start__ = .;
		*(vtable)
		*(.data*)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		KEEP(*(.jcr*))
		. = ALIGN(4);

		__Code_In_RAM_Start = .;

		KEEP(*(.code_in_ram*))
		__Code_In_RAM_End = .;

		/* Hardware look array. */
		__Lock_Start = .;
		KEEP(*(SORT_BY_NAME(.hw_lock*)))
		__Lock_End = .;

		/* All data end */
		__data_end__ = .;

	} > RAM

    __Lock_Size = __Lock_End - __Lock_Start;

    /* QSPI_FLASH Retentive section */
	.qspi_retentive (NOLOAD):
    {
        __qspi_retentive_start__ = .;
        KEEP(*(.qspi_retentive*))
        __qspi_retentive_end__ = .;
    } > QSPI_FLASH
	__qspi_retentive_size__ = __qspi_retentive_end__ - __qspi_retentive_start__;

    /* QSPI_FLASH Non-retentive section */
    __qspi_flash_code_addr__ = __etext + (__data_end__ - __data_start__);
    .qspi_flash : /* AT (__qspi_flash_code_addr__) uncomment to copy internal flash to QSPI flash */
    {
        __qspi_flash_start__ = .;
        KEEP(*(.qspi_flash*))
        __qspi_flash_end__ = .;
    } > QSPI_FLASH

    __qspi_flash_code_size__ = __qspi_flash_end__ - __qspi_flash_start__;
    __qspi_region_max_size__ = 0x4000000;   /* Must be the same as defined in MEMORY above */
    __qspi_region_start_address__ = __qspi_flash_start__;
    __qspi_region_end_address__ = __qspi_flash_start__ + __qspi_region_max_size__;

    .noinit (NOLOAD):
    {
		. = ALIGN(4);
        __noinit_start = .;
        KEEP(*(.noinit*))
        __noinit_end = .;
    } > RAM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	.heap (NOLOAD):
	{
		. = ALIGN(8);
		__HeapBase = .;
		__end__ = .;
		end = __end__;
		KEEP(*(.heap*))
		__HeapLimit = .;
	} > RAM

    /* Stacks are stored in this section. */
    .stack_dummy (NOLOAD):
    {
        . = ALIGN(8);
        __StackLimit = .;
        /* Main stack */
        KEEP(*(.stack))
        __StackTop = .;
        /* Thread stacks */
        KEEP(*(.stack*))
        __StackTopAll = .;
    } > RAM

    PROVIDE(__stack = __StackTopAll);

    /* This symbol represents the end of user allocated RAM. The RAM after this symbol can be used
       at run time for things such as ThreadX memory pool allocations. */
    __RAM_segment_used_end__ = ALIGN(__StackTopAll , 4);

	/* Data flash. */
	.dflash :
	{
		__Data_Flash_Start = .;
		KEEP(*(.dflash*))
		__Data_Flash_End = .;
	} > DATA_FLASH
	
	.id_code_1 :
    {
        __ID_Code_1_Start = .;
        KEEP(*(.id_code_1*))
        __ID_Code_1_End = .;
    } > ID_CODE_1

    .id_code_2 :
    {
        __ID_Code_2_Start = .;
        KEEP(*(.id_code_2*))
        __ID_Code_2_End = .;
    } > ID_CODE_2
    
    .id_code_3 :
    {
        __ID_Code_3_Start = .;
        KEEP(*(.id_code_3*))
        __ID_Code_3_End = .;
    } > ID_CODE_3

    .id_code_4 :
    {
        __ID_Code_4_Start = .;
        KEEP(*(.id_code_4*))
        __ID_Code_4_End = .;
    } > ID_CODE_4
}
