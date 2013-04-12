#include <stdio.h>
#include <math.h>
int main()
{
  int a;
  double res;

  printf( "Hello! Enter number:\n" );
  scanf( "%d", &a);
  if ( a ==1 ||  a==2 ){
    goto YES;
  }
  res=a;
  while( res > 2 )
  {
    res/=2;
  }
  if ( res == 2 ){
YES:
    printf("Yes, %i is a power of two.\n", a);
  } else {
    printf("No, %i is not a power of two.\n", a);
  }
  return 0;
}
