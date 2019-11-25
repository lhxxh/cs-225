/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
class Sticker;
class StickerSheet{
public:
  StickerSheet(const Image& picture,unsigned int max);
  ~StickerSheet();
  StickerSheet(const StickerSheet& other);
  const StickerSheet& operator=(const StickerSheet &other);
  void changeMaxStickers(unsigned int max);
  int addSticker(Image &sticker,unsigned int x,unsigned int y);
  bool translate(unsigned index,unsigned int x,unsigned int y);
  void removeSticker(unsigned int index);
  Image* getSticker(unsigned int index) const;
  Image render() const;
  void set_stickerarray(Sticker* head);
private:
  void _copy(const StickerSheet& other);
  const Image* base=nullptr;
  Sticker* stickerarray=nullptr;      //array hold the sticker class
  unsigned int maxnum=0;
};

//subclass for {image,x,y}
class Sticker{
public:
  Image* get_imageptr();
  void set_imageptr(Image* ptr);
  unsigned int get_coordinate_x();
  void set_coordinate_x(unsigned int x);
  unsigned int get_coordinate_y();
  void set_coordinate_y(unsigned int y);
private:
  Image* image=nullptr;
  unsigned int coordinate_x=0;
  unsigned int coordinate_y=0;
};
