
const Char * c_str() const {
    ...
    if (data[size()] != '\0')
    data[size()] = '\0';
    return data;
}

void copy_file_transact(const path& from, 
                    const path& to) {
    bf::path t = to.native() + ".deleteme";
    try{
        bf::copy_file(from, t);
        bf::rename(t, to);        
    } catch (...) {
        ::remove(t.c_str());
        throw;
    }
}

void move_file_transact(const path& from, 
                    const path& to) {
    bf::copy_file_transact(from, to);                        
    try{
        bf::rename(t, to);        
    } catch (...) {
        ::remove(t.c_str());
        throw;
    }
}

namespace detail {
    enum class ScopeGuardOnExit {};
    template <typename Fun>
    ScopeGuard <Fun>
    operator+(ScopeGuardOnExit, Fun&& fn) {
        return ScopeGuard<Fun>(std::forward<Fun>(fn));
    }
}

#define SCOPE_EXIT \
    auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) \
    = ::detail::ScopeGuardOnExit() + [&]()

#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) \

template <typename FunctionType, bool executeOnException>
class ScopeGuardForNewException {
    FunctionType function_ ;
    UncaughtExceptionCounter ec_;
public:
    explicit ScopeGuardForNewException (const FunctionType& fn)
        : function_(fn) {
   }
 
    explicit ScopeGuardForNewException (const FunctionType&& fn)
        : function_(std::move(fn)) {
    ~ScopeGuardForNewException() noexcept(executeOnException) {
        if (executeOnException == ec_.isNewUncaughtException()) {
            function_();
        }
    }
};

enum class ScopeGuard



void copy_file_transact(const path& from, 
                    const path& to) {
    bf::path t = to.native() + ".deleteme";
    SCOPE_FAIL  {::remove(t.c_str()); };
    bf::copy_file(from, t);
    bf::rename(t, to);
}

void move_file_transact(const path& from, 
                    const path& to) {
    bf::copy_file_transact(from, to);                        
    SCOPE_FAIL { ::remove(to.c_str());};
        bf::remove(t.c_str());   
    }
}

int strin



void process(char *const buf, size_t len) {
    if (!len) return;
    const auto save = buf[len - 1];
    buf[len -1] = 255;
    SCOPE_EXIT { buf[len - 1] = save; };
    for(auto p = buff;;) switch( auto c = *p++) {
        ...
    }
}