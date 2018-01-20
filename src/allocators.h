#ifndef MARINECORE_ALLOCATORS_H
#define MARINECORE_ALLOCATORS_H

#include <string.h>
#include <string>

#ifdef WIN32
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN 1
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#define mlock(p, n) VirtualLock((p), (n));
#define munlock(p, n) VirtualUnlock((p), (n));
#else
#include <sys/mman.h>
#include <limits.h>
#ifndef PAGESIZE
#include <unistd.h>
#define PAGESIZE sysconf(_SC_PAGESIZE)
#endif
#define mlock(a,b) \
  mlock(((void *)(((size_t)(a)) & (~((PAGESIZE)-1)))),\
  (((((size_t)(a)) + (b) - 1) | ((PAGESIZE) - 1)) + 1) - (((size_t)(a)) & (~((PAGESIZE) - 1))))
#define munlock(a,b) \
  munlock(((void *)(((size_t)(a)) & (~((PAGESIZE)-1)))),\
  (((((size_t)(a)) + (b) - 1) | ((PAGESIZE) - 1)) + 1) - (((size_t)(a)) & (~((PAGESIZE) - 1))))
#endif

template<typename T>
struct secure_allocator : public std::allocator<T>
{
    typedef std::allocator<T> base;
    typedef typename base::size_type size_type;
    typedef typename base::difference_type  difference_type;
    typedef typename base::pointer pointer;
    typedef typename base::const_pointer const_pointer;
    typedef typename base::reference reference;
    typedef typename base::const_reference const_reference;
    typedef typename base::value_type value_type;
    secure_allocator() throw() {}
    secure_allocator(const secure_allocator& a) throw() : base(a) {}
    template <typename U>
    secure_allocator(const secure_allocator<U>& a) throw() : base(a) {}
    ~secure_allocator() throw() {}
    template<typename _Other> struct rebind
    { typedef secure_allocator<_Other> other; };

    T* allocate(std::size_t n, const void *hint = 0)
    {
        T *p;
        p = std::allocator<T>::allocate(n, hint);
        if (p != NULL)
            mlock(p, sizeof(T) * n);
        return p;
    }

    void deallocate(T* p, std::size_t n)
    {
        if (p != NULL)
        {
            memset(p, 0, sizeof(T) * n);
            munlock(p, sizeof(T) * n);
        }
        std::allocator<T>::deallocate(p, n);
    }
};


template<typename T>
struct zero_after_free_allocator : public std::allocator<T>
{
    typedef std::allocator<T> base;
    typedef typename base::size_type size_type;
    typedef typename base::difference_type  difference_type;
    typedef typename base::pointer pointer;
    typedef typename base::const_pointer const_pointer;
    typedef typename base::reference reference;
    typedef typename base::const_reference const_reference;
    typedef typename base::value_type value_type;
    zero_after_free_allocator() throw() {}
    zero_after_free_allocator(const zero_after_free_allocator& a) throw() : base(a) {}
    template <typename U>
    zero_after_free_allocator(const zero_after_free_allocator<U>& a) throw() : base(a) {}
    ~zero_after_free_allocator() throw() {}
    template<typename _Other> struct rebind
    { typedef zero_after_free_allocator<_Other> other; };

    void deallocate(T* p, std::size_t n)
    {
        if (p != NULL)
            memset(p, 0, sizeof(T) * n);
        std::allocator<T>::deallocate(p, n);
    }
};

typedef std::basic_string<char, std::char_traits<char>, secure_allocator<char> > SecureString;

#endif
