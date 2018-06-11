#include "kprintf.h"
#include "serial.h"

int kputchar(int ch)
{
	if(ch == '\n')
		write_serial('\r');
	write_serial(ch);
	return ch;
}

int kputs(const char *s)
{
	int ret = 0;
	while (*s) {
		ret++;
		kputchar(*s++);
	}
	return ret;
}

int kputint(int x, int try_scan_num)
{
	char buffer[12];
	char *ptr = buffer + 11;
	int neg = 0;
	int digit_count = 0;
	buffer[11] = 0;
	if (x == 0) {
		kputchar('0');
		return x;
	}
	if (x < 0) {
		neg = 1;
		x = -x;
	}
	while (x) {
		ptr--;
		*ptr = (x % 10) + '0';
		x /= 10;
		digit_count++;
	}
	if (neg) {
		ptr--;
		*ptr = '-';
		digit_count++; /*also see it as a digit, to control the width*/
	}
	/*padding*/
	while (digit_count < try_scan_num) {
		ptr--;
		*ptr = ' ';
		digit_count++; /*also see it as a digit, to control the width*/
	}
	
	kputs(ptr);
	return x;
}

int kputintx(unsigned int x, int try_scan_num)
{
	char HEX_MAP[] = "0123456789abcdef";
	char buffer[12];
	char *ptr = buffer + 11;
	int digit_count = 0;
	buffer[11] = 0;
	if (x == 0) {
		kputchar('0');
		return x;
	}
	while (x) {
		ptr--;
		*ptr = HEX_MAP[x & 15];
		x >>= 4;
	}
	
	/*padding*/
	while (digit_count < try_scan_num) {
		ptr--;
		*ptr = ' ';
		digit_count++; /*also see it as a digit, to control the width*/
	}
	kputs(ptr);
	return x;
}


int kputinto(unsigned int x, int try_scan_num)
{
	char HEX_MAP[] = "012345678";
	char buffer[12];
	char *ptr = buffer + 11;
	int digit_count = 0;
	buffer[11] = 0;
	if (x == 0) {
		kputchar('0');
		return x;
	}
	while (x) {
		ptr--;
		*ptr = HEX_MAP[x & 7];
		x >>= 3;
	}
	
	/*padding*/
	while (digit_count < try_scan_num) {
		ptr--;
		*ptr = ' ';
		digit_count++; /*also see it as a digit, to control the width*/
	}
	kputs(ptr);
	return x;
}

const int ERROR_SCAN_NUM_FROM_STR = -1;
static int try_scan_num_from_str(const char **format_ptr) /*return -1 or number */
{
	
	char current_char = **format_ptr;
	int sum = 0;
	int bool_succeed = 0;
	while (1) {
		if (current_char >= '0' && current_char <= '9') /*is a number*/
		{
			sum = sum * 10 + (current_char - '0');
			bool_succeed = 1;
			(*format_ptr)++;
			current_char = **format_ptr;
		} else {
			/*not a number now*/
			if (bool_succeed != 1) {
				/* fail to get a number */
				return ERROR_SCAN_NUM_FROM_STR; /*error*/
			} else {
				/* succeed in geting a number */
				return sum;
			}
		}
	}
}
int kvprintf(const char *format, va_list ap)
{
	int cnt = 0;
	while (*format) {
		if (*format != '%') {
			kputchar(*format++);
		} else {
			format++; /* skip '%' */
			int try_scan_num = try_scan_num_from_str(&format);
			
			
			switch (*format) {
			case 'c': {
				char valch = va_arg(ap, int);
				kputchar(valch);
				format++;
				cnt++;
				break;
			}
			case 'd': {
				int valint = va_arg(ap, int);
				kputint(valint, try_scan_num);
				format++;
				cnt++;
				break;
			}
			case 'x': {
				int valint = va_arg(ap, int);
				kputintx(valint, try_scan_num);
				format++;
				cnt++;
				break;
			}
			case 'o': {
				int valint = va_arg(ap, int);
				kputinto(valint, try_scan_num);
				format++;
				cnt++;
				break;
			}
			
			case 's': {
				char *valstr = va_arg(ap, char *);
				kputs(valstr);
				format++;
				cnt++;
				break;
			}
			
			default: {
				
				/*error*/
				cnt = -1;
				goto exit;
			}
			}
		}
	}
	exit:
	return cnt;
}

int kprintf(const char *format, ...)
{
	int cnt = 0;
	va_list ap;
	va_start(ap, format);
	cnt = kvprintf(format, ap);
	va_end(ap);
	return cnt;
}

int test_printf()
{
	int test_num_int = 2018;
	char c = 'a';
	kprintf("Hello%8o \t %d \t %x %c return\n num:888\n", test_num_int, test_num_int, test_num_int, 'a');
	int i = 0;
	while (i++ < 1) {
		kprintf("01: On that bold hill, against a broad blue stream,\n");
		kprintf("02: stood Arthur Phillip on a day of dream;\n");
		kprintf("03: what time the mists of morning westward rolled\n");
		kprintf("04: and heaven flowered on a bay of gold.\n");
		kprintf("05: Here, in the hour that shines and sounds afar,\n");
		kprintf("06: flamed first Old England's banner like a star;\n");
		kprintf("07: Here in a time august with prayer and praise,\n");
		kprintf("08: was born the nation of these splendid days,\n");
		kprintf("09: and here, this land's majestic yesterday\n");
		kprintf("10: of immemorial silence died away \n");
		int count_down = 100000000;
		while (count_down--)
			;
	}
}