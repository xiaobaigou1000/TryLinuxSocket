#include <cstdio>
#include <vector>

int main()
{
    std::FILE *source;
    std::FILE *destination;
    std::vector<char> buffer(512);
    source = fopen("source.txt", "r");
    destination = fopen("destination.txt", "w");

    while (fgets(buffer.data(), 512, source) != nullptr)
    {
        fputs(buffer.data(), destination);
    }
    fclose(source);
    fclose(destination);
}