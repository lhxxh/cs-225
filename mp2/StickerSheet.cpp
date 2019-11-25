#include "StickerSheet.h"
#include "Image.h"
using namespace cs225;

void StickerSheet::_copy(const StickerSheet& other){
  //clear itself
  delete[] stickerarray;

 //assign numbers
  base=other.base;
  maxnum=other.maxnum;
  stickerarray=new Sticker[maxnum];
  for(unsigned i=0;i<maxnum;i++){
    stickerarray[i]=other.stickerarray[i];
  }
}

StickerSheet::StickerSheet( const Image & picture,unsigned int max){
  base=& picture;
  stickerarray=new Sticker[max];
  maxnum=max;
}

StickerSheet::~StickerSheet(){
delete[] stickerarray;
}

StickerSheet::StickerSheet(const StickerSheet& other){
stickerarray=nullptr;
_copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
if(this!=&other)
{
  _copy(other);
}
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned int max){
if(max<maxnum)
{
  for(unsigned int i=max;i<maxnum;i++){
  stickerarray[i].set_imageptr(nullptr);
  stickerarray[i].set_coordinate_x(0);
  stickerarray[i].set_coordinate_y(0);
  }
 }
 else if(max>maxnum)
 {
   Sticker* temp=new Sticker[max];
  for(unsigned int i=0;i<maxnum;i++)
  temp[i]=stickerarray[i];
  delete[] stickerarray;
  stickerarray=temp;
 }
 maxnum=max;
}

int StickerSheet::addSticker(Image& sticker,unsigned int x,unsigned int y){
if(stickerarray[maxnum-1].get_imageptr()==nullptr)
{
  unsigned int i=0;
  while(stickerarray[i].get_imageptr()!=nullptr)
    i+=1;

    stickerarray[i].set_imageptr(&sticker);
    stickerarray[i].set_coordinate_x(x);
    stickerarray[i].set_coordinate_y(y);
    return 0;
}
else
return -1;
}

bool StickerSheet::translate(unsigned int index,unsigned int x,unsigned int y){
  if(index<maxnum)
  {
  if(stickerarray[index].get_imageptr()!=0)
  {
    stickerarray[index].set_coordinate_x(x);
    stickerarray[index].set_coordinate_y(y);
    return true;
  }
  else
  return false;
  }
  else
  return false;
}

void StickerSheet::removeSticker(unsigned int index){
for(unsigned int i=index;i<maxnum-1;i++)
stickerarray[i]=stickerarray[i+1];
}

Image* StickerSheet::getSticker(unsigned int index) const{
if(index<maxnum)
return stickerarray[index].get_imageptr();
else
return nullptr;
}

Image StickerSheet::render() const {
//prepare new base pictur
unsigned int wid=base->width();
unsigned int hei=base->height();
Image* new_base=new Image;
new_base->resize(wid,hei);
for(unsigned int b=0;b<hei;b++){
  for(unsigned int a=0;a<wid;a++){
    HSLAPixel& new_pixel=new_base->getPixel(a,b);
    HSLAPixel& old_pixel=base->getPixel(a,b);
    new_pixel=old_pixel;
  }
}

//resize base picture

unsigned int new_base_hei=hei;
unsigned int new_base_wid=wid;
for(unsigned int i=0;i<maxnum;i++){
  Image* image_ptr=stickerarray[i].get_imageptr();
  unsigned int x=stickerarray[i].get_coordinate_x();
  unsigned int y=stickerarray[i].get_coordinate_y();
  if(image_ptr==nullptr){break;}
  unsigned int image_wid=(stickerarray[i].get_imageptr())->width();
  unsigned int image_hei=(stickerarray[i].get_imageptr())->height();

  if((x+image_wid)>=wid)
   new_base_wid=x+image_wid+1;
   if((y+image_hei)>=hei)
   new_base_hei=y+image_hei+1;
}
new_base->resize(new_base_wid,new_base_hei);

//add sticker

for(unsigned int i=0;i<maxnum;i++){
Image* image_ptr=stickerarray[i].get_imageptr();
unsigned int x=stickerarray[i].get_coordinate_x();
unsigned int y=stickerarray[i].get_coordinate_y();
if(image_ptr==nullptr){break;}
unsigned int image_width=(stickerarray[i].get_imageptr())->width();
unsigned int image_height=(stickerarray[i].get_imageptr())->height();
for(unsigned int d=0;d<image_height;d++){
  for(unsigned int c=0;c<image_width;c++){
    HSLAPixel& base_pixel=new_base->getPixel(c+x,d+y);
    HSLAPixel& image_pixel=image_ptr->getPixel(c,d);
    if(image_pixel.a!=0)
    base_pixel=image_pixel;
  }
 }
}
 Image ret= *new_base;
 delete new_base;
 return ret;
}

void StickerSheet::set_stickerarray(Sticker* head){
  stickerarray=head;
}


Image* Sticker::get_imageptr(){
  return image;
}

void Sticker::set_imageptr(Image *ptr){
  image=ptr;
}

unsigned int Sticker::get_coordinate_x(){
  return coordinate_x;
}

void Sticker::set_coordinate_x(unsigned int x){
  coordinate_x=x;
}

unsigned int Sticker::get_coordinate_y(){
  return coordinate_y;
}

void Sticker::set_coordinate_y(unsigned int y){
  coordinate_y=y;
}
