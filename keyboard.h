#ifndef __KEYBOARD_H
#define __KEYBOARD_H

void kbc_sub_int(int *hook);
void kbc_unsub_int(int *hook);
int read_kbc();

#endif
