#ifndef PASCALCHECKER
#define PASCALCHECKER

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <set>
using namespace std;

namespace grammcheck {

	// �ؼ���������� �к� ��ֵ
	class KeyInfo {
	public:
		KeyInfo() {};
		KeyInfo(int i, string ele) {
			index = i;
			elem = ele;
		};
		int index;	// �к� ��ע������
		string elem;	// ��ֵ ���ֹؼ���
	};

	// ��˹�����Լ����
	class PascalChecker
	{
	public:
		PascalChecker();
		~PascalChecker() {};
		// ����pascalԴ�ļ�
		bool LoadSrcFile(string srcfile);
		// ����pascalԴ�ļ��ؼ���ƥ��
		void SyntaxAnalyzer();
		// ���Դ�ļ����������
		void PrintSrc();

	private:
		// ��յ�ǰ��������
		void ClearData();
		// �ؼ���ƥ��
		void KeyMatch(KeyInfo key);

		// �ؼ����ֵ䣬��������Ҫ�������йؼ���
		set<string> keywords;
		// Դ�ļ�����
		vector<string> sourcecode;
		// �ؼ���ƥ����ջ
		vector<KeyInfo> keystack;
		// ������Ϣ����
		vector<KeyInfo> errorlist;
		bool endflag;
	};
}

#endif
