#include "../../../includes/definitions.h"

void set_pixel(int x, int y, uint8_t color) {
  uint16_t offset = y * VGA_WIDTH + x;
  *(volatile uint8_t *)(VGA_ADDRESS + offset) = color;
} // setpixles on screen
__attribute__((used))
void initialize_kernel()
{
  int x,y =0,0;
  while(1)
  {
    set_pixel(x,y,0xF);
    if (x>=VGA_WIDTH)
    {
      x =0;
      y++;
    }
    if(y>=VGA_HEIGHT)
    {
      y=0;
    }
}
