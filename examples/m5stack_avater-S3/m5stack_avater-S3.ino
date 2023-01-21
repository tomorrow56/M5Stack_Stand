#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

Avatar avatar;
ColorPalette *cps[6];
uint8_t palette_index = 0;

uint32_t last_rotation_msec = 0;

void setup()
{
  auto cfg = M5.config();
  cfg.internal_mic = false;
  M5.begin(cfg);

  // for M5AtomS3
  uint8_t first_cps = 4;
  float scale = 0.5f;
  int8_t position_x = 5;
  int8_t position_y = -15;
  uint8_t display_rotation = 0; // ディスプレイの向き(0〜3)

  M5.Lcd.setRotation(display_rotation);
  avatar.setScale(scale);
  avatar.setPosition(position_x, position_y);
  avatar.init(); // start drawing

  cps[0] = new ColorPalette();
  cps[0]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[0]->set(COLOR_BACKGROUND, TFT_YELLOW);
  cps[1] = new ColorPalette();
  cps[1]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[1]->set(COLOR_BACKGROUND, TFT_ORANGE);
  cps[2] = new ColorPalette();
  cps[2]->set(COLOR_PRIMARY, (uint16_t)0x00ff00);
  cps[2]->set(COLOR_BACKGROUND, (uint16_t)0x303303);
  cps[3] = new ColorPalette();
  cps[3]->set(COLOR_PRIMARY, TFT_WHITE);
  cps[3]->set(COLOR_BACKGROUND, TFT_BLACK);
  cps[4] = new ColorPalette();
  cps[4]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[4]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[5] = new ColorPalette();
  cps[5]->set(COLOR_PRIMARY, 0x303303);
  cps[5]->set(COLOR_BACKGROUND, 0x00ff00);
  avatar.setColorPalette(*cps[first_cps]);

  last_rotation_msec = millis();
}

uint32_t count = 0;
int interval = 1;

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed()) {
    palette_index++;
    if (palette_index > 5) {
      palette_index = 0;
    }
    avatar.setColorPalette(*cps[palette_index]);
  }

  if ((millis() - last_rotation_msec) > interval * 100) {
    interval = random(0, 10);
    float angle = 2 * sin(count);
    avatar.setRotation(angle);
    last_rotation_msec = millis();
    count++;
  }
}
