#include "RPN.cpp"

int main(int argc, char **argv)
{
    RPN rpn;
    int size(0);

    if (argc != 2)
    {
        std::cerr << "Error : give me (only) a reverse polish notation !" << std::endl;
        return (0);
    }
    else
    {
        for (int i(1); i < argc; i++)
        {
            size = rpn.gather(argv[i]);
        }
        if (size != 1)
        {
            std::cerr << "Error: too many elements left" << std::endl;
            return (0);
        }
        std::cout << "Resultat : " << rpn.getRes() << std::endl;
    }
    return (0);
}
