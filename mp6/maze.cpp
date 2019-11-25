/* Your code here! */
#include "maze.h"
SquareMaze::SquareMaze(){
  width_=0;
  height_=0;
  size_=0;
}

void SquareMaze::makeMaze(int width,int height){
  width_=width;
  height_=height;
  size_=width_*height_;
  cells.addelements(size_);
  int drawcounter1=15;
  int drawcounter2=15;

  for(int i=0;i<size_;i++){
    rightwall.push_back(true);
    downwall.push_back(true);
  }
  sleep(1);
  srand(time(NULL));
  //helper variable
  int time=0;

  for(int counter=size_/2;counter>0;counter--){
    int deleteright=rand()%2;
    int row=rand()%(height_-1);
    int column=rand()%(width_-1);

    if(deleteright){
     if(rightwall[row*width_+column]==true&&cells.find(row*width_+column)!=cells.find(row*width_+column+1)){
       cells.setunion(row*width_+column,row*width_+column+1);
       rightwall[row*width_+column]=false;
     }
    }
    else{
     if(downwall[row*width_+column]==true&&cells.find(row*width_+column)!=cells.find((row+1)*width_+column)){
       cells.setunion(row*width_+column,(row+1)*width_+column);
       downwall[row*width_+column]=false;
     }
    }

}
//exclude the final cell by -1 on size_
for(int cellnum=0;cellnum<size_-1;cellnum++){
  //right-most cells
  if(cellnum%width_==width_-1){
    if(downwall[cellnum]==true&&cells.find(cellnum)!=cells.find(cellnum+width_)){
      cells.setunion(cellnum,cellnum+width_);
      downwall[cellnum]=false;
    }
  }
  //down-most cells
  else if(cellnum+width_>=size_){
    if(rightwall[cellnum]==true&&cells.find(cellnum)!=cells.find(cellnum+1)){
      cells.setunion(cellnum,cellnum+1);
      rightwall[cellnum]=false;
    }
  }
  //not rightmost and downmost cell
  else{
    int rightfirst=rand()%2;

    if(rightfirst){
      if(rightwall[cellnum]==true&&cells.find(cellnum)!=cells.find(cellnum+1)){
        cells.setunion(cellnum,cellnum+1);
        rightwall[cellnum]=false;
      }
      if(downwall[cellnum]==true&&cells.find(cellnum)!=cells.find(cellnum+width_)){
        cells.setunion(cellnum,cellnum+width_);
        downwall[cellnum]=false;
      }
    }
    else{
      if(downwall[cellnum]==true&&cells.find(cellnum)!=cells.find(cellnum+width_)){
        cells.setunion(cellnum,cellnum+width_);
        downwall[cellnum]=false;
      }
      if(rightwall[cellnum]==true&&cells.find(cellnum)!=cells.find(cellnum+1)){
        cells.setunion(cellnum,cellnum+1);
        rightwall[cellnum]=false;
      }
    }
  }
}
}

bool SquareMaze::canTravel(int x,int y,int dir)const{
  int cellnum=y*width_+x;
  if(dir==0){
    if(rightwall[cellnum]==false)
    return true;
    else
    return false;
  }
  else if(dir==1){
    if(downwall[cellnum]==false)
    return true;
    else
    return false;
  }
  else if(dir==2){
    if(cellnum>0){
    if(rightwall[cellnum-1]==false)
    return true;
  }
    else
    return false;
  }
  else if(dir==3){
    if(cellnum-width_>=0){
    if(downwall[cellnum-width_]==false)
    return true;
  }
    else
    return false;
  }
  return false;
}

void SquareMaze::setWall(int x,int y,int dir,bool exists){
  int cellnum=y*width_+x;
  if(cellnum>=0){
  if(dir==0){
    if(exists&&cellnum%width_!=width_-1)
    rightwall[cellnum]=true;
    else
    rightwall[cellnum]=false;
  }
  else if(dir==1){
    if(exists&&cellnum+width_<size_)
    downwall[cellnum]=true;
    else
    downwall[cellnum]=false;
  }
}
}

vector<int> SquareMaze::solveMaze(){
vector<bool> visited;
vector<pair<int,int>> path_coordinate;
vector<pair<int,int>> solution_coordinate;
vector<int> ret;
int xValueofDes=width_;
unsigned maxLength=0;
stack<pair<int,int>> coordinate;
for(int i=0;i<size_;i++){visited.push_back(false);}
if(!canTravel(0,0,0)&&!canTravel(0,0,1)&&!canTravel(0,0,2)&&!canTravel(0,0,3)){return ret;}//case for which cannot move around from origin
//initialize the coordinate stack
coordinate.push(make_pair(0,0));
while(!coordinate.empty()){
  pair<int,int> pop_elem=coordinate.top();
  coordinate.pop();
  int x_coordinate=pop_elem.first;
  int y_coordinate=pop_elem.second;
  visited[y_coordinate*width_+x_coordinate]=true;
  path_coordinate.push_back(pop_elem);
  int flag=0;
  if(canTravel(x_coordinate,y_coordinate,0)){
    if(visited[y_coordinate*width_+x_coordinate+1]==false){
      coordinate.push(make_pair(x_coordinate+1,y_coordinate));
      flag=1;
    }
  }
  if(canTravel(x_coordinate,y_coordinate,1)){
    if(visited[(y_coordinate+1)*width_+x_coordinate]==false){
      coordinate.push(make_pair(x_coordinate,y_coordinate+1));
      flag=1;
    }
  }
  if(canTravel(x_coordinate,y_coordinate,2)){
    if(visited[y_coordinate*width_+x_coordinate-1]==false){
      coordinate.push(make_pair(x_coordinate-1,y_coordinate));
      flag=1;
    }
  }
  if(canTravel(x_coordinate,y_coordinate,3)){
    if(visited[(y_coordinate-1)*width_+x_coordinate]==false){
      coordinate.push(make_pair(x_coordinate,y_coordinate-1));
      flag=1;
    }
  }
  //checkpoint for solution print
       if(y_coordinate==height_-1){
         if(maxLength<path_coordinate.size()){
          solution_coordinate.assign(path_coordinate.begin(),path_coordinate.end());
          maxLength=path_coordinate.size();
          xValueofDes=x_coordinate;
        }
        else if(maxLength==path_coordinate.size()){
          if(x_coordinate<xValueofDes){
            solution_coordinate.assign(path_coordinate.begin(),path_coordinate.end());
            maxLength=path_coordinate.size();
            xValueofDes=x_coordinate;
          }
        }
      }
//pop path element when no direction to go (backtrace)
if(flag==0){
  while(!path_coordinate.empty()){
    pair<int,int> path_elem=path_coordinate.back();
    int path_x=path_elem.first;
    int path_y=path_elem.second;
    if(canTravel(path_x,path_y,0)){
      if(visited[path_y*width_+path_x+1]==false){break;}
    }
    if(canTravel(path_x,path_y,1)){
      if(visited[(path_y+1)*width_+path_x]==false){break;}
    }
    if(canTravel(path_x,path_y,2)){
      if(visited[path_y*width_+path_x-1]==false){break;}
    }
    if(canTravel(path_x,path_y,3)){
      if(visited[(path_y-1)*width_+path_x]==false){break;}
    }
    path_coordinate.pop_back();
  }
}

}
//copy the solution into return
for(unsigned i=1;i<solution_coordinate.size();i++){
  pair<int,int> present=solution_coordinate[i];
  pair<int,int> previous=solution_coordinate[i-1];
  if(present.first-previous.first==1){ret.push_back(0);}
  else if(present.first-previous.first==-1){ret.push_back(2);}
  else if(present.second-previous.second==1){ret.push_back(1);}
  else if(present.second-previous.second==-1){ret.push_back(3);}
}
return ret;
}



PNG* SquareMaze::drawMaze() const{
  PNG* mazeImage=new PNG(width_*10+1,height_*10+1);
  //top most line blacken it except entrance
  for(unsigned i=10;i<mazeImage->width();i++){
    HSLAPixel& pixel=mazeImage->getPixel(i,0);
    pixel=HSLAPixel(0,1,0,1);
  }
  //left most line blacken it
  for(unsigned j=0;j<mazeImage->height();j++){
    HSLAPixel& pixel=mazeImage->getPixel(0,j);
    pixel=HSLAPixel(0,1,0,1);
  }
  //blacken maze wall
  for(int i=0;i<height_;i++){
    for(int j=0;j<width_;j++){
    if(rightwall[i*width_+j]==true){
      int counter=10;
      for(int a=0;a<=counter;a++){
        HSLAPixel& pixel=mazeImage->getPixel((j+1)*10,i*10+a);
        pixel=HSLAPixel(0,1,0,1);
      }
    }
    if(downwall[i*width_+j]==true){
      int counter=10;
      for(int a=0;a<=counter;a++){
        HSLAPixel& pixel=mazeImage->getPixel(j*10+a,(i+1)*10);
        pixel=HSLAPixel(0,1,0,1);
      }
    }
  }
}
  return mazeImage;
}

PNG* SquareMaze::drawMazeWithSolution(){
  PNG* maze=drawMaze();
  vector<int> solution=solveMaze();
  int counter=11;
  int x_position=5;
  int y_position=5;
  for(const int& it:solution){
    if(it==0){
      for(int i=0;i<counter;i++){
      HSLAPixel& pixel=maze->getPixel(x_position+i,y_position);
      pixel=HSLAPixel(0,1,0.5,1);
      }
      x_position+=10;
    }
    else if(it==1){
      for(int i=0;i<counter;i++){
      HSLAPixel& pixel=maze->getPixel(x_position,y_position+i);
      pixel=HSLAPixel(0,1,0.5,1);
      }
      y_position+=10;
    }
    else if(it==2){
     for(int i=0;i<counter;i++){
     HSLAPixel& pixel=maze->getPixel(x_position-i,y_position);
     pixel=HSLAPixel(0,1,0.5,1);
    }
      x_position-=10;
    }
    else if(it==3){
      for(int i=0;i<counter;i++){
      HSLAPixel& pixel=maze->getPixel(x_position,y_position-i);
      pixel=HSLAPixel(0,1,0.5,1);
     }
       y_position-=10;
    }
  }
  if(static_cast<unsigned>(y_position+5)==maze->height()-1){
  y_position+=5;              //reach the end line
  counter=5;
  for(int i=0;i<counter;i++){
    HSLAPixel& pixelleft=maze->getPixel(x_position-i,y_position);
    HSLAPixel& pixelright=maze->getPixel(x_position+i,y_position);
    pixelleft=HSLAPixel();
    pixelright=HSLAPixel();
  }
}
  return maze;
}
