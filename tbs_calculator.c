#include <stdio.h>
#include <math.h>


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int calculate_tbs(int nre_, int n_re, float r, int qm, int v) {
//   """Calculates the TBS based on the given parameters.

//   Args:
//     nre_: The number of resource elements (REs) allocated for the transport block on a single PRB.
//     n_re: The total number of REs allocated for the PDSCH within a PRB.
//     r: The code rate.
//     qm: The modulation order.
//     v: The number of transmission layers.

//   Returns:
//     The TBS in bits.
//   """

  float ninfo = nre_ * r * qm * v;
  int n = MIN(156, n_re);
  float c = ninfo + 24.0 / 3816.0;

  int tbs;
  if (r <= 1.0 / 4.0) {
    tbs = 8 + 24 - 24;
  } else if (ninfo > 8424.0) {
    tbs = 8 + c * ninfo + 24 - c * 24;
  } else {
    tbs = 8 + c * ninfo + 24 - c * 24;
  }

  return tbs;
}

int main() {
  int nre_ = 100;
  int n_re = 12;
  float r = 438;
  int qm = 6;
  int v = 1;

  int tbs = calculate_tbs(nre_, n_re, r, qm, v);

  printf("The TBS is %d bits.\n", tbs);

  return 0;
}
