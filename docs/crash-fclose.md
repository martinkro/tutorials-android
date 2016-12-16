# Crash fclose on Android 7.1.1

## Crash Information

Build fingerprint: 'google/volantis/flounder:7.1.1/NMF26F/3425388:user/release-keys'
12-14 20:25:29.367  1524  1524 F DEBUG   : Revision: '0'
12-14 20:25:29.367  1524  1524 F DEBUG   : ABI: 'arm'
12-14 20:25:29.367  1524  1524 F DEBUG   : pid: 1509, tid: 1509, name: ersoonal.runner  >>> com.persoonal.runner <<<
12-14 20:25:29.368  1524  1524 F DEBUG   : signal 7 (SIGBUS), code 1 (BUS_ADRALN), fault addr 0xffd9b82c
12-14 20:25:29.368  1524  1524 F DEBUG   :     r0 e9f80928  r1 00000008  r2 eb40cae8  r3 e9f8092c
12-14 20:25:29.368  1524  1524 F DEBUG   :     r4 0000a000  r5 00000000  r6 00000000  r7 00000014
12-14 20:25:29.368  1524  1524 F DEBUG   :     r8 00000000  r9 00000002  sl e9f80500  fp e9f80610
12-14 20:25:29.368  1524  1524 F DEBUG   :     ip 0000001c  sp ffd9b82c  lr ffd9b82c  pc eb3e269a  cpsr 800f0030
12-14 20:25:29.376  1524  1524 F DEBUG   : 
12-14 20:25:29.376  1524  1524 F DEBUG   : backtrace:
12-14 20:25:29.377  1524  1524 F DEBUG   :     #00 pc 0005369a  /system/lib/libc.so (je_arena_maybe_purge+413)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #01 pc 0005892f  /system/lib/libc.so (arena_run_dalloc+1154)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #02 pc 000589eb  /system/lib/libc.so (arena_dalloc_bin_run+38)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #03 pc 000551d3  /system/lib/libc.so (arena_dalloc_bin_locked_impl+542)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #04 pc 00055287  /system/lib/libc.so (je_arena_dalloc_bin+74)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #05 pc 000552b3  /system/lib/libc.so (je_arena_dalloc_small+18)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #06 pc 00065021  /system/lib/libc.so (ifree+608)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #07 pc 0006524f  /system/lib/libc.so (je_free+70)
12-14 20:25:29.377  1524  1524 F DEBUG   :     #08 pc 0004f429  /system/lib/libc.so (fclose+96)

## jemalloc android-7.1.1_r1

bionic/libc/private/bionic_globals.h
struct libc_globals{
    vdso_entry vdso[VDSO_END];
    long setjmp_cookie;
    MallocDispatch malloc_dispatch;
}

/bionic/libc/private/bionic_malloc_dispatch.h

struct MallocDispatch {
  MallocCalloc calloc;
  MallocFree free;
  MallocMallinfo mallinfo;
  MallocMalloc malloc;
  MallocMallocUsableSize malloc_usable_size;
  MallocMemalign memalign;
  MallocPosixMemalign posix_memalign;
#if defined(HAVE_DEPRECATED_MALLOC_FUNCS)
  MallocPvalloc pvalloc;
#endif
  MallocRealloc realloc;
#if defined(HAVE_DEPRECATED_MALLOC_FUNCS)
  MallocValloc valloc;
#endif
  MallocIterate iterate;
  MallocMallocDisable malloc_disable;
  MallocMallocEnable malloc_enable;
} __attribute__((aligned(32)));

/bionic/libc/bionic/malloc_common.cpp

87extern "C" void free(void* mem) {
88  auto _free = __libc_globals->malloc_dispatch.free;
89  if (__predict_false(_free != nullptr)) {
90    _free(mem);
91  } else {
92    Malloc(free)(mem);
93  }
94}

104extern "C" void* malloc(size_t bytes) {
105  auto _malloc = __libc_globals->malloc_dispatch.malloc;
106  if (__predict_false(_malloc != nullptr)) {
107    return _malloc(bytes);
108  }
109  return Malloc(malloc)(bytes);
110}


1248static const uint64_t h_steps[] = {
1249#define	STEP(step, h, x, y) \
1250		h,
1251		SMOOTHSTEP
1252#undef STEP
1253	};


#define STEP(step,h,x,y) h,
SMOOTHSTEP

STEP(   1, UINT64_C(0x0000000000000014), 0.005, 0.000001240643750) => UINT64_C(0x0000000000000014),