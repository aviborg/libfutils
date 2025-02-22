/******************************************************************************
 * Copyright (c) 2015 Parrot S.A.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Parrot Company nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE PARROT COMPANY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @file fdutils.c
 *
 * @brief fd utility function
 *
 *****************************************************************************/
#define _GNU_SOURCE
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include "futils/fdutils.h"

#ifdef _WIN32
#define FD_CLOEXEC	1
#define F_GETFD		1		/**< Get file descriptor flags */
#define F_SETFD		2		/**< Set file descriptor flags */
#define F_GETFL		3		/**< Get file status flags */
#define F_SETFL		4		/**< Set file status flags */
#endif

int fd_set_close_on_exec(int fd)
{
	int old, ret;

	old = fcntl(fd, F_GETFD, 0);
	if (old < 0)
		return -errno;

	ret = fcntl(fd, F_SETFD, FD_CLOEXEC | old);
	if (ret < 0)
		return -errno;

	return 0;
}

int fd_has_close_on_exec(int fd)
{
	int flags;
	flags = fcntl(fd, F_GETFD, 0);
	if (flags < 0)
		return 0;

	return flags & FD_CLOEXEC ? 1 : 0;
}

int fd_add_flags(int fd, int flags)
{
	int old, ret;

	old = fcntl(fd, F_GETFL, 0);
	if (old < 0)
		return -errno;

	ret = fcntl(fd, F_SETFL, old | flags);
	if (ret < 0)
		return -errno;

	return 0;
}
