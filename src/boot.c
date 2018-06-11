#include "ata.h"
#include "kernel_loader.h"
#include "serial.h"
#include "kprintf.h"
void goto_kernel()
{
	void (*kernel_entry)() = (void (*)())0x80001000;
	kernel_entry();
}

void boot()
{
	ata_init();
	load_kernel();
	goto_kernel();
//	test_printf();
//	test_serial();
	while (1)
		;
}