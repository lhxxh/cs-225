#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("alma.png");
  Image i;    i.readFromFile("i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40,  50);
  sheet.addSticker(i, 60, 100);
  Image final_image=sheet.render();
  final_image.writeToFile("myImage.png");
  return 0;
}
