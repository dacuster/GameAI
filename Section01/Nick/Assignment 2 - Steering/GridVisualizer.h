#pragma once

class Grid;
class GraphicsBuffer;
class Color;

class GridVisualizer : public Trackable
{
public:
	GridVisualizer( Grid* pGrid );
	~GridVisualizer();

	void addColor( int index, const Color& color );
	void removeAllEntriesOfColor( const Color& color );
	//void removeEntry( int index, const Color& color );
	void setModified() { mDirty = true; };
	void draw( GraphicsBuffer& dest );
private:
	void refresh();

	Grid* mpGrid;
	//key is color, vector contains all indices to be colored that color
	std::map< Color, std::vector<int> > mColormap;

	bool mDirty;
};