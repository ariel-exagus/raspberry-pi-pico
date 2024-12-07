#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "button.hpp"

#include "font6_data.hpp"
#include "font8_data.hpp"
//#include "msa301.hpp"

using namespace pimoroni;

extern unsigned char _binary_fox_tga_start[];

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

// Buttons
Button button_a(PicoExplorer::A);
Button button_b(PicoExplorer::B);
Button button_x(PicoExplorer::X);
Button button_y(PicoExplorer::Y);

int main() {
  //graphics.set_font(&font8);

  struct pt {
    float      x;
    float      y;
    uint8_t    r;
    float     dx;
    float     dy;
    uint16_t pen;
  };

  std::vector<pt> shapes;
  for(int i = 0; i < 10; i++) {
    pt shape;
    shape.x = rand() % 240;
    shape.y = rand() % 135;
    shape.r = (rand() % 10) + 3;
    shape.dx = float(rand() % 255) / 128.0f;
    shape.dy = float(rand() % 255) / 128.0f;
    shape.pen = graphics.create_pen(rand() % 255, rand() % 255, rand() % 255);
    shapes.push_back(shape);
  }

  Pen BG = graphics.create_pen(120, 40, 60);
  Pen background = BG;
  //Pen WHITE = graphics.create_pen(255, 255, 255);
  //Pen BG = graphics.create_pen(0, 0, 0);
  Pen WHITE = graphics.create_pen(255, 255, 255);
  Pen BLACK = graphics.create_pen(0,0,0);
  Pen RED = graphics.create_pen(255,0,0);
  Pen BLUE = graphics.create_pen(0,0,255);
  Pen GREEN = graphics.create_pen(0,255,0);
  Pen YELLOW = graphics.create_pen(0,255,255);
  Pen PURPLE = graphics.create_pen(255,0,255);
  Pen BOX = graphics.create_pen(55, 65, 75);

  Point text_location(0, 0);

  uint32_t i = 0;
  while(true) {
    graphics.set_pen(background);
    graphics.clear();

    for(auto &shape : shapes) {
      shape.x += shape.dx;
      shape.y += shape.dy;
      if(shape.x < 0) shape.dx *= -1;
      if(shape.x >= graphics.bounds.w) shape.dx *= -1;
      if(shape.y < 0) shape.dy *= -1;
      if(shape.y >= graphics.bounds.h) shape.dy *= -1;

      graphics.set_pen(shape.pen);
      graphics.circle(Point(shape.x, shape.y), shape.r);
    }


    if(button_a.read()) {
      graphics.set_pen(WHITE);
      graphics.character('A', Point(120, 180), 5);
      background = BG;
      text_location.x -= 1;
    }

    if(button_b.read()) {
      graphics.set_pen(WHITE);
      graphics.character('B', Point(120, 180), 5);
      background = WHITE;
      text_location.x += 1;
    }

    if(button_x.read()) {
      graphics.set_pen(WHITE);
      graphics.character('X', Point(120, 180), 5);
      background = RED;
      text_location.y -= 1;
    }

    if(button_y.read()) {
      graphics.set_pen(WHITE);
      graphics.character('Y', Point(120, 180), 5);
      background = BLUE;
      text_location.y += 1;
    }

    // float tyoff = cos(i / 20.0f) * 50.0f - 50.0f;
    // Rect text_box(10, 10, 150, 150);
    // graphics.set_pen(BOX);
    // graphics.rectangle(text_box);
    // text_box.deflate(10);
    // graphics.set_clip(text_box);
    // graphics.set_pen(WHITE);
    // graphics.text("Texto de prueba que se coloca en multiples líneas dentro del rectangulo Dibujado.", Point(text_box.x, text_box.y + tyoff), 100);

    // graphics.remove_clip();

    graphics.set_pen(BLACK);
    graphics.text("Hello World", text_location, 240);

    // graphics.set_pen(WHITE);
    // graphics.set_font(&font8);
    // graphics.text("PICO Explorer Test", Point(10, 10), 220);
    // graphics.text("Pimoroni pico Graphical project Template.", Point(10, 30), 220);

    // graphics.set_pen(PURPLE);
    // graphics.set_font(&font6);
    // graphics.text("> by Exagus", Point(10, 220), 220);
    

    // st7789.update(&graphics);


    // This can agregate a outline in the rectangle
    //WHITE = graphics.create_pen(255, 255, 255);
    // Rect box(10, 70, 100, 100);
    // box.inflate(1); // Inflate our box by 1px on all sides
    // graphics.set_pen(GREEN); // White outline
    // graphics.rectangle(box);
    // box.deflate(1); // Return to our original box size
    // graphics.set_pen(0, 0, 0); /// Black fill
    // graphics.rectangle(box);

    // Point cursor(0, 210);
    // graphics.set_pen(RED); 
    // graphics.pixel_span(cursor, 240);

    st7789.update(&graphics);
    i++;
  }

  return 0;
}