#include "pascalchecker.h"

namespace grammcheck {

	// Ĭ�ϳ�ʼ�� �ؼ����ֵ�
	PascalChecker::PascalChecker() {
		keywords = { "begin", "end", "if", "else", "then", "end.", "end;" };
		endflag = false;
	}

	// ����pascalԴ�ļ�
	bool PascalChecker::LoadSrcFile(string srcfile) {
		ifstream inf(srcfile);
		string src;
		ClearData();	// �����ļ�����յ�ǰ����
		// �ļ���������Чʱ��ʾ������
		if (!inf) {
			cout << "The path of source file is valid!" << endl;
			return false;
		}
		// ���ж�ȡpascalԴ�ļ�
		while (!inf.eof()) {
			getline(inf, src);
			sourcecode.push_back(src);
		}
		// �ļ�Ϊ��ʱ�������ʾ�����أ��������
		if (!sourcecode.size()) {
			cout << "The file you opened is empty!" << endl;
			return false;
		}
		cout << "The analysis result is as follows:" << endl;
		return true;
	}

	// ����pascalԴ�ļ��ؼ���ƥ��
	void PascalChecker::SyntaxAnalyzer() {
		for (int i = 0; i < sourcecode.size(); ++i) {
			string codeline = sourcecode[i];
			// ����д��ĸ��ת��ΪСд����Ϊpascal���Դ�Сд������
			for (auto &c : codeline) {
				c = tolower(c);
			}
			string word;
			istringstream istring(codeline);
			while (istring >> word) {
				// ���ֵ��в��ҵ�ǰword��ȷ���Ƿ�Ϊ�ؼ���
				if (keywords.find(word) != keywords.end()) {
					KeyInfo info(i+1, word);
					// ���йؼ���ƥ��
					KeyMatch(info);	
				}
			}
		}
		// ƥ����ɺ󣬹ؼ���ջ���в�����˵��δƥ�䣬������������Ϣ
		if (keywords.size()) {
			for (auto &info : errorlist) {
				keystack.push_back(info);
			}
			errorlist.swap(keystack);

		}
	}

	// ���Դ�ļ����������
	void PascalChecker::PrintSrc() {
		cout << "**********************************" << endl;
		int i = 1;
		for (auto &src : sourcecode) {
			string errorflag = " ";
			// ������д��ڴ�����ǰ��*
			for (auto &error : errorlist) {
				if (i == error.index) {
					errorflag = "*";
				}
			}
			cout.width(3);
			cout << i++ << errorflag + src << endl;
		}
		cout << "************** error *************" << endl;
		// ���������Ϣ
		for (auto key : errorlist) {
			cout << "line " << key.index << ": " + key.elem + " have no matching keywords" <<endl;
		}
	}

	// ��յ�ǰ��������
	void PascalChecker::ClearData() {
		sourcecode.clear();
		keystack.clear();
		errorlist.clear();
		endflag = false;
	}

	// �ؼ���ƥ��
	void PascalChecker::KeyMatch(KeyInfo keyinfo) {
		auto iter_begin = keystack.begin(), iter_end = keystack.end();
		string lastkey, key = keyinfo.elem;
		KeyInfo lastinfo;
		if (iter_begin != iter_end) {		// �ؼ���ջ�ǿ�ʱ
			lastinfo = keystack[keystack.size() - 1];
			lastkey = lastinfo.elem;
			if (key == "begin" || key == "if") {
				if (lastkey == "if") {
					errorlist.push_back(lastinfo);
					keystack.pop_back();
					keystack.push_back(keyinfo);
				}
				else {
					keystack.push_back(keyinfo);
				}
			}
			else if (key == "then") {
				if (lastkey == "if") {
					keystack.push_back(keyinfo);
				}
				else {
					errorlist.push_back(keyinfo);
				}
			}
			else if (key == "else") {
				if (lastkey == "then") {
					keystack.pop_back();
					keystack.pop_back();
				}
				else {
					errorlist.push_back(keyinfo);
				}
			}
			else if (key == "end" || key == "end;") {
				if (lastkey == "begin") {
					keystack.pop_back();
				}
				else if (lastkey == "then") {
					keystack.pop_back();
					keystack.pop_back();
					KeyMatch(keyinfo);
				}
				else if (lastkey == "if") {
					keystack.pop_back();
					errorlist.push_back(lastinfo);
					KeyMatch(keyinfo);
				}
			}
		}
		else {		// �ؼ���ջΪ��ʱ��˵�����ļ�ͷ
			if (key == "begin") {
				keystack.push_back(keyinfo);
			}
			else {
				errorlist.push_back(keyinfo);
			}
		}
	}

}
