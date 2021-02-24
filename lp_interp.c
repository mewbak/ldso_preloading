#define _GNU_SOURCE
#include "lp_interp.h"

static void
lp_init_ctx(struct lp_ctx *ctx, char **envp)
{

	ctx->envp = envp;
	return;
}

int
_start(int argc, char **argv, char **envp)
{
	struct lp_ctx ctx;
	struct lp_auxv_entry entry;
	lp_auxv_iterator_t auxv_iter;

	lp_printf("envp: %p\n", envp);
	lp_init_ctx(&ctx, envp);
	lp_auxv_iterator_init(&ctx, &auxv_iter);
	while(lp_auxv_iterator_next(&auxv_iter, &entry) == LP_ITER_OK) {
		lp_printf("type: %u\n", entry.type);
		if (entry.type == AT_EXECFN) {
			lp_printf("EXEC_FN: %s\n", (char *)entry.value);
		}
	}
	return 0;
}
