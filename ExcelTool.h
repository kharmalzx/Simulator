#pragma once
#include <xlsxcell.h>
#include <xlsxdocument.h>
#include "Data.h"


using QXlsx::Document;
using QXlsx::Cell;
using QXlsx::Format;

class ExcelTool 
{
public:
	ExcelTool();
	~ExcelTool();

	QVariant getNumericCellValue(int row, int col);
	QVariant getStringCellValue(int row, int col);
	bool setWorkbook(QString filePath);
	bool setWorksheet(QString sheetName);
	bool setMapSheet(QString sheetName);
	int getSheetRow();
	int getSheetCol();


	void readCom2Shelf();
	Data* data;
	
private:
	Document* wks;
	QString sheet_map;
	QString sheet_customer;

	
	Map* map;
};
