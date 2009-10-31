/*
 * EB platform-specific initialisation and setup
 *
 * Copyright (C) 2007 Bahadir Balban
 */

#include <l4/generic/platform.h>
#include <l4/generic/space.h>
#include <l4/generic/irq.h>
#include INC_ARCH(linker.h)
#include INC_PLAT(printascii.h)
#include INC_SUBARCH(mm.h)
#include INC_SUBARCH(mmu_ops.h)
#include INC_GLUE(memory.h)
#include INC_GLUE(memlayout.h)
#include INC_PLAT(offsets.h)
#include INC_PLAT(platform.h)
#include INC_PLAT(uart.h)
#include INC_PLAT(irq.h)
#include INC_ARCH(asm.h)

void init_platform_console(void)
{
	add_boot_mapping(EB_UART0_BASE, PLATFORM_CONSOLE0_BASE, PAGE_SIZE,
		    MAP_IO_DEFAULT_FLAGS);

	/*
	 * Map same UART IO area to userspace so that primitive uart-based
	 * userspace printf can work. Note, this raw mapping is to be
	 * removed in the future, when file-based io is implemented.
	 */
	add_boot_mapping(EB_UART0_BASE, USERSPACE_UART_BASE, PAGE_SIZE,
		    MAP_USR_IO_FLAGS);

	uart_init();
}

void init_platform_timer(void)
{
	add_boot_mapping(EB_TIMER01_BASE, PLATFORM_TIMER0_BASE, PAGE_SIZE,
		    MAP_IO_DEFAULT_FLAGS);
	add_boot_mapping(EB_SYSCTRL_BASE, EB_SYSCTRL_VBASE, PAGE_SIZE,
		    MAP_IO_DEFAULT_FLAGS);
	timer_init();
}

void init_platform_irq_controller()
{
#if 0
	add_boot_mapping(PB926_VIC_BASE, PLATFORM_IRQCTRL_BASE, PAGE_SIZE,
		    MAP_IO_DEFAULT_FLAGS);
	add_boot_mapping(PB926_SIC_BASE, PLATFORM_SIRQCTRL_BASE, PAGE_SIZE,
		    MAP_IO_DEFAULT_FLAGS);
	irq_controllers_init();
#endif
}

void platform_init(void)
{
	init_platform_console();
	init_platform_timer();
	init_platform_irq_controller();
}

