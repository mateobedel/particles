#include "Vecteur.hxx"
#include <gtest/gtest.h>

TEST(VecteurTest, NormTest) {
    Vecteur v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.norm(), 5.0f); 
}

TEST(VecteurTest, OperatorAddTest) {
    Vecteur v1(1.0f, 2.0f, 3.0f);
    Vecteur v2(4.0f, 5.0f, 6.0f);
    Vecteur result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(VecteurTest, OperatorSubtractTest) {
    Vecteur v1(5.0f, 6.0f, 7.0f);
    Vecteur v2(1.0f, 2.0f, 3.0f);
    Vecteur result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 4.0f);
}

TEST(VecteurTest, OperatorMultiplyTest) {
    Vecteur v1(1.0f, 2.0f, 3.0f);
    Vecteur v2(4.0f, 5.0f, 6.0f);
    Vecteur result = v1 * v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 10.0f);
    EXPECT_FLOAT_EQ(result.z, 18.0f);
}

TEST(VecteurTest, OperatorDivideTest) {
    Vecteur v1(4.0f, 6.0f, 8.0f);
    Vecteur v2(2.0f, 3.0f, 4.0f);
    Vecteur result = v1 / v2;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 2.0f);
}


TEST(VecteurTest, AssignmentOperatorTest) {
    Vecteur v1(1.0f, 2.0f, 3.0f);
    Vecteur v2 = v1;
    EXPECT_FLOAT_EQ(v2.x, 1.0f);
    EXPECT_FLOAT_EQ(v2.y, 2.0f);
    EXPECT_FLOAT_EQ(v2.z, 3.0f);
}


TEST(VecteurTest, OperatorPlusEqualsTest) {
    Vecteur v(1.0f, 2.0f, 3.0f);
    v += Vecteur(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(v.x, 5.0f);
    EXPECT_FLOAT_EQ(v.y, 7.0f);
    EXPECT_FLOAT_EQ(v.z, 9.0f);
}

TEST(VecteurTest, OperatorMinusEqualsTest) {
    Vecteur v(5.0f, 6.0f, 7.0f);
    v -= Vecteur(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 4.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
    EXPECT_FLOAT_EQ(v.z, 4.0f);
}

TEST(VecteurTest, OperatorMultiplyEqualsTest) {
    Vecteur v(1.0f, 2.0f, 3.0f);
    v *= Vecteur(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(v.x, 4.0f);
    EXPECT_FLOAT_EQ(v.y, 10.0f);
    EXPECT_FLOAT_EQ(v.z, 18.0f);
}

TEST(VecteurTest, OperatorDivideEqualsTest) {
    Vecteur v(4.0f, 6.0f, 8.0f);
    v /= Vecteur(2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 2.0f);
}


TEST(VecteurTest, OperatorAddScalarTest) {
    Vecteur v(1.0f, 2.0f, 3.0f);
    Vecteur result = v + 2.0f;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 5.0f);
}

TEST(VecteurTest, OperatorMultiplyScalarTest) {
    Vecteur v(1.0f, 2.0f, 3.0f);
    Vecteur result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

