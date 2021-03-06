#include "lp_interp.h"

#define ERRONEOUS_AUXV_COUNT 4096

void
lp_auxv_iterator_init(struct lp_ctx *ctx, struct lp_auxv_iterator *iter)
{
	int i;

	iter->index = 0;
	iter->ctx = ctx;

	for (i = 0; &ctx->envp[i] != NULL; i++)
		;
	iter->auxv = (Elf64_auxv_t *)&ctx->envp[i];
	return;
}

lp_iterator_res_t
lp_auxv_iterator_next(struct lp_auxv_iterator *iter, struct lp_auxv_entry *entry)
{
	int i = 0;
	struct lp_ctx *ctx = 0;

	lp_printf("iter: index %d\n", iter->index);
	lp_printf("iter: a_type: %d\n", iter->auxv[iter->index].a_type);
	if (iter->auxv[iter->index].a_type == AT_NULL)
		return LP_ITER_DONE;

	entry->type = iter->auxv[iter->index].a_type;
	entry->value = iter->auxv[iter->index].a_un.a_val;
	if (iter->auxv[iter->index].a_type == AT_EXECFN)
		entry->string = (char *)entry->value;
	if (iter->index++ >= ERRONEOUS_AUXV_COUNT)
		return LP_ITER_ERROR;
	return LP_ITER_OK;
}
