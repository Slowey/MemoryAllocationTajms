#include "MemoryTests.h"
#include <MemoryManager.h>
#include <iostream>
#include <algorithm>



MemoryTests::MemoryTests()
{
}


MemoryTests::~MemoryTests()
{
}

void MemoryTests::CreateRandomAccessNumbers(std::string fileName, double amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        randomNumbers.push_back(i);
    }

    std::random_shuffle(randomNumbers.begin(), randomNumbers.end());

    FILE* newFile;
    fopen_s(&newFile, fileName.c_str(), "wb");
    
    fwrite(&randomNumbers[0], sizeof(int), amount, newFile);

    fclose(newFile);
}

void MemoryTests::LoadRandomAccessNumbers(std::string fileName, double amount)
{
    FILE* openFile;
    fopen_s(&openFile, fileName.c_str(), "rb");

    randomNumbers.resize(amount);
    fread(&randomNumbers[0], sizeof(int), amount, openFile);

    fclose(openFile);
}

// Test functions

void MemoryTests::TestAllocateMany(double amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
    }
}

void MemoryTests::TestAllocateListAndUseRandomly(double amount)
{
    std::vector<int*> myVector;
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        myVector.push_back(newInt);
    }

    for (size_t i = 0; i < amount - 1; i++)
    {
        *myVector[randomNumbers[i + 1]] += *myVector[randomNumbers[i]];
    }
}

void MemoryTests::TestAllocateThenDeleteRandomly(double amount)
{
    std::vector<int*> myVector;
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        myVector.push_back(newInt);
    }

    for (size_t i = 0; i < amount; i++)
    {
        delete myVector[randomNumbers[i]];
    }
}

void MemoryTests::TestAllocateManyDifferent(double amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        int* newSmall1 = new int[1];
        int* newSmall2 = new int[2];
        int* newSmall3 = new int[3];
        int* newSmall4 = new int[4];
        int* newSmall5 = new int[5];
        int* newSmall6 = new int[6];
        int* newSmall7 = new int[7];
        int* newSmall8 = new int[8];
        int* newSmall9 = new int[16];
        int* newSmall10 = new int[32];
        int* newSmall11 = new int[64];
        int* newSmall12 = new int[128];
        int* newSmall13 = new int[256];
        int* newSmall14 = new int[512];
        int* newSmall15 = new int[1024];
        int* newSmall16 = new int[2048];
    }
}

// Test for specific

struct Matrix
{
    Matrix()
    {

    }
    Matrix(float x1, float x2, float x3, float x4,
        float y1, float y2, float y3, float y4, 
        float z1, float z2, float z3, float z4,
        float w1, float w2, float w3, float w4 )
    {
        x[0] = x1;
        x[1] = x2;
        x[2] = x3;
        x[3] = x4;

        y[0] = y1;
        y[1] = y2;
        y[2] = y3;
        y[3] = y4;

        z[0] = z1;
        z[1] = z2;
        z[2] = z3;
        z[3] = z4;

        w[0] = w1;
        w[1] = w2;
        w[2] = w3;
        w[3] = w4;
    }

    void operator*(Matrix &mat)
    {
        Matrix tempMat;
        tempMat.x[0] = this->x[0] * mat.x[0] + this->x[1] * mat.y[0] + this->x[2] * mat.z[0] + this->x[2] * mat.z[0] + this->x[3] * mat.w[0];
        tempMat.x[1] = this->x[0] * mat.x[1] + this->x[1] * mat.y[1] + this->x[2] * mat.z[1] + this->x[2] * mat.z[1] + this->x[3] * mat.w[1];
        tempMat.x[2] = this->x[0] * mat.x[2] + this->x[1] * mat.y[2] + this->x[2] * mat.z[2] + this->x[2] * mat.z[2] + this->x[3] * mat.w[2];
        tempMat.x[3] = this->x[0] * mat.x[3] + this->x[1] * mat.y[3] + this->x[2] * mat.z[3] + this->x[2] * mat.z[3] + this->x[3] * mat.w[3];

        tempMat.y[0] = this->y[0] * mat.x[0] + this->y[1] * mat.y[0] + this->y[2] * mat.z[0] + this->y[2] * mat.z[0] + this->y[3] * mat.w[0];
        tempMat.y[1] = this->y[0] * mat.x[1] + this->y[1] * mat.y[1] + this->y[2] * mat.z[1] + this->y[2] * mat.z[1] + this->y[3] * mat.w[1];
        tempMat.y[2] = this->y[0] * mat.x[2] + this->y[1] * mat.y[2] + this->y[2] * mat.z[2] + this->y[2] * mat.z[2] + this->y[3] * mat.w[2];
        tempMat.y[3] = this->y[0] * mat.x[3] + this->y[1] * mat.y[3] + this->y[2] * mat.z[3] + this->y[2] * mat.z[3] + this->y[3] * mat.w[3];

        tempMat.z[0] = this->z[0] * mat.x[0] + this->z[1] * mat.y[0] + this->z[2] * mat.z[0] + this->z[2] * mat.z[0] + this->z[3] * mat.w[0];
        tempMat.z[1] = this->z[0] * mat.x[1] + this->z[1] * mat.y[1] + this->z[2] * mat.z[1] + this->z[2] * mat.z[1] + this->z[3] * mat.w[1];
        tempMat.z[2] = this->z[0] * mat.x[2] + this->z[1] * mat.y[2] + this->z[2] * mat.z[2] + this->z[2] * mat.z[2] + this->z[3] * mat.w[2];
        tempMat.z[3] = this->z[0] * mat.x[3] + this->z[1] * mat.y[3] + this->z[2] * mat.z[3] + this->z[2] * mat.z[3] + this->z[3] * mat.w[3];

        tempMat.w[0] = this->w[0] * mat.x[0] + this->w[1] * mat.y[0] + this->w[2] * mat.z[0] + this->w[2] * mat.z[0] + this->w[3] * mat.w[0];
        tempMat.w[1] = this->w[0] * mat.x[1] + this->w[1] * mat.y[1] + this->w[2] * mat.z[1] + this->w[2] * mat.z[1] + this->w[3] * mat.w[1];
        tempMat.w[2] = this->w[0] * mat.x[2] + this->w[1] * mat.y[2] + this->w[2] * mat.z[2] + this->w[2] * mat.z[2] + this->w[3] * mat.w[2];
        tempMat.w[3] = this->w[0] * mat.x[3] + this->w[1] * mat.y[3] + this->w[2] * mat.z[3] + this->w[2] * mat.z[3] + this->w[3] * mat.w[3];

        *this = tempMat;
    }

    float x[4];
    float y[4];
    float z[4];
    float w[4];
};

void MemoryTests::TestAllocateMatricesForFramesSpecific(double amount, int frames)
{
    PoolAllocator* matricAllocator = MemoryManager::Get()->CreatePoolAllocator();

    for (size_t i = 0; i < frames; i++)
    {
        std::vector<Matrix*> matrices;
        for (size_t i = 0; i < amount; i++)
        {
            Matrix* newMat = new (matricAllocator) Matrix();
            matrices.push_back(newMat);
        }
    }
}

void MemoryTests::TestAllocateAndUseMatricesForFramesSpecific(double amount, int frames)
{
    PoolAllocator* matricAllocator = MemoryManager::Get()->CreatePoolAllocator();

    for (size_t i = 0; i < frames; i++)
    {
        std::vector<Matrix*> matrices;
        for (size_t i = 0; i < amount; i++)
        {
            Matrix* newMat = new (matricAllocator) Matrix();
            matrices.push_back(newMat);
        }

        Matrix view = Matrix();
        

        for (size_t i = 0; i < amount; i++)
        {
            *matrices[i]*view;
        }
    }
}