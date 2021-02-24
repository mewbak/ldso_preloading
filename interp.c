#define _GNU_SOURCE
#include "interp.h"

static void
lp_init_ctx(struct lp_ctx *ctx, char **envp)
{

	ctx->envp = envp;
	return;
}

int main(int argc, char **argv, char **envp)
{
	struct lp_ctx ctx;

	lp_init_ctx(&ctx, envp);
	return 0;
}
