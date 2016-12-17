#include "cpuid.h"

struct cpuid_info_t info;

void cpuid_detect() {
	unsigned long temp;
	__cpuid_get_vendor_string((char*)&info.vendor_string);
	info.max_cpuid_value = __cpuid_get_max_eax();
	if (info.max_cpuid_value > 0) {
		info.stepping = __cpuid_get_stepping();
		info.family = __cpuid_get_family();
		info.model = __cpuid_get_model();
		info.features_ecx = __cpuid_get_features_ecx();
		info.features_edx = __cpuid_get_features_edx();
		info.brand_ID_8bit = __cpuid_get_8bit_brand_id();
		info.CLFLUSH_size = __cpuid_get_CLFLUSH_size();
		info.logical_processors = __cpuid_get_logical_processors();

		info.features.hypervisor = info.features_ecx & 0x80000000;
		info.features.F16C = info.features_ecx & 0x20000000;
		info.features.AVX = info.features_ecx & 0x10000000;
		info.features.XSAVE_enabled = info.features_ecx & 0x08000000;
		info.features.XSAVE_supported = info.features_ecx & 0x04000000;
		info.features.AES = info.features_ecx & 0x02000000;
		info.features.POPCNT = info.features_ecx & 0x00800000;
		info.features.SSE4_2 = info.features_ecx & 0x00100000;
		info.features.SSE4_1 = info.features_ecx & 0x00080000;
		info.features.CMPXCHG16B = info.features_ecx & 0x00002000;
		info.features.FMA = info.features_ecx & 0x00001000;
		info.features.supplemental_SSE3 = info.features_ecx & 0x00000200;
		info.features.MONITOR = info.features_ecx & 0x00000008;
		info.features.PCLMULQDQ = info.features_ecx & 0x00000002;
		info.features.SSE3 = info.features_ecx & 0x00000001;
		info.features.hyper_threading = info.features_edx & 0x10000000;
		info.features.SSE2 = info.features_edx & 0x04000000;
		info.features.SSE = info.features_edx & 0x02000000;
		info.features.FXSR = info.features_edx & 0x01000000;
		info.features.MMX = info.features_edx & 0x00800000;
		info.features.CLFLUSH = info.features_edx & 0x00080000;
		info.features.PSE36 = info.features_edx & 0x00020000;
		info.features.PAT = info.features_edx & 0x00010000;
		info.features.CMOV = info.features_edx & 0x00008000;
		info.features.MCA = info.features_edx & 0x00004000;
		info.features.PGE = info.features_edx & 0x00002000;
		info.features.MTRR = info.features_edx & 0x00001000;
		info.features.sys_instructions = info.features_edx & 0x00000800;
		info.features.APIC = info.features_edx & 0x00000200;
		info.features.CMPXCHG8B = info.features_edx & 0x00000100;
		info.features.MCE = info.features_edx & 0x00000080;
		info.features.PAE = info.features_edx & 0x00000040;
		info.features.MSR = info.features_edx & 0x00000020;
		info.features.TSC = info.features_edx & 0x00000010;
		info.features.PSE = info.features_edx & 0x00000008;
		info.features.debugging = info.features_edx & 0x00000004;
		info.features.VME = info.features_edx & 0x00000002;
		info.features.FPU = info.features_edx & 0x00000001;
	}
	if (info.max_cpuid_value > 4) {
		temp = __cpuid_get_monitor_line_sizes();
		info.monitor.minimum_line_size = (unsigned short)(temp & 0xFFFF);
		info.monitor.maximum_line_size = (unsigned short)((temp >> 16) & 0xFFFF);
		temp = __cpuid_get_monitor_features();
		info.monitor.IBE = temp & 0x00000002;
		info.monitor.EMX = temp & 0x00000001;
	}
	if (info.max_cpuid_value > 5) {
		info.frequency_monitor = __cpuid_get_ecx(6) & 0x00000001;
	}
}

struct cpuid_info_t* cpuid_get_info() {
	return &info;
}