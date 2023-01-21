#include <M5Unified.h>

uint16_t FORE_COLOR = TFT_BLACK;
uint16_t BACK_COLOR = TFT_WHITE;
boolean happy = false;

void setup()
{
  auto cfg = M5.config();
  cfg.internal_mic = false;
  M5.begin(cfg);

  uint8_t display_rotation = 0; // ディスプレイの向き(0〜3)

  M5.Display.setRotation(display_rotation);
  drawSadMac(FORE_COLOR, BACK_COLOR);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed()) {
    happy = !happy;
    if(happy){
      drawHappyMac(FORE_COLOR, BACK_COLOR);
    }else{
      drawSadMac(FORE_COLOR, BACK_COLOR);
    }
  }
}

void drawSadMac(uint16_t FORE_COLOR, uint16_t BACK_COLOR){
  int x_offset;
  uint32_t COLOR_PRIMARY = M5.Display.color16to24(FORE_COLOR);
  uint32_t COLOR_BACKGROUND = M5.Display.color16to24(BACK_COLOR);

  M5.Display.fillScreen(COLOR_BACKGROUND);
  // Right Eye
  x_offset = 0;
  M5.Display.fillRect(24 + x_offset, 31, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(39 + x_offset, 31, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(31 + x_offset, 39, 8, 7, COLOR_PRIMARY);
  M5.Display.fillRect(24 + x_offset, 46, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(39 + x_offset, 46, 7, 8, COLOR_PRIMARY);

  // Left Eye
  x_offset = 60;
  M5.Display.fillRect(24 + x_offset, 31, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(39 + x_offset, 31, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(31 + x_offset, 39, 8, 7, COLOR_PRIMARY);
  M5.Display.fillRect(24 + x_offset, 46, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(39 + x_offset, 46, 7, 8, COLOR_PRIMARY);

  // Nose
  M5.Display.fillRect(46, 61, 8, 8, COLOR_PRIMARY);
  M5.Display.fillRect(54, 69, 15, 7, COLOR_PRIMARY);
  M5.Display.fillRect(69, 61, 7, 8, COLOR_PRIMARY);

  // Mouse
  M5.Display.fillRect(39, 91, 7, 8, COLOR_PRIMARY);
  M5.Display.fillRect(46, 84, 38, 7, COLOR_PRIMARY);
  M5.Display.fillRect(84, 91, 15, 8, COLOR_PRIMARY);
  M5.Display.fillRect(99, 99, 7, 7, COLOR_PRIMARY);
}

void drawHappyMac(uint16_t FORE_COLOR, uint16_t BACK_COLOR){
  int x_offset;
  uint32_t COLOR_PRIMARY = M5.Display.color16to24(FORE_COLOR);
  uint32_t COLOR_BACKGROUND = M5.Display.color16to24(BACK_COLOR);

  M5.Display.fillScreen(COLOR_BACKGROUND);
  // Right Eye
  x_offset = 0;
  M5.Display.fillRect(31 + x_offset, 34, 8, 16, COLOR_PRIMARY);

  // Left Eye
  x_offset = 53;
  M5.Display.fillRect(31 + x_offset, 34, 8, 16, COLOR_PRIMARY);

  // Nose
  M5.Display.fillRect(61, 34, 8, 46, COLOR_PRIMARY);
  M5.Display.fillRect(53, 72, 8, 8, COLOR_PRIMARY);

  // Mouse
  M5.Display.fillRect(38, 86, 8, 8, COLOR_PRIMARY);
  M5.Display.fillRect(46, 94, 31, 8, COLOR_PRIMARY);
  M5.Display.fillRect(77, 86, 8, 8, COLOR_PRIMARY);
}
