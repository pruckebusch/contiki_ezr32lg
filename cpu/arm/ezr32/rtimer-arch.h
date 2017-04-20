#ifndef __RTIMER_ARCH_H__
#define __RTIMER_ARCH_H__

// Resolution 30.518us, max schedule : 512s
#define RTIMER_ARCH_SECOND  32768
/*
typedef uint32_t rtimer_clock_t;

// TODO : Warning rtimer_clock_t is in fact uint24 !!!
#define RTIMER_CLOCK_LT(a,b)     ((signed long)((a)-(b)) < 0)
*/

rtimer_clock_t rtimer_arch_now(void);

#endif /* __RTIMER_ARCH_H__ */
