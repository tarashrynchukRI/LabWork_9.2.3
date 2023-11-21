#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_9.2.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YourProjectNamespace
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestCreateFunction)
        {
            const int N = 2;  
            Student* s = new Student[N];

            std::stringstream input;
            input << " Гринчук\n1\n0\n5\n4\n3\n"  
                << " Михальчук\n2\n1\n3\n3\n4\n";  

            std::streambuf* originalCin = std::cin.rdbuf();
            std::cin.rdbuf(input.rdbuf());

            Create(s, N);

            std::cin.rdbuf(originalCin);

            Assert::AreEqual(std::string("Гринчук"), s[0].surname);
            Assert::AreEqual(5, s[0].physics);
            Assert::AreEqual(4, s[0].math);
            Assert::AreEqual(3, s[0].programming);

            Assert::AreEqual(std::string(" Михальчук"), s[1].surname);
            Assert::AreEqual(3, s[1].physics);
            Assert::AreEqual(3, s[1].math);
            Assert::AreEqual(4, s[1].numericalMethods);

            delete[] s;  
        }
    };
}
