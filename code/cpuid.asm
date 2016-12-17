[BITS 32]

global __cpuid_get_eax
global __cpuid_get_ebx
global __cpuid_get_ecx
global __cpuid_get_edx
global __cpuid_get_vendor_string
global __cpuid_get_max_eax
global __cpuid_get_stepping
global __cpuid_get_family
global __cpuid_get_model
global __cpuid_get_features_ecx
global __cpuid_get_features_edx
global __cpuid_get_8bit_brand_id
global __cpuid_get_CLFLUSH_size
global __cpuid_get_logical_processors
global __cpuid_get_monitor_line_sizes
global __cpuid_get_monitor_features

__cpuid_get_eax:
	mov eax, [esp + 4]
	push ebx
	cpuid
	pop ebx
	ret

__cpuid_get_ebx:
	mov eax, [esp + 4]
	push ebx
	cpuid
	mov eax, ebx
	pop ebx
	ret

__cpuid_get_ecx:
	mov eax, [esp + 4]
	push ebx
	cpuid
	mov eax, ecx
	pop ebx
	ret

__cpuid_get_edx:
	mov eax, [esp + 4]
	push ebx
	cpuid
	mov eax, edx
	pop ebx
	ret

__cpuid_get_vendor_string:
	push ebx
	xor eax, eax
	cpuid
	mov eax, [esp + 8]
	mov [eax], ebx
	mov [eax + 4], edx
	mov [eax + 8], ecx
	mov byte [eax + 13], 0
	pop ebx
	ret

__cpuid_get_max_eax:
	push ebx
	xor eax, eax
	cpuid
	pop ebx
	ret

__cpuid_get_stepping:
	push ebx
	mov eax, 1
	cpuid
	and eax, 0xF
	pop ebx
	ret

__cpuid_get_family:
	push ebx
	mov eax, 1
	cpuid
	shld ebx, eax, 20
	shld eax, eax, 8
	and ebx, 0xFF
	and eax, 0xF
	cmp eax, 0xF
	jne .cpuid_get_family_skip
	add eax, ebx
.cpuid_get_family_skip:
	pop ebx
	ret

__cpuid_get_model:
	push ebx
	mov eax, 1
	cpuid
	shld eax, eax, 4
	shld ebx, eax, 12
	and eax, 0xF
	and ebx, 0xF0
	cmp eax, 0xF
	jne .cpuid_get_model_skip
	or eax, ebx
.cpuid_get_model_skip:
	pop ebx
	ret

__cpuid_get_features_ecx:
	push ebx
	mov eax, 1
	cpuid
	mov eax, ecx
	pop ebx
	ret

__cpuid_get_features_edx:
	push ebx
	mov eax, 1
	cpuid
	mov eax, edx
	pop ebx
	ret

__cpuid_get_8bit_brand_id:
	push ebx
	mov eax, 1
	cpuid
	and ebx, 0xFF
	mov eax, ebx
	pop ebx
	ret

__cpuid_get_CLFLUSH_size:
	push ebx
	mov eax, 1
	cpuid
	shld eax, ebx, 8
	and eax, 0xFF
	pop ebx
	ret

__cpuid_get_logical_processors:
	push ebx
	mov eax, 1
	cpuid
	shld eax, ebx, 16
	and eax, 0xFF
	pop ebx
	ret

__cpuid_get_monitor_line_sizes:
	push ebx
	mov eax, 5
	cpuid
	and ebx, 0xFFFF
	and eax, 0xFFFF
	shrd ebx, ebx, 16
	or eax, ebx
	pop ebx
	ret

__cpuid_get_monitor_features:
	push ebx
	mov eax, 5
	cpuid
	mov eax, ecx
	pop ebx
	ret