#include "PmergeMe.cpp"
#include "jacobJohnson.cpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: not enough parameters" << std::endl;
        exit (1);
    }
    for (int i(1); i < argc; i++)
    {
        std::istringstream ss(argv[i]);
        std::string str = argv[i];
        if (!isdigit(*argv[i]))
        {
            std::cout << "Error: invalid parameter : " << argv[i] << std::endl;
            exit (1);
        }
        else if (atoi(str.c_str()) < 0)
        {
            std::cout << "Error: negative number : " << str << std::endl;
            exit(1);
        }
    }
    PmergeMe merge;
    clock_t vecTime;
    clock_t deqTime;
    try
    {
        vecTime = clock();
        deqTime = clock();
        merge.assemble(argv, argc);
        vecTime = clock() - vecTime;
        deqTime = clock() - deqTime;
        std::cout << "Time to process a range of " << argc - 1 << " elements with VECTOR : " << (float)vecTime * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;
        std::cout << "Time to process a range of " << argc - 1 << " elements with DEQUE : " << (float)deqTime * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;
    }
    catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
    return (0);
}