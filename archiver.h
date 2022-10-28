#pragma once
#include <stdio.h>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <iostream>

/*!
 * \brief ��������� ���������� ����
 *
 * ������ ����� ������������ �� ���� ����� ������� ��� ��������� ��������� ������, ���������� ���������� �����
 */
class Archiver {
public:
    Archiver();
    Archiver(std::string inputFilePath, std::string outputFilePath);

    void SetFilesPath(std::string inputFilePath, std::string outputFilePath);
    int ProssedArchiving();
    int ProssedDearchiving();
    int ProssedArchiving(std::string inputFilePath, std::string outputFilePath);
    int ProssedDearchiving(std::string inputFilePath, std::string outputFilePath);

private:
    std::string inputFilePath;
    std::string outputFilePath;

    std::ifstream inputFile;
    std::ofstream outputFile;

    std::vector<std::string> alphabet;
    std::vector<char> alph;
    void MakeArchive();
    void MakeDearchive(int lastBitOffset);
};