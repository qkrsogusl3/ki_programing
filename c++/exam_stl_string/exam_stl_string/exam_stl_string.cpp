// exam_stl_string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
	
	string srcString = "ABCDEFG ȫ�浿 HIJKLMN �浿 OPQRSTU �� VWXYZ";
	
	cout << "ã�� ���ڿ� �Է�: " << endl;
	string findString;
	getline(cin, findString);

	int cnt = 0;
	string::size_type findOffset = 0;

	while (true)
	{
		cout << findOffset << endl;


		findOffset = srcString.find(findString, findOffset);

		if (string::npos == findOffset)
			break;

		cnt++;
		findOffset++;
	}
	cout << "���ڿ� ( " << findString << " ) �� ����: " << cnt << endl;
	cout << findOffset << endl;

	/*string str("1234567890");

	cout << str.substr(5) << endl;
	cout << str.substr(5,3) << endl;
*/

	return 0;

	//string astring;
	//getline(cin, astring);
	//remove(astring.begin(), astring.end(), 't');
	//cout << astring << endl;

	//return 0;

	//string str = "string sample";

	//cout << "str( \"sample\",16) : " << str << ";" << endl;
	//cout << "string size : " << str.size() << endl;
	//cout << "string length : " << str.length() << endl;
	//cout << "string capacity : " << str.capacity() << endl;
	//cout << "string max_size : " << str.max_size() << endl;
	//cout << endl;

	//str.reserve(32);
	//cout << "str.reserve(32) : " << str << ";" << endl;
	//cout << "string size : " << str.size() << endl;
	//cout << "string length : " << str.length() << endl;
	//cout << "string capacity : " << str.capacity() << endl;
	//cout << "string max_size : " << str.max_size() << endl;
	//cout << endl;

	//str = "this is a sample : simple is the best. isn't it?...................";
	//cout << "str : " << str << ";" << endl;
	//cout << "string size : " << str.size() << endl;
	//cout << "string length : " << str.length() << endl;
	//cout << "string capacity : " << str.capacity() << endl;
	//cout << "string max_size : " << str.max_size() << endl;
	//cout << endl;


    //return 0;

}

