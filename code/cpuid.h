#ifndef HEADER_CPUID
#define HEADER_CPUID

#include <stdbool.h>

struct cpuid_info_t {
	char vendor_string[13];
	unsigned long max_cpuid_value;
	unsigned char stepping;
	unsigned char family;
	unsigned char model;
	unsigned long features_ecx;
	unsigned long features_edx;
	unsigned char brand_ID_8bit;
	unsigned char CLFLUSH_size;
	unsigned char logical_processors;
	struct cpuid_feature_t {
		bool hypervisor;
		bool F16C;
		bool AVX;
		bool XSAVE_enabled;
		bool XSAVE_supported;
		bool AES;
		bool POPCNT;
		bool SSE4_2;
		bool SSE4_1;
		bool CMPXCHG16B;
		bool FMA;
		bool supplemental_SSE3;
		bool MONITOR;
		bool PCLMULQDQ;
		bool SSE3;
		bool hyper_threading;
		bool SSE2;
		bool SSE;
		bool FXSR;
		bool MMX;
		bool CLFLUSH;
		bool PSE36;
		bool PAT;
		bool CMOV;
		bool MCA;
		bool PGE;
		bool MTRR;
		bool sys_instructions;
		bool APIC;
		bool CMPXCHG8B;
		bool MCE;
		bool PAE;
		bool MSR;
		bool TSC;
		bool PSE;
		bool debugging;
		bool VME;
		bool FPU;
	} features;
	struct cpuid_monitor_t {
		unsigned short minimum_line_size;
		unsigned short maximum_line_size;
		bool IBE;
		bool EMX;
	} monitor;
	bool frequency_monitor;
};

extern unsigned long __cpuid_get_eax(unsigned long eax);
extern unsigned long __cpuid_get_ebx(unsigned long eax);
extern unsigned long __cpuid_get_ecx(unsigned long ecx);
extern unsigned long __cpuid_get_edx(unsigned long edx);
extern void __cpuid_get_vendor_string(char* ptr);
extern unsigned long __cpuid_get_max_eax();
extern unsigned char __cpuid_get_stepping();
extern unsigned char __cpuid_get_family();
extern unsigned char __cpuid_get_model();
extern unsigned long __cpuid_get_features_ecx();
extern unsigned long __cpuid_get_features_edx();
extern unsigned char __cpuid_get_8bit_brand_id();
extern unsigned char __cpuid_get_CLFLUSH_size();
extern unsigned char __cpuid_get_logical_processors();
extern unsigned long __cpuid_get_monitor_line_sizes();
extern unsigned long __cpuid_get_monitor_features();

void cpuid_detect();
struct cpuid_info_t* cpuid_get_info();

#endif