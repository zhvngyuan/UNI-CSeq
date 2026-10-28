# ------------------------------------------------------------------------------
# NAME = abs_common
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Strings and settings needed for translation
#
# TODO:
#
# Changelog:
#   2016.05.09   Fix problem with pthread type
# -----------------------------------------------------------------------------

namespace = {}

# Thread information
namespace['threadpc'] = '__cs_pc_'
namespace['threadargs'] = '__cs_args_'
namespace['activethread'] = '__cs_activethread_'

namespace['threadname'] = '__cseq_t_'

namespace['malloc'] = 'malloc'
namespace['free'] = 'free'

# Predefined functions
namespace['nondet_type1'] = """\
_Bool __VERIFIER_nondet_bool()
{
    _Bool i;
    return i;
}

char __VERIFIER_nondet_char()
{
    char i;
    return i;
}

int __VERIFIER_nondet_int()
{
    int i;
    return i;
}

unsigned int __VERIFIER_nondet_uint()
{
    unsigned int i; __VERIFIER_assume(i>=0);
    return i;
}

"""

namespace['nondet_type2'] = """\
#define __VERIFIER_nondet_int() nondet_int()
int nondet_int();

#define __VERIFIER_nondet_uint() nondet_uint()
unsigned int nondet_uint();

#define __VERIFIER_nondet_bool() nondet_bool()
_Bool nondet_bool();

char nondet_char();
unsigned char nondet_uchar();

"""

namespace['nondet_type3'] = """\
extern int __VERIFIER_nondet_int();
extern unsigned int __VERIFIER_nondet_uint();
extern _Bool __VERIFIER_nondet_bool();
extern char __VERIFIER_nondet_char();
extern unsigned char __VERIFIER_nondet_uchar();
"""

namespace['assume'] = """\
void __VERIFIER_assume(int i)
{
    while (!i);
    return;
}

"""

namespace['error1'] = """\
void __cseq_error()
{
    ERROR: goto ERROR;
}

"""

namespace['error2'] = """\
void __cseq_error()
{
    assert(0);
}

"""

namespace['error3'] = """\
void __cseq_error()
{
    __VERIFIER_error();
}

"""

namespace['error4'] = """\
extern void __VERIFIER_error();
void __cseq_error() {__VERIFIER_error(); }

"""

namespace['error_uautomizer'] = """\
extern void __VERIFIER_error();
#define assert(cond) if (!(cond)) __VERIFIER_error() 

"""

namespace['llbmc_macro'] = """\
void __llbmc_assume(int);
void __llbmc_assert(int);

#define assume(x) __llbmc_assume(x)
#define __VERIFIER_assume(x) __llbmc_assume(x)

#define assert(x) __llbmc_assert(x)
#define __VERIFIER_assert(x) __llbmc_assert(x)
"""

namespace['functions2'] = """\
//void * __cs_safe_malloc(size_t size)
//{
//    void * ptr = malloc(size);
//    __VERIFIER_assume(ptr);
//    return ptr;
//}

//void * __cs_unsafe_malloc(size_t size)
//{
//    if(__VERIFIER_nondet_bool())
//        return 0;
//    return malloc(size);
//}

void __cs_init_scalar(void *var, unsigned int size)
{
    if (size == sizeof(int))
        *(int *)var = __VERIFIER_nondet_int();
    else {
        char * ptr = (char *)var;
        // size_t j;
        //for (j=0; j<size; j++)
        //  ptr[j] = __cs_nondet_char();
    }
}

"""

namespace['stdlib'] = """\
#include <stdlib.h>
"""

namespace['stdio'] = """\
#include <stdio.h>
"""

namespace['include'] = """\
typedef int __cs_mutex_t;
#define pthread_mutex_t __cs_mutex_t
typedef int __cs_cond_t;
#define pthread_cond_t __cs_cond_t
typedef int __cs_t;
#define pthread_t __cs_t
"""

# Prefix for local variable
namespace['prefix'] = '__cs_l_'

# Prefix for thread local variable
namespace['threadlocal'] = '__cs_thread_local_'

# Name for thread index
namespace['threadid'] = '__cs_thread_index'
