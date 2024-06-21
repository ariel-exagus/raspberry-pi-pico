#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

#include "font6_data.hpp"
#include "font8_data.hpp"
//#include "msa301.hpp"

using namespace pimoroni;

extern unsigned char _binary_fox_tga_start[];

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);


int main() {
  graphics.set_font(&font8);

  //Pen BG = graphics.create_pen(120, 40, 60);
  //Pen WHITE = graphics.create_pen(255, 255, 255);
  Pen BG = graphics.create_pen(0, 0, 0);
  Pen WHITE = graphics.create_pen(255, 255, 255);

  uint32_t i = 0;
  while(true) {
    graphics.set_pen(BG);
    graphics.clear();

    graphics.set_pen(WHITE);
    graphics.set_font(&font8);
    graphics.text("PICO Explorer Test", Point(10, 10), 220);
    graphics.text("Pimoroni pico Graphical project Template.", Point(10, 30), 220);

    graphics.set_font(&font6);
    graphics.text("> by Exagus", Point(10, 220), 220);
    

    st7789.update(&graphics);

    i++;
  }

  return 0;
}