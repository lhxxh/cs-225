/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* retmos=new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    vector<Point<3>> kdtreenode;
    map<Point<3>,TileImage*> record;
    for(vector<TileImage>::iterator it=theTiles.begin();it!=theTiles.end();++it){
      kdtreenode.push_back(convertToXYZ(it->getAverageColor()));
      record.insert(pair<Point<3>,TileImage*>(convertToXYZ(it->getAverageColor()),&(*it)));
    }
    KDTree<3>* kdtree=new KDTree<3>(kdtreenode);
    for(int y=0;y<theSource.getRows();y++){
      for(int x=0;x<theSource.getColumns();x++){
        Point<3> nearest=kdtree->findNearestNeighbor(convertToXYZ(theSource.getRegionColor(y,x)));
        retmos->setTile(y,x,record.find(nearest)->second);
      }
    }

    delete kdtree;
    return retmos;
}
