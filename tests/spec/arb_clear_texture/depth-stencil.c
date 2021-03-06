/*
 * Copyright (c) 2014 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/** @file depth-stencil.c
 *
 * A test of using glClearTexSubImage to clear a depth-stencil
 * texture.
 */

#include "common.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

	config.supports_gl_compat_version = 13;

	config.window_visual = PIGLIT_GL_VISUAL_RGB | PIGLIT_GL_VISUAL_DOUBLE;

	config.khr_no_error_support = PIGLIT_NO_ERRORS;

PIGLIT_GL_TEST_CONFIG_END

void
piglit_init(int argc, char **argv)
{
	bool pass;

        /* We can create depth/stencil textures if either:
         * 1. We have GL 3.0 or later
         * 2. We have GL_EXT_packed_depth_stencil and GL_ARB_depth_texture
         */
	if (piglit_get_gl_version() < 30
	    && !(piglit_is_extension_supported("GL_EXT_packed_depth_stencil") &&
		 piglit_is_extension_supported("GL_ARB_depth_texture"))) {
		printf("OpenGL 3.0 or GL_EXT_packed_depth_stencil + "
		       "GL_ARB_depth_texture is required.\n");
		piglit_report_result(PIGLIT_SKIP);
	}

	pass = test_format(GL_DEPTH24_STENCIL8_EXT,
			   GL_DEPTH_STENCIL_EXT,
			   GL_UNSIGNED_INT_24_8_EXT,
			   4);

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}

enum piglit_result
piglit_display(void)
{
	/* unused */
	return PIGLIT_FAIL;
}
