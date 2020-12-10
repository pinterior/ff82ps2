#include <conio.h>
#include <egb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char work[EgbWorkSize];

int main(int argc, char *argv[]) {
   int x, y;
   char para[16];

   int mode = 0;

   if (1 < argc) {
      mode = atoi(argv[1]);
   }
   if (mode == 0) {
      mode = 1;
   }

   EGB_init(work, sizeof(work));
   EGB_resolution(work, 0, mode);
   EGB_resolution(work, 1, mode);

   EGB_writePage(work, 0);
   EGB_color(work, 0, 15);
   for (y = 0; y < 1024; y += 16) {
      sprintf(para + 6, "%d", y);
      WORD(para)     = 0;
      WORD(para + 2) = y + 15;
      WORD(para + 4) = strlen(para + 6);
      EGB_asciiString(work, 1, para);
   }

   EGB_writePage(work, 1);
   EGB_paintMode(work, 0x20);
   EGB_color(work, 2, 1);
   for (y = 0; y < 1024; y += 16) {
      for (x = y % 32; x < 1024; x += 32) {
         WORD(para)     = x;
         WORD(para + 2) = y;
         WORD(para + 4) = x + 15;
         WORD(para + 6) = y + 15;
         EGB_rectangle(work, para);
      }
   }

   getch();

   _outb(0xff82, 0x37);
   getch();

   return 0;
}
