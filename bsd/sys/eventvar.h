/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*-
 * Copyright (c) 1999,2000 Jonathan Lemon <jlemon@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$FreeBSD: src/sys/sys/eventvar.h,v 1.1.2.2 2000/07/18 21:49:12 jlemon Exp $
 */

#ifndef _SYS_EVENTVAR_H_
#define _SYS_EVENTVAR_H_

#include <sys/event.h>
#include <sys/select.h>
#include <kern/kern_types.h>

#define KQ_NEVENTS	16		/* minimize copy{in,out} calls */
#define KQEXTENT	256		/* linear growth by this amount */

struct kqueue {
	decl_lck_spin_data( ,kq_lock)		/* kqueue lock */
	int		kq_state;
	int		kq_count;		/* number of queued events */
	struct kqtailq	kq_head;		/* list of queued events */
	struct kqtailq	kq_inprocess;		/* list of in-process events */
	struct selinfo	kq_sel;		/* parent select/kqueue info */
	struct filedesc	*kq_fdp;

#define KQ_SEL		0x01
#define KQ_SLEEP	0x02
#define KQ_PROCWAIT	0x04
};

extern struct kqueue *kqueue_alloc(struct proc *);
extern void kqueue_dealloc(struct kqueue *, struct proc *);

typedef int (*kevent_callback_t)(struct kqueue *, struct kevent *, void *);
typedef void (*kevent_continue_t)(struct kqueue *, void *, int);

extern int kevent_register(struct kqueue *, struct kevent *, struct proc *);
extern int kevent_scan(struct kqueue *, kevent_callback_t, kevent_continue_t,
		       void *, struct timeval *, struct proc *);

#endif /* !_SYS_EVENTVAR_H_ */
