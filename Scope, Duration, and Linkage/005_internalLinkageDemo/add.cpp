static int add(int a, int b)
{
    return a + b;
}

namespace {

    int counter = 0;

    void addCounter()
    {
        counter++;
    }
}