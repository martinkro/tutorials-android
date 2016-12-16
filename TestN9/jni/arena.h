#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

#define	SMOOTHSTEP_VARIANT	"smoother"
#define	SMOOTHSTEP_NSTEPS	200
#define	SMOOTHSTEP_BFP		24

struct arena_s {
	/* This arena's index within the arenas array. */
	unsigned		ind;
	/*
	 * Number of threads currently assigned to this arena.  This field is
	 * synchronized via atomic operations.
	 */
	unsigned		nthreads;

	size_t			decay_backlog[SMOOTHSTEP_NSTEPS];

};

typedef struct arena_s arena_t;

size_t
arena_decay_backlog_npages_limit(const arena_t *arena);

#endif