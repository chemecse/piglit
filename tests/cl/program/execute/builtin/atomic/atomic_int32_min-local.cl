/*!
[config]
name: atom_int32_min local
clc_version_min: 10
require_device_extensions: cl_khr_local_int32_extended_atomics

[test]
name: simple int
kernel_name: simple_int
dimensions: 1
global_size: 1 0 0
local_size: 1 0 0
arg_out: 0 buffer int[2] 1 -2
arg_in:  1 buffer int[1] NULL
arg_in:  2 int           1
arg_in:  3 int           -2

[test]
name: simple uint
kernel_name: simple_uint
dimensions: 1
global_size: 1 0 0
local_size:  1 0 0
arg_out: 0 buffer uint[2] 3 2
arg_in:  1 buffer uint[1] NULL
arg_in:  2 uint           3
arg_in:  3 uint           2

[test]
name: simple uint 2
kernel_name: simple_uint
dimensions: 1
global_size: 1 0 0
local_size:  1 0 0
arg_out: 0 buffer uint[2] 4294967295 3
arg_in:  1 buffer uint[1] NULL
arg_in:  2 uint           4294967295
arg_in:  3 uint           3


[test]
name: threads int
kernel_name: threads_int
dimensions: 1
global_size: 8 0 0
local_size:  8 0 0
arg_out: 0 buffer int[1] 0
arg_in:  1 buffer int[1] NULL

[test]
name: threads uint
kernel_name: threads_uint
dimensions: 1
global_size: 8 0 0
local_size:  8 0 0
arg_out: 0 buffer uint[1] 0
arg_in:  1 buffer uint[1] NULL

!*/

#define SIMPLE_TEST(TYPE) \
kernel void simple_##TYPE(global TYPE *out, local TYPE *mem, TYPE initial, TYPE other) { \
	*mem = initial; \
	TYPE a = atom_min(mem, other); \
	out[0] = a; \
	out[1] = *mem; \
}

#define THREADS_TEST(TYPE) \
kernel void threads_##TYPE(global TYPE *out, local TYPE *mem) { \
	*mem = 8; \
	barrier(CLK_LOCAL_MEM_FENCE); \
	atom_min(mem, get_global_id(0)); \
	barrier(CLK_LOCAL_MEM_FENCE); \
	*out = *mem; \
}

SIMPLE_TEST(int)
SIMPLE_TEST(uint)

THREADS_TEST(int)
THREADS_TEST(uint)
