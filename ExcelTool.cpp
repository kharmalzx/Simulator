#include "ExcelTool.h"

template<typename T>
bool notInVector(const vector<T>& vec, const T& item) {
	for (const T& element : vec)
		if (element == item)
			return false;
	return true;
}


ExcelTool::ExcelTool()
{
	sheet_map = QString("map Store1");
	wks = new Document("param/sim_param.xlsm");
	data = new Data();
	map = data->map;
}

ExcelTool::~ExcelTool()
{
	delete data;
	delete wks;
}

QVariant ExcelTool::getNumericCellValue(int row, int col)
{
	
	if(wks->cellAt(row, col))
		return wks->cellAt(row, col)->value();
	else {
		system("pause");
		std::cout << "Error: getNumericCellValue at " << row << ", " << col << std::endl;
		return QVariant();
	}

}

QVariant ExcelTool::getStringCellValue(int row, int col)
{
	Cell* cell = wks->cellAt(row, col);
	if (cell && cell->cellType() == Cell::StringType)
		return cell->value();
	else {
		system("pause");
		std::cout << "Error: getStringCellValue at " << row << ", " << col << std::endl;
		return QVariant();
	}
}

bool ExcelTool::setWorkbook(QString filePath)
{	
	if(wks!=nullptr)delete wks;

	wks =new Document(filePath);

	if (wks->load())
		return true;
	return false;
}

bool ExcelTool::setWorksheet(QString sheetName)
{
	wks->selectSheet(sheetName);
	if(!wks->load())
		return false;
	return true;
}

bool ExcelTool::setMapSheet(QString sheetName)
{
	if(wks->currentSheet()->sheetName()==sheetName)
		return true;

	wks->selectSheet(sheetName);
	sheet_map = sheetName;
	if (!wks->load())
		return false;
	return true;
}

int ExcelTool::getSheetRow()
{
	int row = 1;
	while (wks->cellAt(row, 1) && wks->cellAt(row,1)->value().toString()!="") {
		row++;
	}
	row--;

	return row;
}

int ExcelTool::getSheetCol()
{
	int col = 1;
	while (wks->cellAt(1, col) && wks->cellAt(1, col)->value().toString()!="") {
		col++;
	}
	col--;

	return col;
}

void ExcelTool::readCom2Shelf()
{
	wks->selectSheet("sn_sn");

}
