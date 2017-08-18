#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Heap.hpp"
#include "BinaryTree.hpp"
#include "Pair.h"

void readFileAndSetHeap(const char* fileName, Heap<BinaryTree<Pair<char>>> &heap)
{
	std::ifstream fileToRead(fileName, std::ios::in | std::ios::binary);
	if (!fileToRead)
	{
		std::cout << "There is a problem with the file!\n";
		return;
	}

	if (fileToRead.good())
	{
		fileToRead.seekg(0, fileToRead.end);
		int fileSize = fileToRead.tellg();
		fileToRead.seekg(0, fileToRead.beg);

		std::cout << fileSize << std::endl;

		for (int i = 0; i < fileSize; ++i)
		{
			char byte;
			fileToRead.read((char*)&byte, sizeof(byte));

			Pair<char> byteToPush(byte);
			BinaryTree<Pair<char>> treeForByte(byteToPush);
			heap.insert(treeForByte);
		}

		fileToRead.close();
	}

}

void createHuffmanTree(Heap<BinaryTree<Pair<char>>> &heap, BinaryTree<Pair<char>> &huffmanTree)
{
	BinaryTree<Pair<char>> leftTree;
	BinaryTree<Pair<char>> rightTree;

	int size = heap.getSize();
	while (size > 1)
	{
		leftTree = heap.getHightestPriority();
		size--;
		rightTree = heap.getHightestPriority();
		size--;
		BinaryTree<Pair<char>>::mergeTrees(leftTree, rightTree, huffmanTree);
		heap.insert(huffmanTree);
	}

	huffmanTree = heap.getHightestPriority();
}

void compressBits(Vector<Vector<bool>> &allPathsInHuffmanTree, int posInVect, Vector<char> &resultBits)
{
	char bits = NULL;
	int bitCounter = 0;
	int sizeOfPath = allPathsInHuffmanTree[posInVect].getNumberOfElements();
	
	for (int c = 0; c < sizeOfPath; ++c)
	{
		bitCounter++;
		if (allPathsInHuffmanTree[posInVect][c])
		{
			if (bitCounter == 8)
			{
				bitCounter = 0;
				bits = NULL;
			}
			bits = bits * 2 + 1;
			resultBits.pushBack(bits);
			continue;
		}

		if (bitCounter == 8)
		{
			bitCounter = 0;
			bits = NULL;
		}
		bits = bits << 1;
		resultBits.pushBack(bits);
	}
}

void compressFile( Vector<char> &resultBits, Vector<bool> &pathInHuffmanTree, Vector<Vector<bool>> &allPathsInHuffmanTree)
{
	int sizeOfPath = allPathsInHuffmanTree.getNumberOfElements();

	for (int j = 0; j < sizeOfPath; ++j)
	{
		compressBits(allPathsInHuffmanTree, j, resultBits);
	}
}

void decompressFile()
{

}

void writeResultInTmpFile(Vector<char> &resultBits)
{
	std::ofstream fileToWrite("result.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!fileToWrite)
	{
		std::cout << "There is a problem with file to write \n";
		return;
	}

	if (fileToWrite.good())
	{
		fileToWrite.write(resultBits.getContainer(), sizeof(char)*resultBits.getNumberOfElements());

		fileToWrite.close();
	}
}

int main(int argc, char* argv[])
{
	char buff[100000];
	std::cin.getline(buff, 100);

	if (!strcmp(buff, "-Pack"))
	{
		//std::cin.getline(buff, 1000);

		BinaryTree<Pair<char>> huffmanTree;
		Heap<BinaryTree<Pair<char>>> heap;
		Vector<bool> pathInHuffmanTree;
		Vector<Vector<bool>> allPathsInHuffmanTree;
		Vector<char> resultBits;

		readFileAndSetHeap(argv[1], heap);
		createHuffmanTree(heap, huffmanTree);
		huffmanTree.findAndSetPathsInTree(pathInHuffmanTree, allPathsInHuffmanTree);
		compressFile(resultBits, pathInHuffmanTree, allPathsInHuffmanTree);
		writeResultInTmpFile(resultBits);

		return 0;
	}
	else if (!strcmp(buff, "-Unpack"))
	{
		std::cin.getline(buff, 1000);
		
		BinaryTree<Pair<char>> huffmanTree;
		Heap<BinaryTree<Pair<char>>> heap;
		Vector<bool> pathInHuffmanTree;
		Vector<Vector<bool>> allPathsInHuffmanTree;
		Vector<char> resultBits;

		readFileAndSetHeap(buff, heap);
		createHuffmanTree(heap, huffmanTree);
		huffmanTree.findAndSetPathsInTree(pathInHuffmanTree, allPathsInHuffmanTree);

		std::cin.getline(buff, 1000);

		decompressFile();

		return 0;
	}
	else if (!strcmp(buff, "-List"))
	{

		return 0;
	}

	return 0;
}