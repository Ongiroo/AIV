//f is a future tuple of futures
auto x = async([] { return fibonacci<cpp_int>(1'000'000); });
auto y = async([] { return fibonacci<cpp_int>(2'000'000); });
auto z = when_all(std::move(x), std::move(y)).then([](auto f) {
  auto t = f.get();
  return cpp_int(get<0>(t).get() * get<1>(t).get());
});
cout << z.get() << endl;