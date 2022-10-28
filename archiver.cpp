#include "archiver.h"
//=======Public=======================================

/*!
 * \brief Пустой объект, закодированные символы
 * \details Путь к файлам не указан
 */
Archiver::Archiver()
{
    inputFilePath = "";
    outputFilePath = "";
    alphabet.assign(128, "");
    alphabet['A'] = "000000";
    alphabet['B'] = "000001";
    alphabet['C'] = "000010";
    alphabet['D'] = "000011";
    alphabet['E'] = "000100";
    alphabet['F'] = "000101";
    alphabet['G'] = "000110";
    alphabet['H'] = "000111";
    alphabet['I'] = "001000";
    alphabet['J'] = "001001";
    alphabet['K'] = "001010";
    alphabet['L'] = "001011";
    alphabet['M'] = "001100";
    alphabet['N'] = "001101";
    alphabet['O'] = "001110";
    alphabet['P'] = "001111";
    alphabet['Q'] = "010000";
    alphabet['R'] = "010001";
    alphabet['S'] = "010010";
    alphabet['T'] = "010011";
    alphabet['U'] = "010100";
    alphabet['V'] = "010101";
    alphabet['W'] = "010110";
    alphabet['X'] = "010111";
    alphabet['Y'] = "011000";
    alphabet['Z'] = "011001";
    alphabet['a'] = "011010";
    alphabet['b'] = "011011";
    alphabet['c'] = "011100";
    alphabet['d'] = "011101";
    alphabet['e'] = "011110";
    alphabet['f'] = "011111";
    alphabet['g'] = "100000";
    alphabet['h'] = "100001";
    alphabet['i'] = "100010";
    alphabet['j'] = "100011";
    alphabet['k'] = "100100";
    alphabet['l'] = "100101";
    alphabet['m'] = "100110";
    alphabet['n'] = "100111";
    alphabet['o'] = "101000";
    alphabet['p'] = "101001";
    alphabet['q'] = "101010";
    alphabet['r'] = "101011";
    alphabet['s'] = "101100";
    alphabet['t'] = "101101";
    alphabet['u'] = "101110";
    alphabet['v'] = "101111";
    alphabet['w'] = "110000";
    alphabet['x'] = "110001";
    alphabet['y'] = "110010";
    alphabet['z'] = "110011";
    alphabet[' '] = "110100";
    alphabet['\n'] = "110101";
    alphabet['.'] = "110110";
    alphabet[','] = "110111";

    for (char i = 'A'; i <= 'Z'; i++)
        alph.push_back(i);
    for (char i = 'a'; i <= 'z'; i++)
        alph.push_back(i);
    alph.push_back(' ');
    alph.push_back('\n');
    alph.push_back('.');
    alph.push_back(',');
}

/*!
 * \brief Объект с указанными путями к файлам
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 */
Archiver::Archiver(std::string inputFilePath0, std::string outputFilePath0) : Archiver()
{
    inputFilePath = inputFilePath0;
    outputFilePath = outputFilePath0;
}
/*!
 * \brief Указание путей к файлам
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 */
void Archiver::SetFilesPath(std::string inputFilePath0, std::string outputFilePath0)
{
    inputFilePath = inputFilePath0;
    outputFilePath = outputFilePath0;
}
/*!
 * \brief Выполнить архивацию с заданными файлами
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 * \return 0 в случае успеха, иначе код ошибки
 */
int Archiver::ProssedArchiving(std::string inputFilePath0, std::string outputFilePath0)
{
    SetFilesPath(inputFilePath0, outputFilePath0);
    return ProssedArchiving();
}
/*!
 * \brief Выполнить деархивацию с заданными файлами
 * \param inputFilePath Путь к входному файлу
 * \param outputFilePath Путь к выходному файлу
 * \return 0 в случае успеха, иначе код ошибки
 */
int Archiver::ProssedDearchiving(std::string inputFilePath0, std::string outputFilePath0)
{
    SetFilesPath(inputFilePath0, outputFilePath0);
    return ProssedDearchiving();
}

/*!
 * \brief Выполнить архивацию
 * \details Выполняется архивация с текущими сохраненными путями к файлам
 * \return 0 в случае успеха, иначе код ошибки
 */
int Archiver::ProssedArchiving()
{
    inputFile.open(inputFilePath, std::ios::in | std::ios::binary);
    if (!inputFile)
    {
        std::cerr << "Can't open file 1\n";
        return 1;
    }

    outputFile.open(outputFilePath, std::ios::binary | std::ios::out);
    if (!outputFile)
    {
        std::cout << "File error - can't open to write data!\n";
        return 2;
    }
    MakeArchive();
    outputFile.close();
    inputFile.close();
    return 0;
}

/*!
 * \brief Выполнить деархивацию
 * \details Выполняется деархивация с текущими сохраненными путями к файлам
 * \return 0 в случае успеха, иначе код ошибки
 */

int Archiver::ProssedDearchiving()
{
    char lastBitOffset;
    inputFile.open(inputFilePath, std::ios::in | std::ios::binary);
    if (!inputFile)
    {
        std::cerr << "Can't open file 2\n";
        return 1;
    }
    inputFile >> lastBitOffset;

    outputFile.open(outputFilePath, std::ios::binary | std::ios::out);
    if (!outputFile)
    {
        std::cout << "File error - can't open to write data!\n";
        return 2;
    }
    MakeDearchive(lastBitOffset);

    inputFile.close();
    outputFile.close();
    return 0;
}

//=======Private=======================================================

void Archiver::MakeArchive()
{
    outputFile.put('\0');
    int offset = 0; char currentByte = 0;
    for (char i = 0; inputFile.read(&i, 1);)
    {
        for (size_t j = 0; j < alphabet[i].size(); j++)
        {
            if (alphabet[i][j] == '0')
                currentByte <<= 1;
            else
                currentByte = (currentByte << 1) | 1;
            if ((++offset) >= 8)
            {
                outputFile.put(currentByte);
                offset = 0;
                currentByte = 0;
            }
        }
    }

    if (offset)
    {
        currentByte <<= 8 - offset;
        outputFile.put(currentByte);
    }
    currentByte = !offset ? 8 : offset;
    outputFile.seekp(0);
    outputFile.put(currentByte);
    std::cout << "The archiving was successful" << std::endl;
}

void Archiver::MakeDearchive(int lastBitOffset)
{
    char c0, c1;
    int n = 0, t = 0;
    int mask = 0b10000000;
    inputFile.get(c0);
    while (1)
    {
        if (inputFile.get(c1))
        {
            for (int i = 0; i < 8; i++)
            {
                t <<= 1;
                if (c0 & mask)
                    t++;
                if ((++n) >= 6)
                {
                    outputFile.put(alph[t]);
                    t = 0;
                    n = 0;
                }
                c0 <<= 1;
            }
            c0 = c1;
        }
        else
        {
            for (int i = 0; i < lastBitOffset; i++)
            {
                t <<= 1;
                if (c0 & mask)
                    t++;
                if ((++n) >= 6)
                {
                    outputFile.put(alph[t]);
                    t = 0;
                    n = 0;
                }
                c0 <<= 1;
            }
            break;
        }
    }
    std::cout << "The dearchiving was successful" << std::endl;
}
