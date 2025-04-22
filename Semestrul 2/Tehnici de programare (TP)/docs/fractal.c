/* Generate box fractal in SVG format (Scalable vector graphics)
 * http://en.wikipedia.org/wiki/Vicsek_fractal
 * Run ./a.out > boxfract.svg and look at the file in a browser
 * SVG drawing commands: l=line, m=move, h=horiz. line, v=vert. line
 * uppercase: absolute coordinates, lowercase: relative coordinates
 * e.g. M x y = move to (x, y)
 * l dx dy = line from current point, moving by dx, dy */

#include <stdio.h>

void drawsqr(double x, double y, double side)
{
  printf("M %.1f %.1f ", x, y); // move to origin of figure
  printf("h %.1f ", side);      // %.1f : real with 1 digit after .
  printf("v %.1f ", side);
  printf("h %.1f ", -side);
  printf("v %.1f ", -side);
}

void drawfig(double x, double y, double side)
{
  if (side < 3)
    drawsqr(x, y, side);
  else
  {
    double s3 = side / 3;
    drawfig(x, y, s3);                   // NNE
    drawfig(x + 2 * s3, y, s3);          // NNW
    drawfig(x + s3, y + s3, s3);         // centru
    drawfig(x, y + 2 * s3, s3);          // ssw
    drawfig(x + 2 * s3, y + 2 * s3, s3); // sse
  }
}

int main(void)
{
  // string constant followed by string constant = concatenated constrants
  printf("<?xml version=\"1.0\"?>\n"
         "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n"
         "<path fill=\"none\" stroke=\"blue\" d=\"");
  drawfig(0, 0, 1000);
  printf("\"/>\n</svg>\n");
  return 0;
}
