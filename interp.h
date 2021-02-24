#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <search.h>
#include <sys/time.h>
#include <elf.h>

typedef struct lp_auxv_iterator {
	unsigned int index;
	struct lp_ctx *ctx;
	Elf64_auxv_t *auxv;
} lp_auxv_iterator_t;

typedef struct lp_auxv_entry {
	uint64_t value;
	int type;
	char *string;
} lp_auxv_entry_t;

typedef struct lp_proc {
	pid_t pid;
	pid_t ppid;
	gid_t gid;
	gid_t egid;
	unsigned int page_size;
	uint64_t phdr_vaddr;
	uint64_t entry_vaddr;
	uint64_t base_vaddr;
	uint64_t canary_value;
	uint64_t phdr_count;
	char *exec_path;
	uint32_t platform;
	uint64_t secure;
} lp_proc_t;

typedef struct lp_ctx {
	char **envp;
	char *lp_script;
	uint64_t flag;
	uint64_t mode;
	struct lp_proc proc;
} lp_ctx_t;

typedef enum lp_iterator_res {
	LP_ITER_OK = 0,
	LP_ITER_DONE,
	LP_ITER_ERROR
} lp_iterator_res_t;

void lp_auxv_iterator_init(struct lp_ctx *, struct lp_auxv_iterator *);
lp_iterator_res_t lp_auxv_iterator_next(struct lp_auxv_iterator *, struct lp_auxv_entry *);

