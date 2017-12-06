// Egyptian Multiplication (Russian Peasant Algorithm)

template <typename T, typename N, typename O> T 
power(T x, N n, O op) {
  if (n == 0)
    return identity_element(op);
  while ((n & 1) == 0) {
    n >>= 1;
    x = op(x, x);
  }
  T result = x;
  n >>= 1;
  while (n != 0) {
    x = op(x, x);
    if ((n & 1) != 0)
      result = op(result, x);
    n >>= 1;
  }
  return result;
}