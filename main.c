#include "util.h"
#include "KeyDef.h"

uint8_t key, prev, i;
bit brust = 0;

void main() {
	portInit();
	timerInit();
	serialInit();
	endInit();
	
	write("NSDN-Keypad v1.1\n");
	
	while (1) {
		key = scanKey();
		if (key != 0xFF) {
			if (key == prev && !brust) {
				for (i = 0; i < 10; i++) {
					delay(2);
					key = scanKey();
					if (key != prev) goto END;
				}
				brust = 1;
				END:
				_nop_();
			}
			prev = key;
			if (key != 0xFF) send(key);
			key = 0xFF;
			delay(2);
		} else {
			brust = 0;
			prev = 0;
		}
	}
}