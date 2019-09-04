#include "pascalchecker.h"
#include <iostream>
using namespace grammcheck;

int main()
{
	PascalChecker checker;
	string path("pascal_src0.pas");
	// ���Ĭ���ļ���Ч��������������
	if (checker.LoadSrcFile(path)) {
		checker.SyntaxAnalyzer();
		checker.PrintSrc();
	}
	// ��ѭ���������ļ������ɼ������������ļ�
	while (1) {
		cout << endl << "Please enter the path of the pascal source file!(enter exit to quit)" << endl;
		cin >> path;
		if (path == "exit") {
			return 0;
		}
		if (checker.LoadSrcFile(path)) {
			checker.SyntaxAnalyzer();
			checker.PrintSrc();
		}
	}
	return 0;
}
