#include <dispatch/dispatch.h>
#include <functional>
#include <future>
#include <type_traits>

namespace stlab {
template <class Function, class... Args>
auto async(Function &&f, Args &&... args) {
  using result_type =
      std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>;
  using packaged_type = std::packaged_task<result_type()>;
  auto p = new packaged_type(
      std::bind(std::forward<Function>(f), std::forward<Args>(args)...));
  auto result = p->get_future();
  dispatch_async_f(
      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), p,
      [](void *f_) {
        packaged_type *f = static_cast<packaged_type *>(f_);
        (*f)();
        delete f;
      });
  return result;
}
} // namespace stlab