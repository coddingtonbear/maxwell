#include <Arduino.h>

#define ICON_WIDTH 24
#define ICON_HEIGHT 24
// 'wifi' 24x24
static unsigned char wifi[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xff, 0x00, 0xe0, 0xff, 0x07, 0xf8, 0xff, 0x1f, 0xfc, 0xff, 0x3f,
   0x7e, 0x00, 0x7e, 0x1f, 0x30, 0xf8, 0x0e, 0xff, 0x71, 0xc0, 0xff, 0x07,
   0xf0, 0xff, 0x0f, 0xe0, 0xc1, 0x07, 0x40, 0x00, 0x02, 0x00, 0x3c, 0x00,
   0x00, 0xff, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x18, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// 'video' 24x24
static unsigned char video[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x01, 0xf8, 0xff, 0x11,
   0xf8, 0xff, 0x19, 0xf8, 0xff, 0x1d, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1d, 0xf8, 0xff, 0x19,
   0xf8, 0xff, 0x11, 0xf8, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// 'point_light' 24x24
static unsigned char lights[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
   0x30, 0x18, 0x0c, 0x70, 0x18, 0x0e, 0xe0, 0x18, 0x07, 0xc0, 0x81, 0x03,
   0x80, 0x00, 0x01, 0x00, 0x3c, 0x00, 0x00, 0x7e, 0x00, 0x7c, 0x7e, 0x3e,
   0x7c, 0x7e, 0x3e, 0x00, 0x7e, 0x00, 0x00, 0x38, 0x00, 0x80, 0x00, 0x01,
   0xc0, 0x81, 0x03, 0xe0, 0x18, 0x07, 0x70, 0x18, 0x0e, 0x30, 0x18, 0x0c,
   0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// 'battery_level5' 24x24
static unsigned char batteryFull[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x07,
   0xfc, 0xff, 0x0f, 0xfc, 0xff, 0x0f, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f,
   0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x0f, 0xfc, 0xff, 0x0f,
   0xf8, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// 'batery_level3'  24x24
static unsigned char batteryHalf[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x07,
   0xfc, 0xff, 0x0f, 0xfc, 0x1f, 0x0c, 0xfc, 0x1f, 0x3c, 0xfc, 0x1f, 0x3c,
   0xfc, 0x1f, 0x3c, 0xfc, 0x1f, 0x3c, 0xfc, 0x1f, 0x0c, 0xfc, 0xff, 0x0f,
   0xf8, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// 'gps' 24x24
static unsigned char gps[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
   0x00, 0x00, 0x1e, 0x00, 0x80, 0x0f, 0x00, 0xe0, 0x0f, 0x00, 0xfc, 0x0f,
   0x00, 0xff, 0x07, 0xc0, 0xff, 0x07, 0xf8, 0xff, 0x03, 0xfc, 0xff, 0x03,
   0xf0, 0xff, 0x01, 0x80, 0xff, 0x01, 0x00, 0xfc, 0x01, 0x00, 0xfc, 0x00,
   0x00, 0xf8, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x30, 0x00,
   0x00, 0x30, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
