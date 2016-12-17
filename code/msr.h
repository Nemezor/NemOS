#ifndef HEADER_MSR
#define HEADER_MSR

#define MSR_IA32_MPERF 0xE7
#define MSR_IA32_APERF 0xE8
#define MSR_IA32_EFER 0xC0000080

extern long long msr_read(long msr);
extern void msr_write(long msr, long long data);

#endif