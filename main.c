#include "util.h"
#include "KeyDef.h"

uint8_t key, prev, i;
bit brust = 0;

void main() {
	portInit();
	serialInit();
	
	write("NSDN-Keypad v1.0\n");
	
	while (1) {
		key = (char)scanKey();
		if (key == KeyCL) {
			while (key == KeyCL)
				key = (char)scanKey();
			if (Ctrl) {
				CapsLock = ~CapsLock;
				CLPOS = CapsLock;
				Ctrl = 0;
			} else Caps = 1;
		} else if (key == KeyCt) {
			while (key == KeyCt)
				key = (char)scanKey();
			Ctrl = 1;
			//send(KeyCt);
		} else if (key == KeyAl) {
			while (key == KeyAl)
				key = (char)scanKey();
			Alt = 1;
			//send(KeyAl);
		} else if (key == KeyEsc) {
			while (key == KeyEsc)
				key = (char)scanKey();
			//send(KeyEsc);
		} else if (key != 0xFF) {
			if (key == prev && !brust) {
				for (i = 0; i < 10; i++) {
					delay(2);
					key = (char)scanKey();
					if (key != prev) goto END;
				}
				brust = 1;
				END:
				_nop_();
			}
			prev = key;
			if (key >= 'A' && key <= 'Z' && !CapsLock && !Caps) key += 32;
			if (key != 0xFF) send(key);
			key = 0xFF;
			delay(2);
			Ctrl = 0; Alt = 0; Caps = 0;
		} else {
			brust = 0;
			prev = 0;
		}
	}
}