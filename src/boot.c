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
	kprintf("[BootLoader] Init ATA driver...\n");
	ata_init();
	kprintf("[BootLoader] ATA Init Done.\n");
	kprintf("[BootLoader] Loading kernel...\n");
	load_kernel();
	kprintf("[BootLoader] Kernel loaded.\n");
	kprintf("[BootLoader] Jump to kernel.\n");
	goto_kernel();
	while (1)
		;
}
