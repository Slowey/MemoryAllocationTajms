#pragma once
#include <string>
#include <vector>
#include "LibDefines.h"

class MemoryTests
{
public:
    MemoryTests();
    ~MemoryTests();
    void CreateAllocator(size_t p_size);
    void CreateRandomAccessNumbers(std::string fileName, double amount, int seed);

    void TestGenericAllocate(double amount);

    void TestGenericAllocateAndUseRandomly(double amount);

    void TestGenericAllocateDifferentSizes(double amount);

    void TestSpecificAllocate(double amount);

    void TestSpecificAllocateMatrices(double amount);

    void TestSpecificAllocateAndUseMatrices(double amount);

    void TestSpecificAllocateAndUseMatricesRandomly(double amount);

    void TestSpecificDelete(long amount);

    void TestSpecificDeleteRandomly(long amount);


   

    std::vector<int> randomNumbers;
    std::vector<int*> numbers;
    PoolAllocator* poolAllocator;
};


struct Matrix
{
    Matrix()
    {
        x[0] = 1;
        x[1] = 2;
        x[2] = 3;
        x[3] = 4;
              
        y[0] = 5;
        y[1] = 6;
        y[2] = 7;
        y[3] = 8;
              
        z[0] = 9;
        z[1] = 10;
        z[2] = 11;
        z[3] = 12;
               
        w[0] = 13;
        w[1] = 14;
        w[2] = 15;
        w[3] = 16;
    }
    Matrix(float x1, float x2, float x3, float x4,
        float y1, float y2, float y3, float y4,
        float z1, float z2, float z3, float z4,
        float w1, float w2, float w3, float w4)
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

