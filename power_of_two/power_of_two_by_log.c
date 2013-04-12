#include <stdio.h>
#include <math.h>
int main()
{
  int a;
  float r;

  printf( "Hello! Enter number:\n" );
  scanf( "%d", &a);
  r=log(a)/log(2);
  if ( floorf( r ) == r ){
    printf("Yes, %i is a power of two.\n", a);
  } else {
    printf("No, %i is not a power of two.\n", a);
  }
  return 0;
}
