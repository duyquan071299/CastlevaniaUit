#include"conio.h"
#include"stdio.h"
#include"string.h"
#include"iostream"
#include <fstream>
#include <windows.h> 
using namespace std;

#define CELL_WIDTH 256
#define CELL_HEIGHT 416
#define TILE_SIZE 32

void CreatrGridFile(int level)
{
	ifstream ifile;
	char fileMapName[45];
	sprintf_s(fileMapName, "Resources\\Maps\\Scene%d.txt", level);
	ifile.open(fileMapName);
	int Columns, Rows;
	ifile >> Columns >> Rows;
	ifile.close();
	cout << Columns;

	int GridCols = (Columns*TILE_SIZE) / CELL_WIDTH;
	int GridRows = ((Rows*TILE_SIZE) / CELL_HEIGHT) + 1;

	char gridFileName[30];
	sprintf_s(gridFileName, "Resources\\Maps\\Grid%d.txt", level);
	ofstream ofile;
	ofile.open(gridFileName);
	ofile << GridCols << " " << GridRows;

	char objectsFileName[45];
	sprintf_s(objectsFileName, "Resources\\Maps\\Scene%d_Object.txt", level);
	ifile.open(objectsFileName);
	
	while (ifile.good()) {
		int type, x, y, holder, width, height;
		ifile >> type >> x >> y >> width >> height >> holder;
		int LeftCell = int(x) / CELL_WIDTH;
		int RightCell = int(x + width) / CELL_WIDTH;
		int TopCell = int(y) / CELL_HEIGHT;
		int BottomCell = int(y + height) / CELL_HEIGHT;
		ofile << "\n" << type << " " << x << " " << y << " " << width << " " << height << " " << holder;
		ofile << "\n" << LeftCell << " " << RightCell << " " << TopCell << " " << BottomCell;
	}
	ifile.close();
	ofile.close();

		


}

int main()
{
	int level;
	const char* newDir = R"(D:\CastlevaniaUit\CastlevaniaUit\)";
		if (!SetCurrentDirectory(newDir)) {
			std::cerr << "Error setting current directory: #" << GetLastError();
			return 1; // quit if we couldn't set the current directory
		}
	cout << "Insert level you want to create grid: ";
	cin >> level;
	cout << "\n";
	CreatrGridFile(level);
	system("Pause");
	return 0;
	
}