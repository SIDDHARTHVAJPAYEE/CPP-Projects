#include<stdio.h>
class Screen
{
public:
void operator<<(int x)
{
printf("%d",x);
}
void operator<<(const char *x)
{
printf("%s",x);
}
void operator<<(char x)
{
printf("%c",x);
}
};
namespace siddharth
{
Screen screen;
}
using namespace siddharth;
int main()
{
screen<<"GOD IS GREAT";
screen<<100;
screen<<'A';
return 0;
}